/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_DISALLOW_ACCESS_CALLBACK_H
#define SCML2_DISALLOW_ACCESS_CALLBACK_H

#include <scml2/memory_callback_base.h>

namespace sc_core {
  class sc_time;
}

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

class memory_disallow_access_callback : public memory_callback_base
{
public:
  memory_disallow_access_callback(bool returnError = true);

  virtual void execute(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  virtual bool has_never_syncing_behavior() const;

private:
  bool mReturnError;
};

inline
memory_disallow_access_callback::
memory_disallow_access_callback(bool returnError) :
  memory_callback_base(returnError ? "<disallow access callback>" :
                                     "<ignore access callback>"),
  mReturnError(returnError)
{
}

}

#endif
