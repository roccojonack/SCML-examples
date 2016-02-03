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
  class test_group_base;
  class reporter_if;
  class test_group_registry_base;

  class test_runner {
    public:
      test_runner(test_group_registry_base* registry, reporter_if* reporter);
      ~test_runner();

      void create_all_test_groups();
      void initialize_all_test_groups();
      void run_all();
      void shutdown_all_test_groups();

    private:
      test_group_registry_base* registry;
      reporter_if* reporter;
      std::vector<test_group_base*> testGroups;
  };
}}
