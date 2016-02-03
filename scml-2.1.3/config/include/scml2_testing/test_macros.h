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

#include <scml2_testing/test.h>
#include <scml2_testing/test_group_registration.h>

#define SCML2_BEGIN_TESTS(testclass) \
public: \
  typedef testclass this_type; \
  virtual void register_tests() { \

#define SCML2_END_TESTS() \
  }

#define SCML2_TEST(test_method) \
  add_test(new scml2::testing::test<this_type>(&this_type::test_method, #test_method));

#define SCML2_APPEND(a, b) SCML2_APPEND2(a, b)
#define SCML2_APPEND2(a, b) SCML2_APPEND3(a, b)
#define SCML2_APPEND3(a, b) a##b

#define SCML2_MAKE_UNIQUE_NAME(a) SCML2_APPEND(a, __LINE__)

#define SCML2_REGISTER_TEST_GROUP(testclass) \
  namespace { scml2::testing::test_group_registration<testclass> SCML2_MAKE_UNIQUE_NAME(foo) = scml2::testing::test_group_registration<testclass>(#testclass); }

#define SCML2_REGISTER_TEST_GROUP_WITH_PARAMETERS(testclass, parameters) \
  namespace { scml2::testing::test_group_registration<testclass> SCML2_MAKE_UNIQUE_NAME(foo) = scml2::testing::test_group_registration<testclass>(#testclass, parameters); }
