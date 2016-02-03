/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory.h>

#include <scml2/memory_storage_base.h>
#include <scml2/memory_storage_creator.h>
#include <scml2/memory_slow_access.h>
#include <scml2/memory_slow_access_content_observer_decorator.h>
#include <scml2/memory_slow_access_storage_decorator.h>
#include <scml2/memory_default_callback.h>
#include <scml2/memory_default_debug_callback.h>
#include <scml2/streams.h>
#include <scml2/utils.h>

#include <scml2_logging/stream.h>
#include <algorithm>
#include <cassert>

namespace scml2 {

template <typename DT>
memory<DT>::
memory(const std::string& name,
       unsigned long long size) :
  toplevel_memory_base(name, size, sizeOf<DT>()),
  mFastAccess()
{
  setup(memory_storage_creator::get_instance().create_storage(*this), false);
}

template <typename DT>
memory<DT>::
memory(const std::string& name,
       unsigned long long size,
       memory_storage_base* storage,
       bool delStorageOnDestruction) :
  toplevel_memory_base(name, size, sizeOf<DT>()),
  mFastAccess()
{
  setup(storage, delStorageOnDestruction);
}

template <typename DT>
memory<DT>::
~memory()
{
}

template <typename DT>
void
memory<DT>::
initialize(const DT& value)
{
  for (unsigned int i = 0; i < get_size(); ++i) {
    put_debug(i, value);
  }
}

template <typename DT>
bool
memory<DT>::
set_symbolic_name(const DT& value, const std::string& name)
{
  std::vector<unsigned char> tmp(sizeOf<DT>());
  to_char_array(value, &tmp[0], sizeOf<DT>(), 0);
  return set_symbolic_name(tmp, name);
}

template <typename DT>
void
memory<DT>::
setup(memory_storage_base* storage, bool delStorageOnDestruction)
{
  set_storage(storage, delStorageOnDestruction);
  init_default_callback(new memory_default_callback<DT>(mFastAccess, *this));
  init_default_debug_callback(new memory_default_debug_callback<DT>(mFastAccess));

  update_fast_access();
}


template <typename DT>
void
memory<DT>::
update_fast_access()
{
  mFastAccess.update(create_slow_access(0));
}

template <typename DT>
memory_slow_access_base<DT>*
memory<DT>::
create_slow_access(unsigned long long offset)
{
  assert(mStorage);
  unsigned char* fastBackdoor = mStorage->get_fast_backdoor();
  if (fastBackdoor) {
    // backdoor pointer available -> fast inline code
    if (mContentObservers.has_observers()) {
      return ::scml2::create_slow_access<DT>(
               create_slow_access_content_observer_decorator<DT>(
                 memory_fast_access_impl<DT>(fastBackdoor + index_to_address<DT>(offset)),
                 mContentObservers,
                 offset));

    } else {
      return ::scml2::create_slow_access<DT>(
               memory_fast_access_impl<DT>(fastBackdoor + index_to_address<DT>(offset)));
    }

  } else {
    // no backdoor pointer available -> use virtual read/write methods of storage class
    if (mContentObservers.has_observers()) {
      return ::scml2::create_slow_access<DT>(
               create_slow_access_content_observer_decorator<DT>(
                 memory_slow_access_storage_decorator<DT>(*mStorage, offset),
                 mContentObservers,
                 offset));

    } else {
      return ::scml2::create_slow_access<DT>(
               memory_slow_access_storage_decorator<DT>(*mStorage, offset));
    }
  }

  SCML2_LOG(get_streams().internal_error()) << "can not create slow access class" << std::endl;
  return 0;
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class memory<type >;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
