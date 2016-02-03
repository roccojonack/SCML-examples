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
#include <scml2_testing/proxy.h>
#include <scml2_testing/register_value_proxy.h>
#include <scml2_testing/predicate.h>
#include <scml2_testing/initiator_socket_proxy_base.h>
#include <amba_pv.h>
#include <amba_pv_scml2.h>
#include <sysc/kernel/sc_dynamic_processes.h>

namespace scml2 { namespace testing {

template<int NUMBITS>
class amba_pv_master_socket_proxy : public proxy< amba_pv::amba_pv_slave_socket<NUMBITS> >, public initiator_socket_proxy_base {
  public:
    amba_pv_master_socket_proxy() : adapter(0) {
    }

    ~amba_pv_master_socket_proxy() {
      if (this->router) {
        unregister_router_callback();
      }
      delete adapter;
    }

  private:
    virtual void handle_target_changed() {
      std::string base(this->target->basename());
      assert(!adapter);
      adapter = new adapter_module((base + "_adapter_module").c_str(), *(this->target));
      this->router = new scml2::router<unsigned char>(base + "_router", ~0ULL);
      register_router_callback();
      adapter->adapter(*(this->router));
    }

    class adapter_module : public sc_core::sc_module {
      public:
        adapter_module(
          sc_core::sc_module_name name, 
          amba_pv::amba_pv_slave_socket<NUMBITS>& socket) : 
            sc_core::sc_module(name), 
            adapter(sc_core::sc_gen_unique_name((std::string((const char*) name) + "_adapter").c_str()), 
            socket) {
        }
        scml2::amba_pv_scml2_target_adapter<NUMBITS> adapter;
    };
    
    adapter_module* adapter;
};

}}
