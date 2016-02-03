/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_STORAGE_BASE_H
#define SCML2_MEMORY_STORAGE_BASE_H

namespace scml2 {

class toplevel_memory_base;

class memory_storage_base
{
public:
  struct fast_backdoor_region
  {
    unsigned long long startAddress;
    unsigned long long endAddress;
    unsigned char* fastBackdoor;
  };

public:
  memory_storage_base();
  virtual ~memory_storage_base();

  virtual unsigned char* get_fast_backdoor() const = 0;
  virtual fast_backdoor_region get_fast_backdoor(unsigned long long address) = 0;
  virtual void read(unsigned long long address,
                    unsigned char* data,
                    unsigned int size) const = 0;
  virtual void write(unsigned long long address,
                     const unsigned char* data,
                     unsigned int size) = 0;

private:
  static memory_storage_base* create_storage(toplevel_memory_base& m);

private:
  memory_storage_base(const memory_storage_base&);
  memory_storage_base& operator=(const memory_storage_base&);
};

}

#endif
