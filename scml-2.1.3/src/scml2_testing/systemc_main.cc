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
#include <scml2_testing/stdout_reporter.h>
#include <scml2_testing/test_group_registry.h>
#include <systemc>

using namespace scml2::testing;

int sc_main(int, char**) {
  stdout_reporter reporter;
  test_runner runner(&test_group_registry::instance(), &reporter);
  runner.create_all_test_groups();
  runner.initialize_all_test_groups();
  systemc_test_runner scrunner("isystemc_test_runner", runner);

  sc_core::sc_start();
  runner.shutdown_all_test_groups();
  reporter.print_verbose_summary();  

  int passCount, failCount, notRunCount, checkCount;
  reporter.get_counters(passCount, failCount, notRunCount, checkCount);
  return (failCount + notRunCount - reporter.get_expected_number_of_failing_tests());
}
