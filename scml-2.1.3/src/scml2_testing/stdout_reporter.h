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

#include <iostream>
#include <sstream>

#include <scml2_testing/reporter_if.h>

namespace scml2 { namespace testing {
  class stdout_reporter : public reporter_if {
    public:
      stdout_reporter();

      virtual void set_total_test_count(int count);
      virtual void handle_test_started(const std::string& modelname, const std::string& testname);
      virtual void handle_test_failed(const std::string& failmsg, const std::string& filename, int linenum);
      virtual void handle_test_succeeded();
      virtual void count_check();
      virtual void get_counters(int& passCount, int& failCount, int& notRunCount, int& checkCount);
      virtual void set_expected_number_of_failing_tests(int n);
      int get_expected_number_of_failing_tests() const;
      void print_brief_summary() const;
      void print_verbose_summary() const;
      
    private:
      std::string mModelname;
      std::string mTestname;
      int mNumberOfTests;
      int mNumberOfChecks;
      int mNumberOfStartedTests;
      int mNumberOfPassingTests;
      int mNumberOfFailingTests;
      int mExpectedNumberOfFailingTests;
      std::ostringstream mFailureDetails;
  };
}}
