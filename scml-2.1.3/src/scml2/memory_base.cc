/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_base.h>
#include <scml2/memory_null_callback.h>
#include <scml2/memory_null_debug_callback.h>
#include <scml2/memory_callback_base.h>
#include <scml2/memory_debug_callback_base.h>
#include <scml2/streams.h>

#include <scml2_logging/stream.h>
#include <cassert>

namespace scml2 {

memory_base::
memory_base(const std::string& name,
            memory_base* parent,
            unsigned long long offset,
            unsigned long long size,
            unsigned int width) :
  memory_region(name, offset, size, width),
  mParent(parent),
  mDefaultCallback(0),
  mDefaultDebugCallback(0),
  mDmiEnabled(true)
{
  mReadCallback = new memory_null_callback(*this);
  mReadCallback->ref();
  mWriteCallback = mReadCallback;
  mWriteCallback->ref();

  mDebugReadCallback = new memory_null_debug_callback(*this);
  mDebugReadCallback->ref();
  mDebugWriteCallback = mDebugReadCallback;
  mDebugWriteCallback->ref();

  if (mParent) {
    mParent->register_alias(*this);
  }
}

memory_base::
~memory_base()
{
  mDefaultCallback->unref();
  mDefaultDebugCallback->unref();
  mReadCallback->unref();
  mWriteCallback->unref();
  mDebugReadCallback->unref();
  mDebugWriteCallback->unref();
}

void
memory_base::
propagate_update_fast_access()
{
  update_fast_access();
  AliasesConstIterator it = mAliases.begin();
  AliasesConstIterator end = mAliases.end();
  for (; it != end; ++it) {
    (*it)->propagate_update_fast_access();
  }
}

void
memory_base::
init_default_callback(memory_callback_base* cb)
{
  assert(!mDefaultCallback);
  assert(cb);
  mDefaultCallback = cb;
  mDefaultCallback->ref();
  do_set_read_callback(cb);
  do_set_write_callback(cb);
}

void
memory_base::
init_default_debug_callback(memory_debug_callback_base* cb)
{
  assert(!mDefaultDebugCallback);
  assert(cb);
  mDefaultDebugCallback = cb;
  mDefaultDebugCallback->ref();
  do_set_debug_read_callback(cb);
  do_set_debug_write_callback(cb);
}

void
memory_base::
register_alias(memory_base& alias)
{
  if ((alias.get_offset() + alias.get_size()) > (get_offset() + get_size())) {
    SCML2_LOG(get_streams().error())
      << "The alias '" << alias.get_name()
      << "' addresses memory that is not in the parent '"
      << get_name() << "'"
      << std::endl;
  }

  AliasesConstIterator it = mAliases.begin();
  AliasesConstIterator end = mAliases.end();
  for (; it != end; ++it) {
    if ((*it)->get_offset() < (alias.get_offset() + alias.get_size()) &&
        alias.get_offset() < ((*it)->get_offset() + (*it)->get_size())) {
      SCML2_LOG(get_streams().error())
        << "The alias '" << alias.get_name()
        << "' overlaps with alias '" << (*it)->get_name()  << "'"
        << std::endl;
    }
  }

  mAliases.push_back(&alias);
}

void
memory_base::
do_set_read_callback(memory_callback_base* cb)
{
  assert(mReadCallback);
  assert(cb);
  mReadCallback->unref();
  mReadCallback = cb;
  mReadCallback->ref();
}

void
memory_base::
do_set_write_callback(memory_callback_base* cb)
{
  assert(mWriteCallback);
  assert(cb);
  mWriteCallback->unref();
  mWriteCallback = cb;
  mWriteCallback->ref();
}

void
memory_base::
do_set_debug_read_callback(memory_debug_callback_base* cb)
{
  assert(mDebugReadCallback);
  assert(cb);
  mDebugReadCallback->unref();
  mDebugReadCallback = cb;
  mDebugReadCallback->ref();
}

void
memory_base::
do_set_debug_write_callback(memory_debug_callback_base* cb)
{
  assert(mWriteCallback);
  assert(cb);
  mDebugWriteCallback->unref();
  mDebugWriteCallback = cb;
  mDebugWriteCallback->ref();
}

void
memory_base::
set_callback(memory_callback_base* cb)
{
  assert(cb);
  scoped_reference<memory_callback_base> scopedRef(cb);
  if (has_default_write_behavior() || has_default_read_behavior()) {
    invalidate_dmi();
  }
  do_set_read_callback(cb);
  do_set_write_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_ACCESS, ACCESS_MODE_REGULAR);
}

void
memory_base::
set_read_callback(memory_callback_base* cb)
{
  assert(cb);
  scoped_reference<memory_callback_base> scopedRef(cb);
  if (has_default_read_behavior()) {
    invalidate_dmi();
  }
  do_set_read_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_READ, ACCESS_MODE_REGULAR);
}

void
memory_base::
set_write_callback(memory_callback_base* cb)
{
  assert(cb);
  scoped_reference<memory_callback_base> scopedRef(cb);
  if (has_default_write_behavior()) {
    invalidate_dmi();
  }
  do_set_write_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_WRITE, ACCESS_MODE_REGULAR);
}

void
memory_base::
remove_callback()
{
  if (!has_default_write_behavior() || !has_default_read_behavior()) {
    scoped_reference<memory_callback_base> scopedRef(mDefaultCallback);
    do_set_read_callback(mDefaultCallback);
    do_set_write_callback(mDefaultCallback);
    invalidate_dmi();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_ACCESS, ACCESS_MODE_REGULAR);
  }
}

void
memory_base::
remove_read_callback()
{
  if (!has_default_read_behavior()) {
    scoped_reference<memory_callback_base> scopedRef(mDefaultCallback);
    do_set_read_callback(mDefaultCallback);
    invalidate_dmi();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_READ, ACCESS_MODE_REGULAR);
  }
}

void
memory_base::
remove_write_callback()
{
  if (!has_default_write_behavior()) {
    scoped_reference<memory_callback_base> scopedRef(mDefaultCallback);
    do_set_write_callback(mDefaultCallback);
    invalidate_dmi();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_WRITE, ACCESS_MODE_REGULAR);
  }
}

memory_callback_base*
memory_base::
get_read_callback() const
{
  return mReadCallback;
}

memory_callback_base*
memory_base::
get_write_callback() const
{
  return mWriteCallback;
}

void
memory_base::
set_debug_callback(memory_debug_callback_base* cb)
{
  assert(cb);
  scoped_reference<memory_debug_callback_base> scopedRef(cb);
  if (has_default_debug_write_behavior() || has_default_debug_read_behavior()) {
    invalidate_dmi();
  }
  do_set_debug_read_callback(cb);
  do_set_debug_write_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_ACCESS, ACCESS_MODE_DEBUG);
}

void
memory_base::
set_debug_read_callback(memory_debug_callback_base* cb)
{
  assert(cb);
  scoped_reference<memory_debug_callback_base> scopedRef(cb);
  if (has_default_debug_read_behavior()) {
    invalidate_dmi();
  }
  do_set_debug_read_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_READ, ACCESS_MODE_DEBUG);
}

void
memory_base::
set_debug_write_callback(memory_debug_callback_base* cb)
{
  assert(cb);
  scoped_reference<memory_debug_callback_base> scopedRef(cb);
  if (has_default_debug_write_behavior()) {
    invalidate_dmi();
  }
  do_set_debug_write_callback(cb);
  mCallbackObservers.notify_callback_changed(ACCESS_TYPE_WRITE, ACCESS_MODE_DEBUG);
}

void
memory_base::
remove_debug_callback()
{
  if (!has_default_debug_write_behavior() || !has_default_debug_read_behavior()) {
    scoped_reference<memory_debug_callback_base> scopedRef(mDefaultDebugCallback);
    do_set_debug_read_callback(mDefaultDebugCallback);
    do_set_debug_write_callback(mDefaultDebugCallback);
    invalidate_dmi();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_ACCESS, ACCESS_MODE_DEBUG);
  }
}

void
memory_base::
remove_debug_read_callback()
{
  if (!has_default_debug_read_behavior()) {
    scoped_reference<memory_debug_callback_base> scopedRef(mDefaultDebugCallback);
    do_set_debug_read_callback(mDefaultDebugCallback);
    invalidate_dmi();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_READ, ACCESS_MODE_DEBUG);
  }
}

void
memory_base::
remove_debug_write_callback()
{
  if (!has_default_debug_write_behavior()) {
    scoped_reference<memory_debug_callback_base> scopedRef(mDefaultDebugCallback);
    do_set_debug_write_callback(mDefaultDebugCallback);
    invalidate_dmi();
    mCallbackObservers.notify_callback_changed(ACCESS_TYPE_WRITE, ACCESS_MODE_DEBUG);
  }
}

memory_debug_callback_base*
memory_base::
get_debug_read_callback() const
{
  return mDebugReadCallback;
}

memory_debug_callback_base*
memory_base::
get_debug_write_callback() const
{
  return mDebugWriteCallback;
}

unsigned int
memory_base::
collect_bitfields(std::vector<bitfield_base*>&) const
{
  return 0;
}

bool
memory_base::
content_is_observable() const
{
  return true;
}

void
memory_base::
enable_dmi()
{
  if (!is_dmi_enabled()) {
    invalidate_dmi();
    mDmiEnabled = true;
  }
}

void
memory_base::
disable_dmi()
{
  if (is_dmi_enabled()) {
    invalidate_dmi();
    mDmiEnabled = false;
  }
}

bool
memory_base::
is_dmi_enabled() const
{
  return mDmiEnabled;
}

bool
memory_base::
set_symbolic_name(const std::vector<unsigned char>& value,
                  const std::string& name)
{
  return mSymbolicNames.set_symbolic_name(value, name);
}

unsigned int
memory_base::
collect_symbolic_names(SymbolicNames& symbolicNames) const
{
  return mSymbolicNames.collect_symbolic_names(symbolicNames);
}

}
