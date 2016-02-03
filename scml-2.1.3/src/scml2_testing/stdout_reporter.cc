/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/stdout_reporter.h>

namespace scml2 { namespace testing {

stdout_reporter::stdout_reporter() : 
    mNumberOfTests(0),
    mNumberOfChecks(0),
    mNumberOfStartedTests(0),
    mNumberOfPassingTests(0),
    mNumberOfFailingTests(0),
    mExpectedNumberOfFailingTests(0) {
}

void stdout_reporter::set_total_test_count(int count) {
  mNumberOfTests = count;
}

void stdout_reporter::handle_test_started(const std::string& modelname, const std::string& testname) {
  ++mNumberOfStartedTests;
  mModelname = modelname;
  mTestname = testname;
}

void stdout_reporter::handle_test_failed(const std::string& failmsg, const std::string& filename, int linenum) {
  ++mNumberOfFailingTests;
  std::cout << "F" << std::flush;
  mFailureDetails << "FAILED: " << mModelname << ", " << mTestname << " ["
                  << filename << ":" << linenum << "] " << failmsg 
                  << std::endl;

}

void stdout_reporter::handle_test_succeeded() {
  ++mNumberOfPassingTests;
  mModelname = "";
  mTestname = "";
  std::cout << "." << std::flush;
}

void stdout_reporter::count_check() {
  ++mNumberOfChecks;
}

void stdout_reporter::get_counters(int& passCount, int& failCount, int& notRunCount, int& checkCount) {
  passCount = mNumberOfPassingTests;
  failCount = mNumberOfFailingTests;
  checkCount = mNumberOfChecks;
  notRunCount = mNumberOfTests - mNumberOfPassingTests - mNumberOfFailingTests;
}

void stdout_reporter::print_brief_summary() const {
  std::ios::fmtflags f = std::cout.flags();
  int notRun = mNumberOfTests - mNumberOfPassingTests - mNumberOfFailingTests;

  std::cout << std::endl << std::dec
            << mNumberOfTests << " tests, "
            << mNumberOfPassingTests << " passing, "
            << mNumberOfFailingTests << " failing, "
            << notRun << " not run / not finished, "
            << mNumberOfChecks << " checks." << std::endl;
  if (mExpectedNumberOfFailingTests > 0) {
    std::cout << "(" << mExpectedNumberOfFailingTests << " failing tests were expected)" << std::endl;
  }
  if (notRun > 0) {
    std::cout << "Unfinished test: " << mModelname << ", " << mTestname << std::endl;
  } 
  std::cout.flags(f);
}

void stdout_reporter::print_verbose_summary() const {
  print_brief_summary();
  std::string s = mFailureDetails.str();
  if (s.empty()) return;
  std::cout << std::endl
            << "Detailed list of failures follows:" << std::endl
            << s << std::endl;
}

void stdout_reporter::set_expected_number_of_failing_tests(int n) {
   mExpectedNumberOfFailingTests = n;
}

int stdout_reporter::get_expected_number_of_failing_tests() const {
  return mExpectedNumberOfFailingTests;
}


}}
