/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#pragma once

#include <systemc>
#include <scml2_testing/proxy.h>
#include <cwrscml2/clock_master.h>

namespace scml2 { namespace testing {

class clock_port_proxy : public proxy< scml2::clock_master > {
  public:
    void set_period_ps(unsigned long long p) {
      target->set_period(sc_core::sc_time((double) p, sc_core::SC_PS));
    }

    unsigned long long get_period_ps() const {
      return target->get_period().value_in_ps();
    }
};


}}
