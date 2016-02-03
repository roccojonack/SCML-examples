/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_NULL_ADAPTER_H
#define SCML2_NULL_ADAPTER_H

#include <tlm.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

class null_adapter
{
public:
  null_adapter() {
  }

  void operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& /*t*/) {
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
  }
};

}

#endif
