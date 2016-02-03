/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_STORAGE_H
#define SCML2_MEMORY_STORAGE_H

#include <scml2/memory_storage_base.h>

namespace scml2 {

class toplevel_memory_base;

class memory_heap_storage :
  public memory_storage_base
{
public:
  memory_heap_storage(toplevel_memory_base& m);
  virtual ~memory_heap_storage();

  virtual unsigned char* get_fast_backdoor() const;
  virtual fast_backdoor_region get_fast_backdoor(unsigned long long address);
  virtual void read(unsigned long long address,
                    unsigned char* data,
                    unsigned int size) const;
  virtual void write(unsigned long long address,
                     const unsigned char* data,
                     unsigned int size);

public:
  static memory_storage_base* create_storage(toplevel_memory_base& m);

private:
  toplevel_memory_base& mMemory;
  unsigned char* mStorage;
};

}

#endif
