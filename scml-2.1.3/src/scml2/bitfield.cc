/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/bitfield.h>

#include <scml2/bitfield_default_read_callback.h>
#include <scml2/bitfield_default_write_callback.h>
#include <scml2/bitfield_default_debug_read_callback.h>
#include <scml2/bitfield_default_debug_write_callback.h>
#include <scml2/bitfield_read_callback_base.h>
#include <scml2/bitfield_write_callback_base.h>
#include <scml2/bitfield_debug_write_callback_base.h>
#include <scml2/bitfield_debug_read_callback_base.h>

#include <cassert>

namespace scml2 {

template <typename DT>
bitfield<DT>::
bitfield(const std::string& name,
         reg<DT>& r,
         unsigned int offset,
         unsigned int size) :
  bitfield_base(name, offset, size, r.get_streams()),
  mRegister(r)
{
  mDefaultReadCallback = new bitfield_default_read_callback<DT>(*this);
  mDefaultReadCallback->ref();
  mReadCallback = mDefaultReadCallback;
  mReadCallback->ref();

  mDefaultWriteCallback = new bitfield_default_write_callback<DT>(*this);
  mDefaultWriteCallback->ref();
  mWriteCallback = mDefaultWriteCallback;
  mWriteCallback->ref();

  mDefaultDebugReadCallback = new bitfield_default_debug_read_callback<DT>(*this);
  mDefaultDebugReadCallback->ref();
  mDebugReadCallback = mDefaultDebugReadCallback;
  mDebugReadCallback->ref();

  mDefaultDebugWriteCallback = new bitfield_default_debug_write_callback<DT>(*this);
  mDefaultDebugWriteCallback->ref();
  mDebugWriteCallback = mDefaultDebugWriteCallback;
  mDebugWriteCallback->ref();

  mRegister.register_bitfield(*this);
}

template <typename DT>
bitfield<DT>::
~bitfield()
{
  mDefaultReadCallback->unref();
  mDefaultWriteCallback->unref();
  mDefaultDebugReadCallback->unref();
  mDefaultDebugWriteCallback->unref();
  mReadCallback->unref();
  mWriteCallback->unref();
  mDebugReadCallback->unref();
  mDebugWriteCallback->unref();
}

template <typename DT>
bool
bitfield<DT>::
set_symbolic_name(const DT& value, const std::string& name)
{
  std::vector<unsigned char> tmp(sizeOf<DT>());
  to_char_array(value, &tmp[0], sizeOf<DT>(), 0);
  return set_symbolic_name(tmp, name);
}

template <typename DT>
void
bitfield<DT>::
do_set_read_callback(bitfield_read_callback_base<DT>* cb)
{
  assert(mReadCallback);
  assert(cb);
  mReadCallback->unref();
  mReadCallback = cb;
  mReadCallback->ref();
}

template <typename DT>
void
bitfield<DT>::
do_set_write_callback(bitfield_write_callback_base<DT>* cb)
{
  assert(mWriteCallback);
  assert(cb);
  mWriteCallback->unref();
  mWriteCallback = cb;
  mWriteCallback->ref();
}

template <typename DT>
void
bitfield<DT>::
do_set_debug_read_callback(bitfield_debug_read_callback_base<DT>* cb)
{
  assert(mDebugReadCallback);
  assert(cb);
  mDebugReadCallback->unref();
  mDebugReadCallback = cb;
  mDebugReadCallback->ref();
}

template <typename DT>
void
bitfield<DT>::
do_set_debug_write_callback(bitfield_debug_write_callback_base<DT>* cb)
{
  assert(mDebugWriteCallback);
  assert(cb);
  mDebugWriteCallback->unref();
  mDebugWriteCallback = cb;
  mDebugWriteCallback->ref();
}

template <typename DT>
void
bitfield<DT>::
set_read_callback(bitfield_read_callback_base<DT>* cb)
{
  assert(cb);
  scoped_reference<bitfield_read_callback_base<DT> > scopedRef(cb);
  if (has_default_read_behavior()) {
    mRegister.bitfield_read_callback_registered();
  }
  do_set_read_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_READ, ACCESS_MODE_REGULAR);
}

template <typename DT>
void
bitfield<DT>::
set_write_callback(bitfield_write_callback_base<DT>* cb)
{
  assert(cb);
  scoped_reference<bitfield_write_callback_base<DT> > scopedRef(cb);
  if (has_default_write_behavior()) {
    mRegister.bitfield_write_callback_registered();
  }
  do_set_write_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_WRITE, ACCESS_MODE_REGULAR);
}

template <typename DT>
void
bitfield<DT>::
remove_callback()
{
  remove_read_callback();
  remove_write_callback();
}

template <typename DT>
void
bitfield<DT>::
remove_read_callback()
{
  if (!has_default_read_behavior()) {
    scoped_reference<bitfield_read_callback_base<DT> > scopedRef(mDefaultReadCallback);
    do_set_read_callback(mDefaultReadCallback);
    mRegister.bitfield_read_callback_unregistered();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_READ, ACCESS_MODE_REGULAR);
  }
}

template <typename DT>
void
bitfield<DT>::
remove_write_callback()
{
  if (!has_default_write_behavior()) {
    scoped_reference<bitfield_write_callback_base<DT> > scopedRef(mDefaultWriteCallback);
    do_set_write_callback(mDefaultWriteCallback);
    mRegister.bitfield_write_callback_unregistered();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_WRITE, ACCESS_MODE_REGULAR);
  }
}

template <typename DT>
bitfield_read_callback_base<DT>*
bitfield<DT>::
get_read_callback() const
{
  return mReadCallback;
}

template <typename DT>
bitfield_write_callback_base<DT>*
bitfield<DT>::
get_write_callback() const
{
  return mWriteCallback;
}

template <typename DT>
void
bitfield<DT>::
set_debug_read_callback(bitfield_debug_read_callback_base<DT>* cb)
{
  assert(cb);
  scoped_reference<bitfield_debug_read_callback_base<DT> > scopedRef(cb);
  if (has_default_debug_read_behavior()) {
    mRegister.bitfield_debug_read_callback_registered();
  }
  do_set_debug_read_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_READ, ACCESS_MODE_DEBUG);
}

template <typename DT>
void
bitfield<DT>::
set_debug_write_callback(bitfield_debug_write_callback_base<DT>* cb)
{
  assert(cb);
  scoped_reference<bitfield_debug_write_callback_base<DT> > scopedRef(cb);
  if (has_default_debug_write_behavior()) {
    mRegister.bitfield_debug_write_callback_registered();
  }
  do_set_debug_write_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_WRITE, ACCESS_MODE_DEBUG);
}

template <typename DT>
void
bitfield<DT>::
remove_debug_callback()
{
  remove_debug_read_callback();
  remove_debug_write_callback();
}

template <typename DT>
void
bitfield<DT>::
remove_debug_read_callback()
{
  if (!has_default_debug_read_behavior()) {
    scoped_reference<bitfield_debug_read_callback_base<DT> > scopedRef(mDefaultDebugReadCallback);
    do_set_debug_read_callback(mDefaultDebugReadCallback);
    mRegister.bitfield_debug_read_callback_unregistered();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_READ, ACCESS_MODE_DEBUG);
  }
}

template <typename DT>
void
bitfield<DT>::
remove_debug_write_callback()
{
  if (!has_default_debug_write_behavior()) {
    scoped_reference<bitfield_debug_write_callback_base<DT> > scopedRef(mDefaultDebugWriteCallback);
    do_set_debug_write_callback(mDefaultDebugWriteCallback);
    mRegister.bitfield_debug_write_callback_unregistered();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_WRITE, ACCESS_MODE_DEBUG);
  }
}

template <typename DT>
bitfield_debug_read_callback_base<DT>*
bitfield<DT>::
get_debug_read_callback() const
{
  return mDebugReadCallback;
}

template <typename DT>
bitfield_debug_write_callback_base<DT>*
bitfield<DT>::
get_debug_write_callback() const
{
  return mDebugWriteCallback;
}

template <typename DT>
bool
bitfield<DT>::
register_callback_observer(bitfield_callback_observer<DT>* o)
{
  return mCallbackObservers.register_observer(o);
}

template <typename DT>
bool
bitfield<DT>::
unregister_all_callback_observers()
{
  return mCallbackObservers.unregister_all_observers();
}

template <typename DT>
bool
bitfield<DT>::
unregister_callback_observer(bitfield_callback_observer<DT>* o)
{
  return mCallbackObservers.unregister_observer(o);
}

template <typename DT>
const char*
bitfield<DT>::
kind() const
{
  return "scml2::bitfield";
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class bitfield<type >;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
