/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/memory_element_value_proxy.h>
#include <scml2_testing/test_memory_element.h>

namespace scml2 { namespace testing {

memory_element_value_proxy::memory_element_value_proxy(test_memory_element* element) : element(element) {
}
unsigned char memory_element_value_proxy::get_value(bool* ok) {
  if (ok) {
    *ok = true;
  }
  return *element;
}

}}
