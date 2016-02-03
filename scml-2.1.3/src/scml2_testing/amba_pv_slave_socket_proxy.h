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

#include <systemc>
#include <scml2.h>
#include <scml2_testing/proxy.h>
#include <scml2_testing/register_value_proxy.h>
#include <scml2_testing/predicate.h>
#include <amba_pv.h>
#include <sysc/kernel/sc_dynamic_processes.h>
#include <cassert>

namespace scml2 { namespace testing {

template<int NUMBITS>
class amba_pv_slave_socket_proxy : public proxy< amba_pv::amba_pv_master_socket<NUMBITS> >, public target_socket_proxy_base {
  public:
    predicate<incomplete, register_value_proxy<unsigned long long>, null_type> read64(unsigned long long offset) {
      return predicate<incomplete, register_value_proxy<unsigned long long>, null_type>(register_value_proxy<unsigned long long>(offset, this));
    }

    predicate<incomplete, register_value_proxy<unsigned int>, null_type> read32(unsigned long long offset) {
      return predicate<incomplete, register_value_proxy<unsigned int>, null_type>(register_value_proxy<unsigned int>(offset, this));
    }

    predicate<incomplete, register_value_proxy<unsigned short>, null_type> read16(unsigned long long offset) {
      return predicate<incomplete, register_value_proxy<unsigned short>, null_type>(register_value_proxy<unsigned short>(offset, this));
    }

    predicate<incomplete, register_value_proxy<unsigned char>, null_type> read8(unsigned long long offset) {
      return predicate<incomplete, register_value_proxy<unsigned char>, null_type>(register_value_proxy<unsigned char>(offset, this));
    }

    virtual bool write8(unsigned long long offset, unsigned char value) {
      return write(offset, value);
    }

    virtual bool write16(unsigned long long offset, unsigned short value) {
      return write(offset, value);
    }

    virtual bool write32(unsigned long long offset, unsigned int value) {
      return write(offset, value);
    }

    virtual bool write64(unsigned long long offset, unsigned long long value) {
      return write(offset, value);
    }

    virtual unsigned char read8(unsigned long long offset, bool* ok) {
      return read<unsigned char>(offset, ok);
    }

    virtual unsigned short read16(unsigned long long offset, bool* ok) {
      return read<unsigned short>(offset, ok);
    }

    virtual unsigned int read32(unsigned long long offset, bool* ok) {
      return read<unsigned int>(offset, ok);
    }

    virtual unsigned long long read64(unsigned long long offset, bool* ok) {
      return read<unsigned long long>(offset, ok);
    }

    template<typename T>
    bool write(unsigned long long offset, T& value) {
      sc_core::sc_time time = sc_core::SC_ZERO_TIME;
      amba_pv::amba_pv_resp_t result = this->target->write(offset, (unsigned char*) &value, sizeof(value), 0, 0, time);
      return result == amba_pv::AMBA_PV_OKAY;
    }

    template<typename T>
    T read(unsigned long long offset, bool* ok) {
      T result;
      sc_core::sc_time time = sc_core::SC_ZERO_TIME;
      amba_pv::amba_pv_resp_t response = this->target->read(offset, (unsigned char*) &result, sizeof(result), 0, time);
      if (ok != 0) {
        *ok = (response == amba_pv::AMBA_PV_OKAY);
      }
      return result; 
    }
};

}}
