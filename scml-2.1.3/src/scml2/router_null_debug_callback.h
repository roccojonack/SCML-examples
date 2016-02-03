/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ROUTER_NULL_DEBUG_CALLBACK_H
#define SCML2_ROUTER_NULL_DEBUG_CALLBACK_H

#include <scml2/router_debug_callback.h>

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

class router_null_debug_callback : public router_debug_callback_base
{
public:
  router_null_debug_callback();

  virtual unsigned int execute(tlm::tlm_generic_payload& trans);
};

inline
router_null_debug_callback::
router_null_debug_callback()
{
}

inline
unsigned int
router_null_debug_callback::
execute(tlm::tlm_generic_payload&)
{
  return 0;
}

}

#endif
