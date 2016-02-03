/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/test_base.h>

namespace scml2 { namespace testing {

test_base::test_base(const std::string& name) : name(name) {
}

test_base::~test_base() {
}

const std::string& test_base::get_name() const {
  return name;
}

}}
