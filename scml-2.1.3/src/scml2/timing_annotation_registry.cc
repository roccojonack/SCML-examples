/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/timing_annotation_registry.h>

#include <systemc>
#include <cassert>

namespace scml2 {

timing_annotation_registry&
timing_annotation_registry::
get_instance()
{
  static timing_annotation_registry instance;
  return instance;
}

timing_annotation_registry::
timing_annotation_registry()
{
}

timing_annotation_registry::
~timing_annotation_registry()
{
}

sc_core::sc_process_b*
timing_annotation_registry::
get_current_process_handle()
{
  return sc_core::sc_get_current_process_handle();
}

void
timing_annotation_registry::
register_timing_annotation(const sc_core::sc_time& t)
{
  const sc_core::sc_process_b* handle = get_current_process_handle();
  mTimingAnnotations[handle].push(&t);
}

void
timing_annotation_registry::
unregister_timing_annotation()
{
  assert(!mTimingAnnotations[get_current_process_handle()].empty());
  return mTimingAnnotations[get_current_process_handle()].pop();
}

const sc_core::sc_time&
timing_annotation_registry::
get_timing_annotation() const
{
  TimingAnnotationConstIter it =
    mTimingAnnotations.find(get_current_process_handle());
  if (it == mTimingAnnotations.end() || it->second.empty()) {
    static const sc_core::sc_time t = sc_core::SC_ZERO_TIME;
    return t;

  } else {
    assert(!it->second.empty());
    return *it->second.top();
  }
}

}
