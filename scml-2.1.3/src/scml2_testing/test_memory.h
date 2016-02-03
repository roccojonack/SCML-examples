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
#include <scml2_testing/memory_if.h>
#include <scml2_testing/test_memory_element.h>

namespace scml2 { namespace testing {
  class initiator_socket_proxy_base;

  class test_memory : public memory_if {
    public:
      test_memory(unsigned long long base, unsigned long long size, initiator_socket_proxy_base& socket);
      ~test_memory();

      test_memory_element operator[](unsigned long long offset);

      virtual unsigned long long get_size() const;
      virtual unsigned long long get_offset() const;

      virtual scml2::mappable_if& get_internal_memory();

      /**
       * open the file on disk, read contents into mMem, starting at addr.
       * read only the first 'size' bytes.
       */
      void load(const std::string& file, unsigned long long addr, size_t size);

      /**
       * Open the file on disk, write contents from mMem, starting at addr.
       * Write only the first 'size' bytes.
       */
      void save(const std::string& file, unsigned long long addr, size_t size);

      /**
       * Open the file on disk, compare contents with mMem, starting at addr.
       * compare only the first 'size' bytes.
       * return 'true' on match, 'false' on mismatch.
       */
      bool compare(const std::string& file, unsigned long long addr, size_t size);

    private:
      unsigned long long base;
      unsigned long long size;
      initiator_socket_proxy_base* socket;
      scml2::memory<unsigned char> data;
  };    
}}
