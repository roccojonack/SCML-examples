/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ROUTER_NULL_CALLBACK_H
#define SCML2_ROUTER_NULL_CALLBACK_H

#include <scml2/router_callback_base.h>
#include <scml2/router_base.h>
#include <scml2/streams.h>

#include <scml2_logging/stream.h>
#include <tlm.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

class router_null_callback : public router_callback_base
{
public:
  router_null_callback(router_base& router);

  virtual void execute(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  virtual bool has_never_syncing_behavior() const;

private:
  router_base& mRouter;
};

inline
router_null_callback::
router_null_callback(router_base& router) :
  mRouter(router)
{
}

inline
void
router_null_callback::
execute(tlm::tlm_generic_payload& trans, sc_core::sc_time&)
{
  SCML2_LOG(mRouter.get_streams().error())
    << "No callback registered: Unmapped address = 0x"
    << std::hex << trans.get_address() << std::dec
    << std::endl;
}

inline
bool
router_null_callback::
has_never_syncing_behavior() const
{
  return true;
}

}

#endif
