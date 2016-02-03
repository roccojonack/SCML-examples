/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/test_runner.h>

#include <scml2_testing/test_group_base.h>
#include <scml2_testing/test_group_factory_base.h>
#include <scml2_testing/test_base.h>
#include <scml2_testing/test_group_registry_base.h>

namespace scml2 { namespace testing {

test_runner::test_runner(test_group_registry_base* registry, reporter_if* reporter) : registry(registry), reporter(reporter) {
}

test_runner::~test_runner() {
  for (size_t i = 0; i < testGroups.size(); ++i) {
    delete testGroups[i];
  }
}

void test_runner::create_all_test_groups() {
  std::vector<test_group_factory_base*> testClassFactories = registry->get_all_test_class_factories();
  for (size_t i = 0; i < testClassFactories.size(); ++i) {
    std::vector<test_group_base*> testClasses = testClassFactories[i]->create_test_groups();
    for (size_t j = 0; j < testClasses.size(); ++j) {
      testClasses[j]->register_tests();
      testGroups.push_back(testClasses[j]);
    }
  }
}

void test_runner::initialize_all_test_groups() {
  for (size_t i = 0; i < testGroups.size(); ++i) {
    test_group_base* testClass = testGroups[i];
    testClass->set_reporter(reporter);
    testClass->do_initialize();
  }
}

void test_runner::run_all() {
  // Count all tests
  size_t testCount = 0;
  for (std::size_t inx = 0; inx < testGroups.size(); ++inx) {
    testCount += testGroups[inx]->get_tests().size();
  }
  reporter->set_total_test_count((int) testCount);
  
  // Run all tests
  for (std::size_t inx = 0; inx < testGroups.size(); ++inx) {
    test_group_base* testClass = testGroups[inx];
    std::vector<test_base*> tests = testClass->get_tests();
    for (size_t i = 0; i < tests.size(); ++i) {
      test_base* test = tests[i];
      reporter->handle_test_started(testClass->get_name(), test->get_name());
      try {
        testClass->do_setup();
        test->run(testClass);
        testClass->do_teardown();
        reporter->handle_test_succeeded();
      } 
      catch (const test_exception&) {
        // Reporter already knows about the failure...
        testClass->do_teardown();
      } 
      catch (...) {
        reporter->handle_test_failed("Unexpected exception", "", -1);
        testClass->do_teardown();
      }
    }
  }
}

void test_runner::shutdown_all_test_groups() {
  for (size_t i = 0; i < testGroups.size(); ++i) {
    testGroups[i]->do_shutdown();
  }
}

}}
