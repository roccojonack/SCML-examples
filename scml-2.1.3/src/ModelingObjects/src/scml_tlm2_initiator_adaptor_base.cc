/*****************************************************************************
 *                   Copyright (C) 2008-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
/*
 * Modifications :
 *
 * Purpose of file : Definition of the scml_tlm2_initiator_adaptor_base
 *
 */

#include "scmlinc/scml_tlm2_initiator_adaptor_base.h"
#include "scmlinc/scml_mapable_if_to_T.h"
#include "scmlinc/scml_memory_utils.h"
#include <vector>
#include <scml2_logging/severity.h>

namespace {
  struct MMHelper
  {
    MMHelper(tlm::tlm_generic_payload& trans) : mTrans(trans) { mTrans.acquire(); }
    ~MMHelper() { mTrans.release(); }
  private:
    tlm::tlm_generic_payload& mTrans;
  };
}
  
scml_tlm2_initiator_adaptor_base::
scml_tlm2_initiator_adaptor_base(sc_core::sc_module_name name,
                                 unsigned int busWidth) :
  sc_core::sc_module(name),
  mWarning(this->name(), scml2::logging::severity::warning()),
  mError(this->name(), scml2::logging::severity::error()),
  mBusWidth(busWidth),
  mPool(1),
  mHasHostEndianness(true)
  , mMapableIf(new scml_mapable_if_to_T<scml_tlm2_initiator_adaptor_base>(*this))
{
  // FIXME: must be power of 2
  assert(!(mBusWidth & (mBusWidth - 1)));
}


scml_tlm2_initiator_adaptor_base::~scml_tlm2_initiator_adaptor_base()
{
  delete mMapableIf;
}

scml_tlm2_initiator_adaptor_base::operator scml_mapable_if& ()
{
  return *mMapableIf;
}

scml_tlm2_initiator_adaptor_base::operator const scml_mapable_if& () const
{
  return *mMapableIf;
}

void scml_tlm2_initiator_adaptor_base::set_endianness(scml_endian e)
{
  mHasHostEndianness =
    scml_memory_utils::hasHostEndianness(
      scml_memory_utils::convert_scml_to_cwrEnd(e));
}

scml_endian scml_tlm2_initiator_adaptor_base::get_endianness() const
{
  if (mHasHostEndianness &&
      scml_memory_utils::hasHostEndianness(cwrLitend)) {
    return scml_little_endian;

  } else {
    return scml_big_endian;
  }
}


#define TRANSPORT(IF) \
  IF::response_type \
  scml_tlm2_initiator_adaptor_base::transport(const IF::request_type& req) \
  { \
    return forwardRequest<IF>(req); \
  }
SCML_FOR_EACH_PV_INTERFACE_TYPE(TRANSPORT)
#undef TRANSPORT


template <typename IF>
typename IF::response_type
scml_tlm2_initiator_adaptor_base::forwardRequest(const typename IF::request_type& req)
{
  // FIXME: add checks

  // only pvIncr is supported by SCML
  if (req.getBurstType() != pvIncr && req.getBurstCount() > 1) {
    SCML2_LOG(mError) << "ERROR: Illegal burstType, only pvIncr is supported!" << std::endl;
  }
  
  // offset not supported
  assert(!req.getOffset());
  // dataSize must be <= buswidth
  assert(req.getDataSize() <= mBusWidth);

  typename IF::response_type resp = req.obtainResp();

  if (!req.getBurstCount()) {
    // ignore requests with a burstCount of 0
    return resp;
  }

  // unaligned accesses not supported
  if (req.getAddress() % (req.getDataSize() / 8)) {
    resp.setResponse(pvError);
    return resp;
  }

  //// FIXME
  //if (req.getBurstCount() > 1 && req.getDataSize() != N) {
  //  SCML2_LOG(mError)
  //    << "The data width of the SCML memory must be the same as the mBusWidth of the tlm2 socket"
  //    << "       Burst accesses should have a wordsize equal to this data width"
  //    << std::endl;
  //}

  tlm::tlm_generic_payload* trans = mPool.claim();
  // FIXME
  trans->set_mm(this);
  MMHelper mmHelper(*trans);

  if (mHasHostEndianness) {
    trans->set_address(req.getAddress());

  } else {
    const unsigned int busWidth = (mBusWidth + 7) / 8;
    trans->set_address(req.getAddress() ^ (busWidth - req.getDataSize() / 8));
  }

  const unsigned int nrOfbytes = req.getBurstCount() * req.getDataSize() / 8;
  std::vector<unsigned char> dataPtr(nrOfbytes);
  trans->set_data_ptr(&dataPtr[0]);
  trans->set_data_length(nrOfbytes);
  trans->set_streaming_width(nrOfbytes);
  trans->set_byte_enable_ptr(0);

  // FIXME: mBusWidth must be equal to data_size
  if (req.getType() == pvWrite) {
    trans->set_command(tlm::TLM_WRITE_COMMAND);
    for (unsigned int i = 0; i < req.getBurstCount(); ++i) {
      for (unsigned int j = 0; j < req.getDataSize() / 8; ++j) {
        dataPtr[i * req.getDataSize() / 8 + j] =
          scml::convert<typename IF::data_type, unsigned char>(req.getWriteData(i) >> (j * 8));
      }
    }

  } else {
    trans->set_command(tlm::TLM_READ_COMMAND);
  }


  if (req.getMode() == pvDebug) {
    if(forwardDebugTransaction(*trans) != trans->get_data_length()) {
      resp.setResponse(pvError);
      return resp;
    }

  } else {
    forwardTransaction(*trans);
  }

  if (req.getType() == pvRead) {
    for (unsigned int i = 0; i < req.getBurstCount(); ++i) {
      typename IF::data_type tmp = 0;
      for (unsigned int j = 0; j < req.getDataSize() / 8; ++j) {
        tmp |= scml::convert<unsigned int, typename IF::data_type>(
                 dataPtr[i * req.getDataSize() / 8 + j]) << (j * 8);
      }
      resp.setReadData(tmp, i);
    }
  }

  resp.setResponse(trans->get_response_status() == tlm::TLM_OK_RESPONSE ? pvOk : pvError);
  return resp;
}

void scml_tlm2_initiator_adaptor_base::free(tlm::tlm_generic_payload* trans)
{
  trans->reset();
  mPool.release(trans);
}

