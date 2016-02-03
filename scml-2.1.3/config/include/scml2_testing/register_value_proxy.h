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

#include <scml2_testing/target_socket_proxy_base.h>

namespace scml2 { namespace testing {
  template<typename VALUE_TYPE>
  class register_value_proxy {
    public:
      typedef VALUE_TYPE ValueType;

      register_value_proxy(unsigned long long offset, target_socket_proxy_base* socketProxy) : offset(offset), socketProxy(socketProxy) {
      }

      VALUE_TYPE get_value(bool* ok) const;

    private:
      unsigned long long offset;
      target_socket_proxy_base* socketProxy;
  };

  template<> inline
  unsigned char register_value_proxy<unsigned char>::get_value(bool* ok) const {
    return socketProxy->read8(offset, ok);
  }

  template<> inline
  unsigned short register_value_proxy<unsigned short>::get_value(bool* ok) const {
    return socketProxy->read16(offset, ok);
  }

  template<> inline
  unsigned int register_value_proxy<unsigned int>::get_value(bool* ok) const {
    return socketProxy->read32(offset, ok);
  }

  template<> inline
  unsigned long long register_value_proxy<unsigned long long>::get_value(bool* ok) const {
    return socketProxy->read64(offset, ok);
  }
}}
