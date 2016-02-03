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

#include <scml2_testing/output_pin_proxy_base.h>

namespace scml2 { namespace testing {
  template<typename VALUE_TYPE>
  class pin_value_proxy {
    public:
      typedef VALUE_TYPE ValueType;

      pin_value_proxy(output_pin_proxy_base<VALUE_TYPE>* port) : port(port) {
      }

      VALUE_TYPE get_value(bool* ok) {
        if (ok) {
          *ok = true;
        }
        return port->get_value();
      }

    private:
      output_pin_proxy_base<VALUE_TYPE>* port;
  };
}}
