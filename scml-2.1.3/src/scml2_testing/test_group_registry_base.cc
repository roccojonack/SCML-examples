/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/test_group_registry_base.h>

namespace scml2 { namespace testing {

test_group_registry_base::~test_group_registry_base() {
}

const std::vector<test_group_factory_base*>& test_group_registry_base::get_all_test_class_factories() {
  return testClassFactories;
}

void test_group_registry_base::add(test_group_factory_base* t) {
  testClassFactories.push_back(t);
}

}}
