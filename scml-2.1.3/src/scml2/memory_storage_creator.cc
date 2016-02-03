/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_storage_creator.h>
#include <scml2/memory_heap_storage.h>

#include <cassert>

namespace scml2 {

memory_storage_creator::
memory_storage_creator() :
  mStorageCreator(&memory_heap_storage::create_storage)
{
}

memory_storage_creator&
memory_storage_creator::
get_instance()
{
  static memory_storage_creator c;
  return c;
}

void
memory_storage_creator::
set_storage_creator(StorageCreator c)
{
  assert(c);
  mStorageCreator = c;
}

memory_storage_creator::StorageCreator
memory_storage_creator::
get_storage_creator() const
{
  return mStorageCreator;
}

memory_storage_base*
memory_storage_creator::
create_storage(toplevel_memory_base& m)
{
  assert(mStorageCreator);
  return (*mStorageCreator)(m);
}

}
