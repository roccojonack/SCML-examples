/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_DISALLOW_DEBUG_ACCESS_CALLBACK_H
#define SCML2_DISALLOW_DEBUG_ACCESS_CALLBACK_H

#include <scml2/memory_debug_callback_base.h>

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

class memory_disallow_debug_access_callback : public memory_debug_callback_base
{
public:
  memory_disallow_debug_access_callback();

  virtual unsigned int execute(tlm::tlm_generic_payload& trans);
};

inline
memory_disallow_debug_access_callback::
memory_disallow_debug_access_callback() :
  memory_debug_callback_base("<disallow debug access callback>")
{
}

}

#endif
