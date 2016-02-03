/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/reg.h>

#include <scml2/memory_default_callback.h>
#include <scml2/memory_default_debug_callback.h>
#include <scml2/memory_bitfields_read_callback.h>
#include <scml2/memory_bitfields_write_callback.h>
#include <scml2/memory_bitfields_debug_read_callback.h>
#include <scml2/memory_bitfields_debug_write_callback.h>

#include <scml2/bitfield.h>
#include <scml2/memory_alias.h>
#include <scml2/memory.h>

#include <scml2/utils.h>

#include <scml2_logging/stream.h>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <limits>

namespace scml2 {

template <typename DT>
reg<DT>::
reg(const std::string& name,
    memory<DT>& parent,
    unsigned long long offset) :
  memory_base(name, &parent, offset, 1, sizeOf<DT>()),
  mToplevel(parent),
  mFastAccess(),
  mNrOfBitfieldReadCallbacks(0),
  mNrOfBitfieldWriteCallbacks(0),
  mNrOfBitfieldDebugReadCallbacks(0),
  mNrOfBitfieldDebugWriteCallbacks(0)
{
  setup();
}

template <typename DT>
reg<DT>::
reg(const std::string& name,
    memory_alias<DT>& parent,
    unsigned long long offset) :
  memory_base(name, &parent, parent.get_offset() + offset, 1, sizeOf<DT>()),
  mToplevel(parent.mToplevel),
  mFastAccess(),
  mNrOfBitfieldReadCallbacks(0),
  mNrOfBitfieldWriteCallbacks(0),
  mNrOfBitfieldDebugReadCallbacks(0),
  mNrOfBitfieldDebugWriteCallbacks(0)
{
  setup();
}

template <typename DT>
reg<DT>::
~reg()
{
}

template <typename DT>
void
reg<DT>::
initialize(const DT& value)
{
  put_debug(value);
}

template <typename DT>
bool
reg<DT>::
set_symbolic_name(const DT& value, const std::string& name)
{
  std::vector<unsigned char> tmp(sizeOf<DT>());
  to_char_array(value, &tmp[0], sizeOf<DT>(), 0);
  return set_symbolic_name(tmp, name);
}

template <typename DT>
void
reg<DT>::
setup()
{
  init_streams(mToplevel.get_streams());

  init_default_callback(new memory_default_callback<DT>(mFastAccess, mToplevel));
  init_default_debug_callback(new memory_default_debug_callback<DT>(mFastAccess));

  update_fast_access();
}

template <typename DT>
void
reg<DT>::
invalidate_dmi()
{
  mToplevel.invalidate_dmi();
}

template <typename DT>
void
reg<DT>::
update_fast_access()
{
  mFastAccess.update(mToplevel.create_slow_access(get_offset()));
}

template <typename DT>
void
reg<DT>::
set_callback(memory_callback_base* cb)
{
  if (mNrOfBitfieldReadCallbacks || mNrOfBitfieldWriteCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It is not possible to register a callback to '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::set_callback(cb);
  }
}

template <typename DT>
void
reg<DT>::
set_read_callback(memory_callback_base* cb)
{
  if (mNrOfBitfieldReadCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It is not possible to register a callback to '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::set_read_callback(cb);
  }
}

template <typename DT>
void
reg<DT>::
set_write_callback(memory_callback_base* cb)
{
  if (mNrOfBitfieldWriteCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It is not possible to register a callback to '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::set_write_callback(cb);
  }
}

template <typename DT>
void
reg<DT>::
remove_callback()
{
  if (mNrOfBitfieldReadCallbacks || mNrOfBitfieldWriteCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It's not possible to call remove_callback on '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::remove_callback();
  }
}

template <typename DT>
void
reg<DT>::
remove_read_callback()
{
  if (mNrOfBitfieldReadCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It's not possible to call remove_callback on '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::remove_read_callback();
  }
}

template <typename DT>
void
reg<DT>::
remove_write_callback()
{
  if (mNrOfBitfieldWriteCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It's not possible to call remove_callback on '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::remove_write_callback();
  }
}

template <typename DT>
void
reg<DT>::
set_debug_callback(memory_debug_callback_base* cb)
{
  if (mNrOfBitfieldDebugReadCallbacks || mNrOfBitfieldDebugWriteCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It is not possible to register a callback to '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::set_debug_callback(cb);
  }
}

template <typename DT>
void
reg<DT>::
set_debug_read_callback(memory_debug_callback_base* cb)
{
  if (mNrOfBitfieldDebugReadCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It is not possible to register a callback to '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::set_debug_read_callback(cb);
  }
}

template <typename DT>
void
reg<DT>::
set_debug_write_callback(memory_debug_callback_base* cb)
{
  if (mNrOfBitfieldDebugWriteCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It is not possible to register a callback to '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::set_debug_write_callback(cb);
  }
}

template <typename DT>
void
reg<DT>::
remove_debug_callback()
{
  if (mNrOfBitfieldDebugReadCallbacks || mNrOfBitfieldDebugWriteCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It's not possible to call remove_callback on '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::remove_debug_callback();
  }
}

template <typename DT>
void
reg<DT>::
remove_debug_read_callback()
{
  if (mNrOfBitfieldDebugReadCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It's not possible to call remove_callback on '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::remove_debug_read_callback();
  }
}

template <typename DT>
void
reg<DT>::
remove_debug_write_callback()
{
  if (mNrOfBitfieldDebugWriteCallbacks) {
    SCML2_LOG(get_streams().error())
      << "It's not possible to call remove_callback on '"
      << get_name() << "' since there are bitfield callbacks registered."
      << std::endl;

  } else {
    memory_base::remove_debug_write_callback();
  }
}

template <typename DT>
void
reg<DT>::
register_bitfield(bitfield<DT>& bitfield)
{
  if ((bitfield.get_offset() + bitfield.get_size()) > (sizeOf<DT>() * 8)) {
    SCML2_LOG(get_streams().error())
      << "The bitfield '" << bitfield.get_name()
      << "' addresses bits outside the range of the parent reg '"
      << get_name() << "'"
      << std::endl;
  }

  BitfieldsIter it = mBitfields.begin();
  BitfieldsConstIter end = mBitfields.end();
  for (; it != end; ++it) {
    if ((*it)->get_name() == bitfield.get_name()) {
      SCML2_LOG(get_streams().internal_error())
        << "Duplicate bitfield name: '" << bitfield.get_name() << "'"
        << std::endl;
    }

    if ((*it)->get_offset() < (bitfield.get_offset() + bitfield.get_size()) &&
        bitfield.get_offset() < ((*it)->get_offset() + (*it)->get_size())) {
      SCML2_LOG(get_streams().error())
        << "The bitfield '" << bitfield.get_name()
        << "' overlaps with bitfield '" << (*it)->get_name() << "'"
        << std::endl;
    }
  }

  mBitfields.push_back(&bitfield);
}

template <typename DT>
inline
void
reg<DT>::
bitfield_read_callback_registered()
{
  if (mNrOfBitfieldReadCallbacks == 0) {
    if (has_default_read_behavior()) {
      set_read_callback(
        new memory_bitfields_read_callback<DT>(*this, mBitfields));
      ++mNrOfBitfieldReadCallbacks;

    } else {
      SCML2_LOG(get_streams().error())
        << "It is not possible to register bitfield callbacks while there"
        << " is a reg callback registered on '" << get_name() << "'"
        << std::endl;
    }
  }
}

template <typename DT>
inline
void
reg<DT>::
bitfield_write_callback_registered()
{
  if (mNrOfBitfieldWriteCallbacks == 0) {
    if (has_default_write_behavior()) {
      set_write_callback(
        new memory_bitfields_write_callback<DT>(*this, mBitfields));
      ++mNrOfBitfieldWriteCallbacks;

    } else {
      SCML2_LOG(get_streams().error())
        << "It is not possible to register bitfield callbacks while there"
        << " is a reg callback registered on '" << get_name() << "'"
        << std::endl;
    }
  }
}

template <typename DT>
inline
void
reg<DT>::
bitfield_read_callback_unregistered()
{
  if (--mNrOfBitfieldReadCallbacks == 0) {
    assert(!has_default_read_behavior());
    remove_read_callback();
    invalidate_dmi();
  }
}

template <typename DT>
inline
void
reg<DT>::
bitfield_write_callback_unregistered()
{
  if (--mNrOfBitfieldWriteCallbacks == 0) {
    assert(!has_default_write_behavior());
    remove_write_callback();
    invalidate_dmi();
  }
}

template <typename DT>
inline
void
reg<DT>::
bitfield_debug_read_callback_registered()
{
  if (mNrOfBitfieldDebugReadCallbacks == 0) {
    if (has_default_debug_read_behavior()) {
      set_debug_read_callback(
        new memory_bitfields_debug_read_callback<DT>(*this, mBitfields));
      ++mNrOfBitfieldDebugReadCallbacks;

    } else {
      SCML2_LOG(get_streams().error())
        << "It is not possible to register bitfield callbacks while there"
        << " is a reg callback registered on '" << get_name() << "'"
        << std::endl;
    }
  }
}

template <typename DT>
inline
void
reg<DT>::
bitfield_debug_write_callback_registered()
{
  if (mNrOfBitfieldDebugWriteCallbacks == 0) {
    if (has_default_debug_write_behavior()) {
      set_debug_write_callback(
        new memory_bitfields_debug_write_callback<DT>(*this, mBitfields));
      ++mNrOfBitfieldDebugWriteCallbacks;

    } else {
      SCML2_LOG(get_streams().error())
        << "It is not possible to register bitfield callbacks while there"
        << " is a reg callback registered on '" << get_name() << "'"
        << std::endl;
    }
  }
}

template <typename DT>
inline
void
reg<DT>::
bitfield_debug_read_callback_unregistered()
{
  if (--mNrOfBitfieldDebugReadCallbacks == 0) {
    assert(!has_default_debug_read_behavior());
    remove_debug_read_callback();
    invalidate_dmi();
  }
}

template <typename DT>
inline
void
reg<DT>::
bitfield_debug_write_callback_unregistered()
{
  if (--mNrOfBitfieldDebugWriteCallbacks == 0) {
    assert(!has_default_debug_write_behavior());
    remove_debug_write_callback();
    invalidate_dmi();
  }
}

template <typename DT>
unsigned int
reg<DT>::
read(unsigned long long address,
     unsigned char* data,
     unsigned int size)
{
  return mToplevel.read(address + index_to_address<DT>(get_offset()),
                        data,
                        size);
}

template <typename DT>
unsigned int
reg<DT>::
write(unsigned long long address,
      const unsigned char* data,
      unsigned int size)
{
  return mToplevel.write(address + index_to_address<DT>(get_offset()),
                         data,
                         size);
}

template <typename DT>
bool
reg<DT>::
register_content_observer(memory_content_observer* o)
{
  return mToplevel.register_content_observer(o, get_offset());
}

template <typename DT>
bool
reg<DT>::
unregister_all_content_observers()
{
  return mToplevel.unregister_all_content_observers();
}

template <typename DT>
bool
reg<DT>::
unregister_content_observer(memory_content_observer* o)
{
  return mToplevel.unregister_content_observer(o);
}

template <typename DT>
unsigned int
reg<DT>::
collect_bitfields(std::vector<bitfield_base*>& b) const
{
  std::copy(mBitfields.begin(),
            mBitfields.end(),
            std::back_insert_iterator<std::vector<bitfield_base*> >(b));
  size_t size = mBitfields.size();
  assert( size < std::numeric_limits<unsigned int>::max());
  return (unsigned int)size;
}

template <typename DT>
const char*
reg<DT>::
kind() const
{
  return "scml2::reg";
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class reg<type >;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
