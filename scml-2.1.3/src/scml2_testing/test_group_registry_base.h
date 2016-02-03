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

#include <vector>

namespace scml2 { namespace testing {
  class test_group_factory_base;

  class test_group_registry_base {
    public:
      virtual ~test_group_registry_base();

      const std::vector<test_group_factory_base*>& get_all_test_class_factories();
      void add(test_group_factory_base* t);
      void clear();

    private:
      std::vector<test_group_factory_base*> testClassFactories;
  };
}}
