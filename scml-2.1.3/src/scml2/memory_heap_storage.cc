/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_heap_storage.h>
#include <scml2/toplevel_memory_base.h>
#include <scml2/streams.h>

#include <scml2_logging/stream.h>
#include <limits>

namespace scml2 {

memory_heap_storage::
memory_heap_storage(toplevel_memory_base& m) :
  mMemory(m)
{
  if (m.get_size()) {
    const unsigned long long size =
      index_to_address(m.get_size(), m.get_width());
    if (size > std::numeric_limits<std::size_t>::max()) {
      SCML2_LOG(m.get_streams().error())
        << "The size (0x" << std::hex << size << ") of memory '"
        << m.get_name() << "' is to big to be allocated on the heap."
        << std::dec << std::endl;
    }
    mStorage = new unsigned char[(std::size_t)size];

  } else {
    mStorage = 0;
  }
}

memory_heap_storage::
~memory_heap_storage()
{
  delete [] mStorage;
}

unsigned char*
memory_heap_storage::
get_fast_backdoor() const
{
  return mStorage;
}

memory_storage_base::fast_backdoor_region
memory_heap_storage::
get_fast_backdoor(unsigned long long)
{
  fast_backdoor_region region;
  region.startAddress = 0x0;
  region.endAddress = index_to_address(mMemory.get_size(),
                                       mMemory.get_width());
  region.fastBackdoor = mStorage;
  return region;
}

void
memory_heap_storage::
read(unsigned long long address,
     unsigned char* data,
     unsigned int size) const
{
  memcpy(data, mStorage + address, size);
}

void
memory_heap_storage::
write(unsigned long long address,
      const unsigned char* data,
      unsigned int size)
{
  memcpy(mStorage + address, data, size);
}

memory_storage_base*
memory_heap_storage::
create_storage(toplevel_memory_base& m)
{
  return new memory_heap_storage(m);
}

}
