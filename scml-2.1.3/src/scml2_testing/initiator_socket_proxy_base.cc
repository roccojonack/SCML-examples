/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/initiator_socket_proxy_base.h>
#include <scml2_testing/memory_if.h>

#include <algorithm>

namespace scml2 { namespace testing {

class initiator_socket_proxy_base::router_callback : public router_callback_base {
  public:
    virtual void execute(tlm::tlm_generic_payload&, sc_core::sc_time&) {
      // TODO
    }

    virtual bool has_never_syncing_behavior() const {
      return false;
    }
};

initiator_socket_proxy_base::initiator_socket_proxy_base() : router(0), callback(0) {
}

initiator_socket_proxy_base::~initiator_socket_proxy_base() {
  if (callback) {
    callback->unref();
    callback = 0;
  }
  delete router;
}

void initiator_socket_proxy_base::register_router_callback() {
  callback = new router_callback();
  callback->ref();
  router->set_callback(callback);
}

void initiator_socket_proxy_base::unregister_router_callback() {
  assert(callback);
  router->set_callback(0);
  callback->unref();
  callback = 0;
}

void initiator_socket_proxy_base::add_memory(memory_if* memory) {
  router->map(memory->get_offset(), memory->get_size(), memory->get_internal_memory(), 0x0);
  memories.push_back(memory);
}

void initiator_socket_proxy_base::remove_memory(memory_if* memory) {
  router->unmap(memory->get_offset());
  memories.erase(std::remove(memories.begin(), memories.end(), memory), memories.end());
}

}}
