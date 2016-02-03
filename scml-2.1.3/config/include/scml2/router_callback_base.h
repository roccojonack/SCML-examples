/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ROUTER_CALLBACK_BASE_H
#define SCML2_ROUTER_CALLBACK_BASE_H

#include <scml2/resource.h>

#include <string>

namespace tlm {
  class tlm_generic_payload;
}

namespace sc_core {
  class sc_time;
}

namespace scml2 {

class router_callback_base : public resource
{
public:
  router_callback_base(const std::string& name = "<anonymous>");
  virtual ~router_callback_base();

  const std::string& get_name() const;

  virtual void execute(tlm::tlm_generic_payload& trans, sc_core::sc_time& t) = 0;
  virtual bool has_never_syncing_behavior() const = 0;

private:
  const std::string mName;
};

inline
router_callback_base::
router_callback_base(const std::string& name) :
  mName(name)
{
}

inline
router_callback_base::
~router_callback_base()
{
}

inline
const std::string&
router_callback_base::
get_name() const
{
  return mName;
}

}

#endif
