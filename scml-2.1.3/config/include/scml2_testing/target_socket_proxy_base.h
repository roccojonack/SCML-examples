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
  class target_socket_proxy_base {
    public:
      virtual ~target_socket_proxy_base();

      virtual bool write8(unsigned long long offset, unsigned char value) = 0;
      virtual unsigned char read8(unsigned long long offset, bool* ok) = 0;

      virtual bool write16(unsigned long long offset, unsigned short value) = 0;
      virtual unsigned short read16(unsigned long long offset, bool* ok) = 0;

      virtual bool write32(unsigned long long offset, unsigned int value) = 0;
      virtual unsigned int read32(unsigned long long offset, bool* ok) = 0;

      virtual bool write64(unsigned long long offset, unsigned long long value) = 0;
      virtual unsigned long long read64(unsigned long long offset, bool* ok) = 0;
  };    
}}
