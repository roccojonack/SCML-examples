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

#include <string>

namespace scml2 { namespace testing {
  class reporter_if {
    public:
      virtual ~reporter_if();

      virtual void set_total_test_count(int count) = 0;
      virtual void handle_test_started(const std::string& modelname, const std::string& testname) = 0;
      virtual void handle_test_failed(const std::string& failmsg, const std::string& filename, int linenum) = 0;
      virtual void handle_test_succeeded() = 0;
      virtual void count_check() = 0;
      virtual void get_counters(int& passCount, int& failCount, int& notRunCount, int& checkCount) = 0;
    };
}}
