/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_TIMING_ANNOTATION_REGISTRY_H
#define SCML2_TIMING_ANNOTATION_REGISTRY_H

#include <map>
#include <stack>

namespace sc_core {
  class sc_process_b;
  class sc_time;
}

namespace scml2 {

class timing_annotation_registry
{
public:
  static timing_annotation_registry& get_instance();

  void register_timing_annotation(const sc_core::sc_time& t);
  void unregister_timing_annotation();

  const sc_core::sc_time& get_timing_annotation() const;

private:
  timing_annotation_registry();
  ~timing_annotation_registry();

  static sc_core::sc_process_b* get_current_process_handle();

private:
  typedef std::map<const sc_core::sc_process_b*,
                   std::stack<const sc_core::sc_time*> > TimingAnnotation;
  typedef TimingAnnotation::iterator TimingAnnotationIter;
  typedef TimingAnnotation::const_iterator TimingAnnotationConstIter;
  TimingAnnotation mTimingAnnotations;
};

}

#endif
