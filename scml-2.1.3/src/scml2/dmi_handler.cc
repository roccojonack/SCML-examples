/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/dmi_handler.h>
#include <scml2/abstraction_level_switch.h>

#include <scml2_logging/severity.h>

namespace scml2 {

logging::stream
dmi_handler::mError("dmi_handler", logging::severity::error());

dmi_handler::
dmi_handler() :
  mFwDirectMemIf(0),
  mDmiEnabled(true)
{
  abstraction_level_switch::get_instance().register_observer(this);
  invalidate(mReadRanges);
  invalidate(mWriteRanges);
}

dmi_handler::
~dmi_handler()
{
  abstraction_level_switch::get_instance().unregister_observer(this);
}

void
dmi_handler::
set_interface(tlm::tlm_fw_direct_mem_if<tlm::tlm_generic_payload>* ifs)
{
  mFwDirectMemIf = ifs;
}

void
dmi_handler::
invalidate(DmiRanges& ranges)
{
  tlm::tlm_dmi dmiData;
  if (!is_dmi_enabled() ||
      !abstraction_level_switch::get_instance().is_dmi_allowed()) {
    dmiData.set_start_address(0);
    dmiData.set_end_address((unsigned long long)-1);
    dmiData.set_granted_access(tlm::tlm_dmi::DMI_ACCESS_NONE);

  } else {
    dmiData.set_start_address(1);
    dmiData.set_end_address(0);
  }

  ranges.clear();
  ranges.push_front(dmiData);
}

bool
dmi_handler::
get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData)
{
  bool result;
  if (trans.is_read()) {
    dmiData = *get_read_range(trans.get_address());
    result = dmiData.is_read_allowed();
    dmiData.allow_read();

  } else {
    dmiData = *get_write_range(trans.get_address());
    result = dmiData.is_write_allowed();
    dmiData.allow_write();
  }

  return result;
}

void
dmi_handler::
invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64)
{
  invalidate(mReadRanges);
  invalidate(mWriteRanges);
}

void
dmi_handler::
enable_dmi()
{
  if (!is_dmi_enabled()) {
    mDmiEnabled = true;
    invalidate_direct_mem_ptr(0, (unsigned long long)-1);
  }
}

void
dmi_handler::
disable_dmi()
{
  if (is_dmi_enabled()) {
    mDmiEnabled = false;
    invalidate_direct_mem_ptr(0, (unsigned long long)-1);
  }
}

tlm::tlm_dmi*
dmi_handler::
get_read_range_slow(unsigned long long address)
{
  DmiRangesIter it = mReadRanges.begin();
  DmiRangesConstIter end = mReadRanges.end();
  for (; it != end; ++it) {
    if (contains(*it, address)) {
      mReadRanges.push_front(*it);
      mReadRanges.erase(it);
      return &mReadRanges.front();
    }
  }

  return load_range(address, true);
}

tlm::tlm_dmi*
dmi_handler::
get_write_range_slow(unsigned long long address)
{
  DmiRangesIter it = mWriteRanges.begin();
  DmiRangesConstIter end = mWriteRanges.end();
  for (; it != end; ++it) {
    if (contains(*it, address)) {
      mWriteRanges.push_front(*it);
      mWriteRanges.erase(it);
      return &mWriteRanges.front();
    }
  }

  return load_range(address, false);
}

tlm::tlm_dmi*
dmi_handler::
load_range(unsigned long long address, bool readNotWrite)
{
  mTrans.set_address(address);
  mTrans.set_command(readNotWrite ? tlm::TLM_READ_COMMAND : tlm::TLM_WRITE_COMMAND);

  tlm::tlm_dmi dmiData;

  if (!mFwDirectMemIf) {
    SCML2_LOG(mError) << "no 'tlm::tlm_fw_direct_mem_if' set" << std::endl;
  }

  assert(contains(dmiData, address));

  if (!mFwDirectMemIf->get_direct_mem_ptr(mTrans, dmiData)) {
    dmiData.set_granted_access(tlm::tlm_dmi::DMI_ACCESS_NONE);
  }

  if (readNotWrite) {
    mReadRanges.push_front(dmiData);
    return &mReadRanges.front();

  } else {
    mWriteRanges.push_front(dmiData);
    return &mWriteRanges.front();
  }
}

void
dmi_handler::
handle_abstraction_level_switched()
{
  invalidate_direct_mem_ptr(0, (unsigned long long)-1);
}

}
