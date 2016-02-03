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

namespace scml2 { namespace testing {
  class test_memory_element;

  class memory_element_value_proxy {
    public:
      typedef unsigned char ValueType;

      memory_element_value_proxy(test_memory_element* element);

      unsigned char get_value(bool* ok);

    private:
      test_memory_element* element;
  };
}}
