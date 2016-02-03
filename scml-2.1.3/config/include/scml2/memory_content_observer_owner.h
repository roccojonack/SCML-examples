/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#ifndef SCML2_MEMORY_CONTENT_OBSERVER_OWNER
#define SCML2_MEMORY_CONTENT_OBSERVER_OWNER

#include <scml2/memory_content_observer.h>
#include <scml2/types.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

class memory_content_observer_owner {
public:
  virtual ~memory_content_observer_owner();
  virtual void handle_pre_content_access(memory_content_observer* o,
                                         access_type type,
                                         access_mode mode,
                                         unsigned long long index) = 0;
  virtual void handle_post_content_access(memory_content_observer* o,
                                          access_type type,
                                          access_mode mode,
                                          unsigned long long index) = 0;
};

inline
memory_content_observer_owner::
~memory_content_observer_owner()
{
}

}

#endif
