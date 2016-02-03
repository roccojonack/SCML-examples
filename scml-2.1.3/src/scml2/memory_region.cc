/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_region.h>
#include <scml2/memory_region_registry.h>
#include <scml2/streams.h>
#include <scml2/utils.h>

#include <scml2_logging/severity.h>
#include <scml2_logging/stream.h>
#include <cassert>

namespace scml2 {

memory_region::
memory_region(const std::string& name,
              unsigned long long offset,
              unsigned long long size,
              unsigned int width) :
  sc_core::sc_object(name.c_str()),
  mStreams(0),
  mOffset(offset),
  mSize(size),
  mWidth(width)
{
  bool result =
    memory_region_registry::get_instance().register_memory_region(this);
  assert(result); (void)result;
}

memory_region::
~memory_region()
{
  bool result =
    memory_region_registry::get_instance().unregister_memory_region(this);
  assert(result); (void)result;
}

void
memory_region::
init_streams(streams& s)
{
  assert(!mStreams);
  mStreams = &s;
}

void
memory_region::
set_description(const std::string& d)
{
  mDescription = d;
}

const std::string&
memory_region::
get_description() const
{
  return mDescription;
}

unsigned int
memory_region::
read(unsigned long long,
     unsigned char*,
     unsigned int)
{
  return 0;
}

unsigned int
memory_region::
write(unsigned long long,
      const unsigned char*,
      unsigned int)
{
  return 0;
}

bool
memory_region::
content_is_observable() const
{
  return false;
}

bool
memory_region::
register_content_observer(memory_content_observer*)
{
  return false;
}

bool
memory_region::
unregister_all_content_observers()
{
  return false;
}

bool
memory_region::
unregister_content_observer(memory_content_observer*)
{
  return false;
}

bool
memory_region::
register_callback_observer(callback_observer* o)
{
  return mCallbackObservers.register_observer(o);
}

bool
memory_region::
unregister_all_callback_observers()
{
  return mCallbackObservers.unregister_all_observers();
}

bool
memory_region::
unregister_callback_observer(callback_observer* o)
{
  return mCallbackObservers.unregister_observer(o);
}

void
memory_region::
enable_dmi()
{
  assert(false);
}

void
memory_region::
disable_dmi()
{
  assert(false);
}

bool
memory_region::
is_dmi_enabled() const
{
  return false;
}

}
