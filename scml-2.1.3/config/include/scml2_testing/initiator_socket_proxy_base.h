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

#include <vector>
#include <scml2.h>

namespace scml2 { namespace testing {
  class memory_if;

  class initiator_socket_proxy_base {
    public:
      initiator_socket_proxy_base();
      virtual ~initiator_socket_proxy_base();

      void add_memory(memory_if* memory);
      void remove_memory(memory_if* memory);

    protected:
      void register_router_callback();
      void unregister_router_callback();

    protected:
      class router_callback;
      std::vector<memory_if*> memories;
      scml2::router<unsigned char>* router;
      router_callback* callback;
  };    
}}
