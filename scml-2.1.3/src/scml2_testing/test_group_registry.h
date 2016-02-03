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
#include <scml2_testing/test_group_registry_base.h>

namespace scml2 { namespace testing {
  class test_group_registry : public test_group_registry_base {
    public:
      static test_group_registry& instance();

    private:
      test_group_registry();
  };
}}
