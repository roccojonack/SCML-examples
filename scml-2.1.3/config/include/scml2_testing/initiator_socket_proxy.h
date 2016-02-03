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

namespace scml2 { namespace testing {

template<int NUMBITS>
class initiator_socket_proxy : public proxy< tlm::tlm_target_socket<NUMBITS> >, public initiator_socket_proxy_base {
  public:
    initiator_socket_proxy() : adapter(0) {
    }

    ~initiator_socket_proxy() {
      if (this->router) {
        unregister_router_callback();
      }
      delete adapter;
    }

  private:
    virtual void handle_target_changed() {
      std::string base(this->target->basename());
      assert(!adapter);
      adapter = new scml2::tlm2_gp_target_adapter<NUMBITS>(base + "_adapter", *(this->target));
      this->router = new scml2::router<unsigned char>(base + "_router", ~0ULL);
      register_router_callback();
      (*adapter)(*(this->router));
    }

    scml2::tlm2_gp_target_adapter<NUMBITS>* adapter;
};

}}
