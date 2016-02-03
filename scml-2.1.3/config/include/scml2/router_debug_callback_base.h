/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ROUTER_DEBUG_CALLBACK_BASE_H
#define SCML2_ROUTER_DEBUG_CALLBACK_BASE_H

#include <scml2/resource.h>

#include <string>

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

class router_debug_callback_base : public resource
{
public:
  router_debug_callback_base(const std::string& name = "<anonymous>");
  virtual ~router_debug_callback_base();

  const std::string& get_name() const;

  virtual unsigned int execute(tlm::tlm_generic_payload& trans) = 0;

private:
  const std::string mName;
};

inline
router_debug_callback_base::
router_debug_callback_base(const std::string& name) :
  mName(name)
{
}

inline
router_debug_callback_base::
~router_debug_callback_base()
{
}

inline
const std::string&
router_debug_callback_base::
get_name() const
{
  return mName;
}

}

#endif
