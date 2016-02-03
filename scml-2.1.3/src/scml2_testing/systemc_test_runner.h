/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <systemc>
#include <iostream>
#include <sstream>

#include <scml2_testing/test_runner.h>

namespace scml2 { namespace testing {
  class test_runner;

  class systemc_test_runner : public sc_core::sc_module {
  public:
    SC_HAS_PROCESS(systemc_test_runner);

    systemc_test_runner(sc_core::sc_module_name n, test_runner& runner);

    void runTheTests();
    
  private:
    test_runner& mRunner;
  };
}}
