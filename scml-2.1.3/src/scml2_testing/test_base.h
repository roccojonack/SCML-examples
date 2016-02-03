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
  class test_base {
    public:
      test_base(const std::string& name);
      virtual ~test_base();

      virtual void run(void*) = 0;

      const std::string& get_name() const;

    private:
      std::string name;
  };
}}
