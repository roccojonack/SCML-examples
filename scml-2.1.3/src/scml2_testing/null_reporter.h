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
  class null_reporter : public reporter_if {
    public:
      null_reporter() {}

      virtual void set_total_test_count(int count) {}
      virtual void handle_test_started(const std::string&, const std::string&) {}
      virtual void handle_test_failed(const std::string&, const std::string&, int) {}
      virtual void handle_test_succeeded() {}
      virtual void count_check() {}
      virtual void get_counters(int&, int&, int&, int&) {}
  };
}}
