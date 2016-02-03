/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/toplevel_memory_base.h>

#include <scml2/burst_unroller.h>
#include <scml2/memory_storage_base.h>
#include <scml2/timing_annotation_registry.h>
#include <scml2/find_alias.h>
#include <scml2/utils.h>

#include <tlm.h>
#include <algorithm>
#include <cstring>
#include <cassert>

namespace scml2 {

toplevel_memory_base::
toplevel_memory_base(const std::string& name,
                     unsigned long long size,
                     unsigned int width) :
  memory_base(name, 0, 0ull, size, width),
  burst_unroller(width),
  debug_burst_unroller(width),
  mTheStreams(new streams(get_name())),
  mStorage(0),
  mReadLatency(sc_core::SC_ZERO_TIME),
  mWriteLatency(sc_core::SC_ZERO_TIME),
  mReadDmiData(size),
  mWriteDmiData(size),
  mDmiPointersInUse(false),
  mDelStorageOnDestruction(false)
{
  init_streams(*mTheStreams);
}

toplevel_memory_base::
~toplevel_memory_base()
{
  if (mDelStorageOnDestruction) {
    delete mStorage;
  }
  delete mTheStreams;
}

void
toplevel_memory_base::
set_storage(memory_storage_base* storage, bool deleteInDestructor)
{
  assert(!mStorage);
  mStorage = storage;
  mDelStorageOnDestruction = deleteInDestructor;
}

void
toplevel_memory_base::
register_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  assert(bwInterface);
  mBwDirectMemIfs.insert(bwInterface);
}

void
toplevel_memory_base::
unregister_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  mBwDirectMemIfs.erase(bwInterface);
}

void
toplevel_memory_base::
invalidate_dmi()
{
  if (mDmiPointersInUse) {
    std::set<tlm::tlm_bw_direct_mem_if*>::iterator it = mBwDirectMemIfs.begin();
    std::set<tlm::tlm_bw_direct_mem_if*>::const_iterator end = mBwDirectMemIfs.end();
    for (; it != end; ++it) {
      (*it)->invalidate_direct_mem_ptr(0, index_to_address(get_size(), get_width()) - 1);
    }
    mDmiPointersInUse = false;
  }
}

std::string
toplevel_memory_base::
get_mapped_name() const
{
  return get_name();
}

void
toplevel_memory_base::
process_unrolled_transaction(tlm::tlm_generic_payload& trans,
                             sc_core::sc_time& t)
{
  b_transport(trans, t);
}

unsigned int
toplevel_memory_base::
process_unrolled_debug_transaction(tlm::tlm_generic_payload& trans)
{
  return transport_dbg(trans);
}

void
toplevel_memory_base::
b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  const unsigned long long address = trans.get_address();
  const unsigned long long lowIndex = address_to_index(address, get_width());
  const unsigned long long highIndex =
    address_to_index(
      address + std::min(trans.get_data_length(), trans.get_streaming_width()) - 1,
      get_width());

  memory_base* alias =
    trans.is_read() ? find_alias(*this,
                                 lowIndex,
                                 highIndex,
                                 HasNonDefaultReadBehavior()) :
                      find_alias(*this,
                                 lowIndex,
                                 highIndex,
                                 HasNonDefaultWriteBehavior());
  if (!alias) {
    if (lowIndex != highIndex) {
      unroll_transaction(trans, t);

    } else {
      trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
    }

  } else {
    trans.set_address(address - index_to_address(alias->get_offset(), get_width()));

    if ((!alias->has_default_read_behavior() && trans.is_read()) ||
        (!alias->has_default_write_behavior() && trans.is_write()) ||
        mContentObservers.has_observers() ||
        mCallbackObservers.has_observers()) {
      timing_annotation_registry::get_instance().register_timing_annotation(t);
      alias->execute_behavior(trans, t);
      timing_annotation_registry::get_instance().unregister_timing_annotation();

    } else {
      alias->execute_behavior(trans, t);
    }

    trans.set_address(address);
  }

  trans.set_dmi_allowed(true);

}

void
toplevel_memory_base::
addReadDmiData(memory_base* alias)
{
  assert(alias->get_parent());
  if (alias->is_dmi_read_allowed()) {
    AliasesConstIterator it = alias->begin_alias();
    AliasesConstIterator end = alias->end_alias();
    for (; it != end; ++it) {
      addReadDmiData(*it);
    }

  } else {
    mReadDmiData.disable(alias->get_offset(),
                         alias->get_offset() + alias->get_size() - 1);
  }
}

void
toplevel_memory_base::
addWriteDmiData(memory_base* alias)
{
  assert(alias->get_parent());
  if (alias->is_dmi_write_allowed()) {
    AliasesConstIterator it = alias->begin_alias();
    AliasesConstIterator end = alias->end_alias();
    for (; it != end; ++it) {
      addWriteDmiData(*it);
    }

  } else {
    mWriteDmiData.disable(alias->get_offset(),
                          alias->get_offset() + alias->get_size() - 1);
  }
}

void
toplevel_memory_base::
addDmiData(memory_base* alias)
{
  if (alias->is_dmi_allowed()) {
    AliasesConstIterator it = alias->begin_alias();
    AliasesConstIterator end = alias->end_alias();

    for (; it != end; ++it) {
      addDmiData(*it);
    }

  } else if (alias->is_dmi_read_allowed()) {
    mWriteDmiData.disable(alias->get_offset(),
                          alias->get_offset() + alias->get_size() - 1);

    AliasesConstIterator it = alias->begin_alias();
    AliasesConstIterator end = alias->end_alias();
    for (; it != end; ++it) {
      addReadDmiData(*it);
    }

  } else if (alias->is_dmi_write_allowed()) {
    mReadDmiData.disable(alias->get_offset(),
                         alias->get_offset() + alias->get_size() - 1);

    AliasesConstIterator it = alias->begin_alias();
    AliasesConstIterator end = alias->end_alias();
    for (; it != end; ++it) {
      addWriteDmiData(*it);
    }

  } else {
    unsigned long long startIndex = alias->get_offset();
    unsigned long long endIndex = alias->get_offset() + alias->get_size() - 1;
    mReadDmiData.disable(startIndex, endIndex);
    mWriteDmiData.disable(startIndex, endIndex);
  }
}

bool
toplevel_memory_base::
get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
  const unsigned long long address = trans.get_address();

  if (!mDmiPointersInUse) {
    mReadDmiData.clear();
    mWriteDmiData.clear();

    if (is_dmi_enabled()) {
      addDmiData(this);
      mContentObservers.disable_dmi(mReadDmiData, mWriteDmiData);

    } else {
      mReadDmiData.disable();
      mWriteDmiData.disable();
    }

    mDmiPointersInUse = true;
  }

  const unsigned long long index = address_to_index(address, get_width());
  const memory_dmi::DmiDataEntry& dmiData =
   trans.is_read() ? mReadDmiData.find(index) :
                     mWriteDmiData.find(index);

  dmi_data.set_start_address(index_to_address(dmiData.startIndex, get_width()));
  dmi_data.set_end_address(index_to_address(dmiData.endIndex, get_width()) + get_width() - 1);
  if (trans.is_read()) {
    dmi_data.allow_read();
    dmi_data.set_read_latency(get_default_read_latency());

  } else {
    dmi_data.allow_write();
    dmi_data.set_write_latency(get_default_write_latency());
  }

  if (dmiData.dmiAllowed) {
    assert(mStorage);
    unsigned char* fastBackdoor = mStorage->get_fast_backdoor();
    if (fastBackdoor) {
      dmi_data.set_dmi_ptr(fastBackdoor + dmi_data.get_start_address());
      return true;

    } else {
      memory_storage_base::fast_backdoor_region region =
        mStorage->get_fast_backdoor(address);
      if (region.fastBackdoor) {
        if (region.startAddress > dmi_data.get_start_address()) {
          dmi_data.set_start_address(region.startAddress);
        }
        if (region.endAddress < dmi_data.get_end_address()) {
          dmi_data.set_end_address(region.endAddress);
        }
        dmi_data.set_dmi_ptr(region.fastBackdoor -
                             region.startAddress +
                             dmi_data.get_start_address());
        return true;
      }
    }
  }

  return false;
}

unsigned int
toplevel_memory_base::
transport_dbg(tlm::tlm_generic_payload& trans)
{
  const unsigned long long address = trans.get_address();
  const unsigned long long lowIndex = address_to_index(address, get_width());
  const unsigned long long highIndex =
    address_to_index(address + trans.get_data_length() - 1, get_width());

  memory_base* alias =
    trans.is_read() ? find_alias(*this,
                                 lowIndex,
                                 highIndex,
                                 HasNonDefaultDebugReadBehavior()) :
                      find_alias(*this,
                                 lowIndex,
                                 highIndex,
                                 HasNonDefaultDebugWriteBehavior());

  trans.set_dmi_allowed(true);

  if (!alias) {
    if (lowIndex != highIndex) {
      return unroll_debug_transaction(trans);

    } else {
      return 0;
    }

  } else {
    trans.set_address(address - index_to_address(alias->get_offset(), get_width()));
    unsigned int result = alias->execute_debug_behavior(trans);
    trans.set_address(address);
    return result;
  }
}

unsigned int
toplevel_memory_base::
read(unsigned long long address,
     unsigned char* data,
     unsigned int size)
{
  size = (unsigned int)std::min<unsigned long long>(size,
						    index_to_address(get_size(),
								     get_width()));
  return get_debug_with_triggering_callbacks(address, data, size);
}

unsigned int
toplevel_memory_base::
write(unsigned long long address,
      const unsigned char* data,
      unsigned int size)
{
  size = (unsigned int)std::min<unsigned long long>(size,
						    index_to_address(get_size(),
								     get_width()));
  return put_debug_with_triggering_callbacks(address, data, size);
}

bool
toplevel_memory_base::
register_content_observer(memory_content_observer* o)
{
  return register_content_observer(o, 0);
}

bool
toplevel_memory_base::
unregister_all_content_observers()
{
  if (mContentObservers.has_observers()) {
    if (mContentObservers.unregister_all_observers()) {
      invalidate_dmi();
      propagate_update_fast_access();
      return true;

    } else {
      return false;
    }
  }

  return true;
}

bool
toplevel_memory_base::
unregister_content_observer(memory_content_observer* o)
{
  bool oldHasObservers = mContentObservers.has_observers();

  if (mContentObservers.unregister_observer(o)) {
    invalidate_dmi();
    if (oldHasObservers != mContentObservers.has_observers()) {
      propagate_update_fast_access();
    }
    return true;
  }

  return false;
}

bool
toplevel_memory_base::
register_content_observer(memory_content_observer* o,
                          unsigned long long offset)
{
  bool oldHasObservers = mContentObservers.has_observers();

  if (mContentObservers.register_observer(o, offset)) {
    invalidate_dmi();
    if (oldHasObservers != mContentObservers.has_observers()) {
      propagate_update_fast_access();
    }
    return true;
  }

  return false;
}

void
toplevel_memory_base::
fast_backdoor_changed()
{
  invalidate_dmi();
  propagate_update_fast_access();
}

const char*
toplevel_memory_base::
kind() const
{
  return "scml2::memory";
}

}
