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
  template<typename T>
  class output_pin_proxy_base {
    public:
      virtual ~output_pin_proxy_base() {}

      virtual T get_value() const = 0;
  };
}}
