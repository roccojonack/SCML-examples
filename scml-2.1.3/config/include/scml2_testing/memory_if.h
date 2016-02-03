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

namespace scml2 { 
  class mappable_if;

  namespace testing {
    class memory_if {
      public:
        virtual ~memory_if();

        virtual unsigned long long get_size() const = 0;
        virtual unsigned long long get_offset() const = 0;

        virtual scml2::mappable_if& get_internal_memory() = 0;
    };    
  }
}
