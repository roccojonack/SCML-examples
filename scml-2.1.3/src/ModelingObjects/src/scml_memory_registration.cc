/*****************************************************************************
 *                   Copyright (C) 1996-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
/*
// Modifications : 
//
// Purpose of file : implementation of class scml_memory_registration
//
*/

#include "scml_memory_registration.h"
#include "scml_memory_map_facade.h"


scml_memory_registration & scml_memory_registration::instance() 
{
  static scml_memory_registration inst;
  return inst;  
}

scml_memory_registration::scml_memory_registration()
{
}

scml_memory_registration::~scml_memory_registration()
{
  // not possible to unregister: Vmem initialization not in synch with global variables
  // nCoWare::nVmem::VmemSystem::getInstance().getRemapState()->unregisterObserver(&remap_observer_instance);
}

bool scml_memory_registration::registerMemory( memory_pointer_type m )
{  
  assert(m);
  const std::pair<MemoryRegionsIter, bool> r =
    mMemoryRegions.insert(std::make_pair(m->getName(), m));
  return r.second;
}

void scml_memory_registration::unRegisterMemory( memory_pointer_type m)
{
  mMemoryRegions.erase(m->getName());
}

scml_memory_registration::memory_pointer_type
scml_memory_registration::findMemoryByName( const ::std::string & n )
{
  MemoryRegionsConstIter it = mMemoryRegions.find(n);
  if (it != mMemoryRegions.end()) {
    return it->second;
  }
  return 0;
}

size_t
scml_memory_registration::collectMemories( ::std::vector< memory_pointer_type >& v )
{
  MemoryRegionsConstIter it = mMemoryRegions.begin();
  MemoryRegionsConstIter end = mMemoryRegions.end();
  for (; it != end; ++it) {
    v.push_back(it->second);
  }
  return mMemoryRegions.size();
}
