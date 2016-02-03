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

#include <scml2_testing/test_base.h>

namespace scml2 { namespace testing {
  template<typename T>
  class test : public test_base {
    public:
      typedef void (T::*method_type)();

      test(method_type method, const std::string& name) : test_base(name) {
        this->method = method;
      }

    private:
      void run(void* object) {
        ((*(T*)object).*method)();
      }

      method_type method;
  };
}}
