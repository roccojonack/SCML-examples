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
 * Purpose of file : Definition of the scml_tlm2_target_adaptor_base
 *
 */

#include "scmlinc/scml_tlm2_target_adaptor_base.h"
#include "scmlinc/scml_memory_utils.h"
#include "scmlinc/scml_pool.h"
#include <vector>

namespace {
  template <typename REQ>
  scml_pool<REQ>& getReqPool()
  {
    static scml_pool<REQ> pool(1);
    return pool;
  }
}

scml_tlm2_target_adaptor_base::
scml_tlm2_target_adaptor_base(sc_core::sc_module_name name,
                              unsigned int busWidth) :
  sc_core::sc_module(name),
  pOut("pOut"),
  mBusWidth(busWidth),
  mHasHostEndianness(true)
{
  // FIXME: must be power of 2
  assert(!(mBusWidth & (mBusWidth - 1)));
}

scml_tlm2_target_adaptor_base::~scml_tlm2_target_adaptor_base()
{
}

void scml_tlm2_target_adaptor_base::set_endianness(scml_endian e)
{
  mHasHostEndianness =
    scml_memory_utils::hasHostEndianness(
      scml_memory_utils::convert_scml_to_cwrEnd(e));
}

scml_endian scml_tlm2_target_adaptor_base::get_endianness() const
{
  if (mHasHostEndianness &&
      scml_memory_utils::hasHostEndianness(cwrLitend)) {
    return scml_little_endian;

  } else {
    return scml_big_endian;
  }
}

void
scml_tlm2_target_adaptor_base::
forwardTransaction(tlm::tlm_generic_payload& trans, bool isDebug)
{
  switch (pOut->getPVInterfaceType()) {
  #define CONVERT_TRANSACTION(IF) \
    case scml::If2PVInterfaceType<IF>::result: \
      forwardTransactionImp<IF>(trans, isDebug); \
      break;
  SCML_FOR_EACH_PV_INTERFACE_TYPE(CONVERT_TRANSACTION)
  #undef CONVERT_TRANSACTION

  case scml::PV_INTERFACE_UNKNOWN:
    // FIXME: hard coded 64bit address
    switch (mBusWidth) {
    case 8:
    case 16:
    case 32:
      forwardTransactionImp<scml_memory_pv_64_32_if>(trans, isDebug);
      break;
    case 64:
      forwardTransactionImp<scml_memory_pv_64_64_if>(trans, isDebug);
      break;
    case 128:
      forwardTransactionImp<scml_memory_pv_64_128_if>(trans, isDebug);
      break;
    case 256:
      forwardTransactionImp<scml_memory_pv_64_256_if>(trans, isDebug);
      break;
    case 512:
      forwardTransactionImp<scml_memory_pv_64_512_if>(trans, isDebug);
      break;
    default:
      assert(0); exit(1);
      break;
    };
    break;

  default:
    assert(0); exit(1);
    break;
  }
}

template <typename IF>
void
scml_tlm2_target_adaptor_base::
forwardTransactionImp(tlm::tlm_generic_payload& trans, bool isDebug)
{
  const unsigned int dataLength = trans.get_data_length();
  const unsigned int busWidth = (mBusWidth + 7) / 8;
  const unsigned long long address = trans.get_address();
  if ((trans.get_byte_enable_ptr() && !isDebug) || // byte enables (ignored if debug)
      ((dataLength > busWidth) &&                  // Burst:
       ((dataLength % busWidth) ||                 // - multiple of buswidth
        (address % busWidth))) ||                  // - address aligned on buswidth
      ((dataLength <= busWidth) &&                 // Single access:
       ((dataLength & (dataLength - 1)) ||         // - size power of 2
        (address % dataLength))) ||                // - address aligned on size
      (trans.get_streaming_width() < dataLength && !isDebug)) { // streaming burst (ignored if debug)
    // Unroll transaction to byte accesses
    unrollTransaction<IF>(trans, isDebug);

  } else {
    // no unrolling needed
    typename IF::request_type& req =
      *getReqPool<typename IF::request_type>().claim();
    unsigned int dataSize = 0;
    if (dataLength > busWidth) {
      dataSize = busWidth;
      req.setBurstCount(dataLength / busWidth);

    } else {
      dataSize = dataLength;
      req.setBurstCount(1);
    }
    req.setDataSize(dataSize * 8);
    req.setOffset(0);
    req.setBurstType(pvIncr);
    req.setThreadID(0);
    req.setMode(isDebug ? pvDebug : pvDefault);
    // FIXME: extensions
    

    std::vector<typename IF::data_type> data(req.getBurstCount());

    if (trans.is_read()) {
      req.setWriteDataSource(0);
      req.setReadDataDestination(&data[0]);
      req.setType(pvRead);

    } else {
      req.setWriteDataSource(&data[0]);
      req.setReadDataDestination(0);
      req.setType(pvWrite);
    }

    if (mHasHostEndianness) {
      req.setAddress(trans.get_address());

    } else {
      req.setAddress(trans.get_address() ^ (busWidth - dataSize));
    }

    // FIXME: sizeof(IF::data_type) must be >= busWidth?
    unsigned char* dataPtr = trans.get_data_ptr();
    if (trans.is_write()) {
      for (unsigned int i = 0; i < req.getBurstCount(); ++i) {
        data[i] = 0;
        for (unsigned int j = 0; j < dataSize; ++j) {
          const unsigned int byte = i * dataSize + j;
          data[i] |= (scml::convert<unsigned char, typename IF::data_type>(dataPtr[byte]) << (j * 8));
        }
      }
    }
    // forward request
    typename IF::response_type resp = pOut->transport(req);
    // FIXME: latency
    if (trans.is_read()) {
      for (unsigned int i = 0; i < req.getBurstCount(); ++i) {
        for (unsigned int j = 0; j < dataSize; ++j) {
          const unsigned int byte = i * dataSize + j;
          dataPtr[byte] = scml::convert<typename IF::data_type, unsigned char>(data[i] >> (j * 8));
        }
      }
    }
    if (resp.getResponse() == pvOk) {
      trans.set_response_status(tlm::TLM_OK_RESPONSE);

    } else {
      trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    }
    trans.set_dmi_allowed(true);
    getReqPool<typename IF::request_type>().release(&req);
  }
}

template <typename IF>
void
scml_tlm2_target_adaptor_base::
unrollTransaction(tlm::tlm_generic_payload& trans, bool isDebug)
{
  // unroll into byte accesses
  typename IF::request_type& req =
    *getReqPool<typename IF::request_type>().claim();
  req.setDataSize(8);   
  req.setOffset(0);
  req.setBurstCount(1);
  req.setBurstType(pvIncr);
  req.setThreadID(0);
  req.setMode(isDebug ? pvDebug : pvDefault);
  // FIXME: extensions

  typename IF::data_type data;
  if (trans.is_read()) {
    req.setWriteDataSource(0);
    req.setReadDataDestination(&data);
    req.setType(pvRead);

  } else {
    req.setWriteDataSource(&data);
    req.setReadDataDestination(0);
    req.setType(pvWrite);
  }

  unsigned char* dataPtr = trans.get_data_ptr();
  tlm::tlm_response_status responseStatus = tlm::TLM_OK_RESPONSE;
  const unsigned int length = trans.get_byte_enable_length() ?
                                trans.get_byte_enable_length() :
                                trans.get_data_length();
  // streaming width ignored for debug
  const unsigned int streamingWidth =
    isDebug ? trans.get_data_length() : trans.get_streaming_width();
  const unsigned int busWidth = (mBusWidth + 7) / 8;
  for (unsigned int i = 0; i < trans.get_data_length(); ++i) {
    if (isDebug ||  // byte enables ignored for debug
        !trans.get_byte_enable_ptr() ||
        trans.get_byte_enable_ptr()[i % length]) {

      assert(streamingWidth);
      if (mHasHostEndianness) {
        req.setAddress(trans.get_address() + i % streamingWidth);

      } else {
        req.setAddress((trans.get_address() + i % streamingWidth) ^ (busWidth - 1));
      }

      if (trans.is_write()) {
        data = scml::convert<unsigned char, typename IF::data_type>(dataPtr[i]);
      }
      // forward request
      typename IF::response_type resp = pOut->transport(req);
      // FIXME: latency
      if (trans.is_read()) {
        dataPtr[i] = scml::convert<typename IF::data_type, unsigned char>(data);
      }
      if (resp.getResponse() != pvOk) {
        responseStatus = tlm::TLM_GENERIC_ERROR_RESPONSE;
      }
    }
  }
  trans.set_response_status(responseStatus);
  trans.set_dmi_allowed(true);
  getReqPool<typename IF::request_type>().release(&req);
}

bool
scml_tlm2_target_adaptor_base::
forwardDMIRequest(tlm::tlm_generic_payload& trans, tlm::tlm_dmi&  dmi_data)
{
    dmi_data.set_start_address(0);
    dmi_data.set_end_address((uint64)-1);
    return false;

}
