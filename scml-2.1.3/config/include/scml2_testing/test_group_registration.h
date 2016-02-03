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

#include <scml2_testing/test_group_factory.h>
#include <scml2_testing/test_group_registry.h>
#include <scml2_testing/parameter_configurations.h>

namespace scml2 { namespace testing {
  template<typename T>
  class test_group_registration {
    public:
      test_group_registration(const std::string& name) {
        factory = new test_group_factory<T>(name);
        test_group_registry::instance().add(factory);
      }

      test_group_registration(const std::string& name, const parameter_configurations& configurations) {
        factory = new test_group_factory<T>(name, configurations);
        test_group_registry::instance().add(factory);
      }

      ~test_group_registration() {
        delete factory;
      }

    private:
      test_group_factory<T>* factory;
  };
}}
