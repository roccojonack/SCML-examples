/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_region_registry.h>
#include <scml2/memory_region.h>

#include <cassert>

namespace scml2 {

memory_region_registry&
memory_region_registry::
get_instance()
{
  static memory_region_registry instance;
  return instance;
}

memory_region_registry::
memory_region_registry()
{
}

memory_region_registry::
~memory_region_registry()
{
}

bool
memory_region_registry::
register_memory_region(memory_region* m)
{
  assert(m);
  const std::pair<MemoryRegionsIter, bool> r =
    mMemoryRegions.insert(std::make_pair(m->get_name(), m));
  return r.second;
}

bool
memory_region_registry::
unregister_memory_region(memory_region* m)
{
  return (mMemoryRegions.erase(m->get_name()) != 0);
}

memory_region*
memory_region_registry::
find_memory_region_by_name(const std::string& name) const
{
  MemoryRegionsConstIter it = mMemoryRegions.find(name);
  if (it != mMemoryRegions.end()) {
    return it->second;
  }
  return 0;
}

unsigned int
memory_region_registry::
collect_memory_regions(std::vector<memory_region*>& v) const
{
  MemoryRegionsConstIter it = mMemoryRegions.begin();
  MemoryRegionsConstIter end = mMemoryRegions.end();
  for (; it != end; ++it) {
    v.push_back(it->second);
  }
  return mMemoryRegions.size();
}

}
