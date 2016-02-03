/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/systemc_test_runner.h>

#include <scml2_testing/test_runner.h>

namespace scml2 { namespace testing {

systemc_test_runner::systemc_test_runner(sc_core::sc_module_name n, test_runner& runner) : sc_core::sc_module(n), mRunner(runner) {
  SC_THREAD(runTheTests);
}

void systemc_test_runner::runTheTests() {
  sc_core::wait(0, sc_core::SC_NS); // Give all threads/methods a chance to initialize
  mRunner.run_all();
  if (sc_core::sc_is_running()) {
    sc_core::sc_stop();
  }
}

}}
