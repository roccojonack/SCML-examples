/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_alias.h>

#include <scml2/memory.h>
#include <scml2/utils.h>

#include <scml2/memory_default_callback.h>
#include <scml2/memory_default_debug_callback.h>

namespace scml2 {

template <typename DT>
memory_alias<DT>::
memory_alias(const std::string& name,
             memory<DT>& parent,
             unsigned long long offset,
             unsigned long long size) :
  memory_base(name, &parent, offset, size, sizeOf<DT>()),
  mToplevel(parent),
  mFastAccess()
{
  setup();
}

template <typename DT>
memory_alias<DT>::
memory_alias(const std::string& name,
             memory_alias<DT>& parent,
             unsigned long long offset,
             unsigned long long size) :
  memory_base(name, &parent, parent.get_offset() + offset, size, sizeOf<DT>()),
  mToplevel(parent.mToplevel),
  mFastAccess()
{
  setup();
}

template <typename DT>
memory_alias<DT>::
~memory_alias()
{
}

template <typename DT>
void
memory_alias<DT>::
initialize(const DT& value)
{
  for (unsigned int i = 0; i < get_size(); ++i) {
    put_debug(i, value);
  }
}

template <typename DT>
bool
memory_alias<DT>::
set_symbolic_name(const DT& value, const std::string& name)
{
  std::vector<unsigned char> tmp(sizeOf<DT>());
  to_char_array(value, &tmp[0], sizeOf<DT>(), 0);
  return set_symbolic_name(tmp, name);
}

template <typename DT>
void
memory_alias<DT>::
setup()
{
  init_streams(mToplevel.get_streams());

  init_default_callback(new memory_default_callback<DT>(mFastAccess, mToplevel));
  init_default_debug_callback(new memory_default_debug_callback<DT>(mFastAccess));

  update_fast_access();
}

template <typename DT>
void
memory_alias<DT>::
invalidate_dmi()
{
  mToplevel.invalidate_dmi();
}

template <typename DT>
void
memory_alias<DT>::
update_fast_access()
{
  mFastAccess.update(mToplevel.create_slow_access(get_offset()));
}

template <typename DT>
unsigned int
memory_alias<DT>::
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
memory_alias<DT>::
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
memory_alias<DT>::
register_content_observer(memory_content_observer* o)
{
  return mToplevel.register_content_observer(o, get_offset());
}

template <typename DT>
bool
memory_alias<DT>::
unregister_all_content_observers()
{
  return mToplevel.unregister_all_content_observers();
}

template <typename DT>
bool
memory_alias<DT>::
unregister_content_observer(memory_content_observer* o)
{
  return mToplevel.unregister_content_observer(o);
}

template <typename DT>
const char*
memory_alias<DT>::
kind() const
{
  return "scml2::memory_alias";
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class memory_alias<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
