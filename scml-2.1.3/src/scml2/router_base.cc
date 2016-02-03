/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/router_base.h>
#include <scml2/mapped_range.h>
#include <scml2/mappable_if.h>
#include <scml2/router_null_callback.h>
#include <scml2/router_null_debug_callback.h>
#include <scml2/router_callback_base.h>
#include <scml2/router_debug_callback_base.h>
#include <scml2/timing_annotation_registry.h>
#include <scml2/callback_observers.h>
#include <scml2/streams.h>
#include <scml2/utils.h>
#include <scml2/types.h>

#include <systemc>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <limits>

namespace scml2 {

router_base::PostConstructorCallback router_base::mPostConstructorCallback = 0;

void
router_base::
set_post_constructor_callback(PostConstructorCallback c)
{
  assert(!mPostConstructorCallback);
  mPostConstructorCallback = c;
}

router_base::
router_base(const std::string& name,
            unsigned long long size,
            unsigned int width) :
  memory_region(name, 0ull, size, width),
  burst_unroller(width),
  debug_burst_unroller(width),
  mTheStreams(new streams(get_name())),
  mDmiPointersInUse(false),
  mDmiEnabled(true)
{
  init_streams(*mTheStreams);

  mCallback = new router_null_callback(*this);
  mCallback->ref();
  mDebugCallback = new router_null_debug_callback();
  mDebugCallback->ref();

  if (mPostConstructorCallback) {
    mPostConstructorCallback(*this);
  }
}

router_base::
~router_base()
{
  mCallback->unref();
  mDebugCallback->unref();

  // Delete read ranges
  MappedRangesIter it = mMappedReadRanges.begin();
  MappedRangesConstIter end = mMappedReadRanges.end();
  for (; it != end; ++it) {
    delete *it;
  }
  mMappedReadRanges.clear();

  // Delete write ranges
  it = mMappedWriteRanges.begin();
  end = mMappedWriteRanges.end();
  for (; it != end; ++it) {
    delete *it;
  }
  mMappedWriteRanges.clear();

  delete mTheStreams;
}

void
router_base::
invalidate_dmi()
{
  if (mDmiPointersInUse) {
    invalidate_direct_mem_ptr(0, index_to_address(get_size(), get_width()) - 1);
    mDmiPointersInUse = false;
  }
}

void
router_base::
process_unrolled_transaction(tlm::tlm_generic_payload& trans,
                             sc_core::sc_time& t)
{
  b_transport(trans, t);
}

unsigned int
router_base::
process_unrolled_debug_transaction(tlm::tlm_generic_payload& trans)
{
  return transport_dbg(trans);
}

bool
router_base::
checkRange(unsigned long long base, unsigned long long size) const
{
  // Base address must be aligned on width
  if (base % get_width()) {
    return false;
  }

  // Mapped size must be a multiple of width
  if (size % get_width()) {
    return false;
  }

  // Mapped size must fit into size of router object
  if ((base + size) > index_to_address(get_size(), get_width())) {
    return false;
  }

  return true;
}

bool
router_base::
checkOverlap(unsigned long long base, unsigned long long size) const
{
  return checkOverlap(mMappedReadRanges, base, size) ||
         checkOverlap(mMappedWriteRanges, base, size);
}

bool
router_base::
checkOverlap(const MappedRanges& ranges,
             unsigned long long base,
             unsigned long long size) const
{
  MappedRangesConstIter it = ranges.begin();
  MappedRangesConstIter end = ranges.end();

  for (; it != end; ++it) {
    const mapped_range* range = *it;
    const unsigned long long iterLow = range->get_base();
    const unsigned long long iterHigh = range->get_base() + (range->get_size() - 1);
    const unsigned long long low = base;
    const unsigned long long high = base + (size - 1);
    if ((iterLow <= high) && (iterHigh >= low)) {
      return true;
    }
  }

  return false;
}

bool
router_base::
unmap(MappedRanges& ranges, unsigned long long base)
{
  MappedRangesIter it = ranges.begin();
  MappedRangesConstIter end = ranges.end();

  for (; it != end; ++it) {
    mapped_range* range = *it;
    if (range->get_base() == base) {
      delete range;
      ranges.erase(it);
      invalidate_dmi();
      // FIXME: unregister bw interface if needed (if last range mapped to this dest)
      return true;
    }
  }
  return false;
}


bool
router_base::
map(unsigned long long base,
    unsigned long long size,
    mappable_if& dest,
    unsigned long long offset)
{
  if (!checkRange(base, size) || checkOverlap(base, size)) {
    return false;
  }

  dest.register_bw_direct_mem_if(this);
  mMappedReadRanges.insert(mMappedReadRanges.begin(), new mapped_range(base, size, dest, offset));
  mMappedWriteRanges.insert(mMappedWriteRanges.begin(), new mapped_range(base, size, dest, offset));
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return true;
}

bool
router_base::
map_read(unsigned long long base,
         unsigned long long size,
         mappable_if& dest,
         unsigned long long offset)
{
  if (!checkRange(base, size) || checkOverlap(mMappedReadRanges, base, size)) {
    return false;
  }

  dest.register_bw_direct_mem_if(this);
  mMappedReadRanges.insert(mMappedReadRanges.begin(), new mapped_range(base, size, dest, offset));
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return true;
}

bool
router_base::
map_write(unsigned long long base,
          unsigned long long size,
          mappable_if& dest,
          unsigned long long offset)
{
  if (!checkRange(base, size) || checkOverlap(mMappedWriteRanges, base, size)) {
    return false;
  }

  dest.register_bw_direct_mem_if(this);
  mMappedWriteRanges.insert(mMappedWriteRanges.begin(), new mapped_range(base, size, dest, offset));
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return true;
}

bool
router_base::
unmap(unsigned long long base)
{
  bool r = unmap(mMappedReadRanges, base);
  bool w = unmap(mMappedWriteRanges, base);
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return r || w;
}

bool
router_base::
unmap_read(unsigned long long base)
{
  if (unmap(mMappedReadRanges, base)) {
    mMappedRangesObservers.notify_mapped_ranges_changed();
    return true;
  }
  return false;
}

bool
router_base::
unmap_write(unsigned long long base)
{
  if (unmap(mMappedWriteRanges, base)) {
    mMappedRangesObservers.notify_mapped_ranges_changed();
    return true;
  }
  return false;
}

void
router_base::
unmap_all()
{
  if (mMappedReadRanges.empty() && mMappedWriteRanges.empty()) {
    return;
  }

  // Read
  MappedRangesIter it = mMappedReadRanges.begin();
  MappedRangesConstIter end = mMappedReadRanges.end();
  for (; it != end; ++it) {
    (*it)->unregister_bw_direct_mem_if(this);
    delete *it;
  }
  mMappedReadRanges.clear();

  // Write
  it = mMappedWriteRanges.begin();
  end = mMappedWriteRanges.end();
  for (; it != end; ++it) {
    (*it)->unregister_bw_direct_mem_if(this);
    delete *it;
  }
  mMappedWriteRanges.clear();

  invalidate_dmi();
  mMappedRangesObservers.notify_mapped_ranges_changed();
}

mapped_range*
router_base::
getMappedRange(MappedRanges& ranges, unsigned long long address)
{
  MappedRangesIter it = ranges.begin();
  MappedRangesConstIter end = ranges.end();

  for (; it != end; ++it) {
    mapped_range* range = *it;
    if (range->contains(address)) {
      // Keep mapped ranges in MRU order
      if (it != ranges.begin()) {
        ranges.push_front(*it);
        ranges.erase(it);
      }
      return range;
    }
  }

  return 0;
}

unsigned int
router_base::
collect_mapped_read_ranges(std::vector<mapped_range*>& v) const
{
  v.clear();
  std::copy(mMappedReadRanges.begin(),
            mMappedReadRanges.end(),
            std::back_insert_iterator<std::vector<mapped_range*> >(v));
  size_t size = mMappedReadRanges.size();
  assert( size < std::numeric_limits<unsigned int>::max());
  return (unsigned int)size;
}

mapped_range*
router_base::
get_mapped_read_range(unsigned long long address) const
{
  return getMappedRange(mMappedReadRanges, address);
}

unsigned int
router_base::
collect_mapped_write_ranges(std::vector<mapped_range*>& v) const
{
  v.clear();
  std::copy(mMappedWriteRanges.begin(),
            mMappedWriteRanges.end(),
            std::back_insert_iterator<std::vector<mapped_range*> >(v));
  size_t size = mMappedWriteRanges.size();
  assert( size < std::numeric_limits<unsigned int>::max());
  return (unsigned int)size;
}

mapped_range*
router_base::
get_mapped_write_range(unsigned long long address) const
{
  return getMappedRange(mMappedWriteRanges, address);
}

void
router_base::
set_callback(router_callback_base* cb)
{
  assert(mCallback);
  assert(cb);
  mCallback->unref();
  mCallback = cb;
  mCallback->ref();
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_ACCESS, ACCESS_MODE_REGULAR);
}

void
router_base::
set_debug_callback(router_debug_callback_base* cb)
{
  assert(mDebugCallback);
  assert(cb);
  mDebugCallback->unref();
  mDebugCallback = cb;
  mDebugCallback->ref();
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_ACCESS, ACCESS_MODE_DEBUG);
}

router_callback_base*
router_base::
get_callback() const
{
  return mCallback;
}

router_debug_callback_base*
router_base::
get_debug_callback() const
{
  return mDebugCallback;
}

std::string
router_base::
get_mapped_name() const
{
  return get_name();
}

void
router_base::
b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  timing_annotation_registry::get_instance().register_timing_annotation(t);

  const unsigned long long address = trans.get_address();
  const unsigned long long lowIndex = address_to_index(address, get_width());
  const unsigned long long endAddress =
      address + std::min(trans.get_data_length(), trans.get_streaming_width()) - 1;
  const unsigned long long highIndex = address_to_index(endAddress, get_width());

  MappedRanges& ranges = (trans.is_read() ? mMappedReadRanges : mMappedWriteRanges);
  mapped_range* range = getMappedRange(ranges, address);

  if (range) {
    if ((lowIndex != highIndex) && !range->contains(endAddress)) {
      unroll_transaction(trans, t);

    } else {
      trans.set_address(range->mapped_address(address));
      range->b_transport(trans, t);
      trans.set_address(address);
    }

  } else {
    if (highIndex >= get_size()) {
      trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);

    } else {
      assert(mCallback);
      unsigned int id =
        mCallbackObservers.notify_begin(trans, ACCESS_MODE_REGULAR);
      mCallback->execute(trans, t);
      mCallbackObservers.notify_end(trans, id);
    }
  }

  timing_annotation_registry::get_instance().unregister_timing_annotation();
}

bool
router_base::
get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData)
{
  const unsigned long long address = trans.get_address();

  mDmiPointersInUse = true;

  if (!is_dmi_enabled()) {
    dmiData.set_start_address(0);
    dmiData.set_end_address((unsigned long long)-1);
    dmiData.allow_read_write();
    return false;
  }

  unsigned long long startAddress = 0;
  unsigned long long endAddress = index_to_address(get_size(), get_width()) - 1;

  if (trans.is_read()) {
    dmiData.allow_read();

  } else {
    dmiData.allow_write();
  }

  if (address > endAddress) {
    dmiData.set_start_address(endAddress + 1);
    dmiData.set_end_address((unsigned long long)-1);
    return false;
  }

  MappedRanges& ranges = (trans.is_read() ? mMappedReadRanges : mMappedWriteRanges);
  MappedRangesIter rangeIter = ranges.begin();
  MappedRangesConstIter end = ranges.end();

  for (; rangeIter != end; ++rangeIter) {
    // invariant: address always lies in [low..high]
    assert((address >= startAddress && address <= endAddress));

    mapped_range* range = *rangeIter;
    if(range->contains(address)) {
      trans.set_address(range->mapped_address(address));
      bool result = range->get_direct_mem_ptr(trans, dmiData);
      trans.set_address(address);

      const unsigned long long mappedStartAddress = range->mapped_address(range->get_base());
      if (dmiData.get_start_address() < mappedStartAddress) {
        dmiData.set_dmi_ptr(dmiData.get_dmi_ptr() + mappedStartAddress - dmiData.get_start_address());
        dmiData.set_start_address(range->unmapped_address(mappedStartAddress));

      } else {
        dmiData.set_start_address(range->unmapped_address(dmiData.get_start_address()));
      }

      const unsigned long long mappedEndAddress = range->mapped_address(range->get_base() + range->get_size() - 1);
      if (dmiData.get_end_address() > mappedEndAddress) {
        dmiData.set_end_address(range->unmapped_address(mappedEndAddress));

      } else {
        dmiData.set_end_address(range->unmapped_address(dmiData.get_end_address()));
      }

      return result;

    } else if (address < range->get_base()) {
      if (range->get_base() <= endAddress) {
        endAddress = range->get_base() - 1;
      }

    } else { // address >= range->get_base() + range->get_size()
      unsigned long long nextStartAddress = range->get_base() + range->get_size();
      if (nextStartAddress > startAddress) {
        startAddress = nextStartAddress;
      }
    }
  }

  dmiData.set_start_address(startAddress);
  dmiData.set_end_address(endAddress);
  return false;
}

unsigned int
router_base::
transport_dbg(tlm::tlm_generic_payload& trans)
{
  const unsigned long long address = trans.get_address();
  const unsigned long long lowIndex = address_to_index(address, get_width());
  const unsigned long long endAddress = address + trans.get_data_length() - 1;
  const unsigned long long highIndex = address_to_index(endAddress, get_width());

  MappedRanges& ranges = (trans.is_read() ? mMappedReadRanges : mMappedWriteRanges);
  mapped_range* range = getMappedRange(ranges, address);

  if (range) {
    if ((lowIndex != highIndex) && !range->contains(endAddress)) {
      return unroll_debug_transaction(trans);

    } else {
      trans.set_address(range->mapped_address(address));
      unsigned int result = range->transport_dbg(trans);
      trans.set_address(address);
      return result;
    }

  } else {
    if (highIndex >= get_size()) {
      return 0;

    } else {
      assert(mDebugCallback);
      unsigned int id =
        mCallbackObservers.notify_begin(trans, ACCESS_MODE_DEBUG);
      unsigned int result = mDebugCallback->execute(trans);
      mCallbackObservers.notify_end(trans, id);
      return result;
    }
  }
}

void
router_base::
register_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  assert(bwInterface);
  mBwDirectMemIfs.insert(bwInterface);
}

void
router_base::
unregister_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  mBwDirectMemIfs.erase(bwInterface);
}

void
router_base::
invalidate_direct_mem_ptr(unsigned long long startRange,
                          unsigned long long endRange)
{
  // FIXME: only invalidate if something is mapped to this range?
  std::set<tlm::tlm_bw_direct_mem_if*>::iterator it = mBwDirectMemIfs.begin();
  std::set<tlm::tlm_bw_direct_mem_if*>::const_iterator end = mBwDirectMemIfs.end();
  for (; it != end; ++it) {
    (*it)->invalidate_direct_mem_ptr(startRange, endRange);
  }
}

unsigned int
router_base::
read(unsigned long long address,
     unsigned char* data,
     unsigned int size)
{
  return get_debug_with_triggering_callbacks(address, data, size);
}

unsigned int
router_base::
write(unsigned long long address,
      const unsigned char* data,
      unsigned int size)
{
  return put_debug_with_triggering_callbacks(address, data, size);
}

void
router_base::
enable_dmi()
{
  if (!is_dmi_enabled()) {
    invalidate_dmi();
    mDmiEnabled = true;
  }
}

void
router_base::
disable_dmi()
{
  if (is_dmi_enabled()) {
    invalidate_dmi();
    mDmiEnabled = false;
  }
}

bool
router_base::
is_dmi_enabled() const
{
  return mDmiEnabled;
}

bool
router_base::
register_mapped_ranges_observer(mapped_ranges_observer* o)
{
  return mMappedRangesObservers.register_observer(o);
}

bool
router_base::
unregister_all_mapped_ranges_observers()
{
  return mMappedRangesObservers.unregister_all_observers();
}

bool
router_base::
unregister_mapped_ranges_observer(mapped_ranges_observer* o)
{
  return mMappedRangesObservers.unregister_observer(o);
}

const char*
router_base::
kind() const
{
  return "scml2::router";
}

}
