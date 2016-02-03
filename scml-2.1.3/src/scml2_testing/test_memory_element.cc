/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/test_memory_element.h>

#include <cassert>

namespace scml2 { namespace testing {

test_memory_element::test_memory_element(const scml2::memory_index_reference<unsigned char>& ref) : ref(ref) {
}

test_memory_element::operator unsigned char () {
  return ref;
}

test_memory_element& test_memory_element::operator=(unsigned char v) {
  ref = v;
  return *this;
}

test_memory_element& test_memory_element::operator=(const test_memory_element& other) {
  ref = other.ref;
  return *this;
}

bool test_memory_element::operator==(const test_memory_element& other) const {
  return ref == other.ref;
}

}}
