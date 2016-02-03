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

#include <scml2.h>
#include <scml2_testing/memory_element_value_proxy.h>
#include <scml2_testing/predicate.h>

namespace scml2 { namespace testing {
  class test_memory_element {
    public:
      test_memory_element(const scml2::memory_index_reference<unsigned char>& ref);

      operator unsigned char ();

      test_memory_element& operator=(unsigned char v);
      test_memory_element& operator=(const test_memory_element& other);
      bool operator==(const test_memory_element& other) const;

      predicate<complete, memory_element_value_proxy, unsigned char> equals(unsigned char val) {
        return predicate<complete, memory_element_value_proxy, null_type>(memory_element_value_proxy(this)).equals(val);
      }

    
    private:
      scml2::memory_index_reference<unsigned char> ref;
  };
}}
