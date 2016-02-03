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
#include <vector>

namespace scml2 { namespace testing {
  class test_group_base;

  class test_group_factory_base {
    public:
      virtual ~test_group_factory_base();

      virtual std::vector<test_group_base*> create_test_groups() = 0;
      virtual std::string get_name() const = 0;
  };
}}
