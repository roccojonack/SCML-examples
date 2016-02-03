/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_REGION_REGISTRY_H
#define SCML2_MEMORY_REGION_REGISTRY_H

#include <map>
#include <vector>
#include <string>

namespace scml2 {

class memory_region;

class memory_region_registry
{
public:
  static memory_region_registry& get_instance();

  memory_region* find_memory_region_by_name(const std::string& name) const;
  unsigned int collect_memory_regions(std::vector<memory_region*>& v) const;

private:
  friend class memory_region;

  bool register_memory_region(memory_region* m);
  bool unregister_memory_region(memory_region* m);

private:
  memory_region_registry();
  ~memory_region_registry();

private:
  typedef std::map<std::string, memory_region*> MemoryRegions;
  typedef MemoryRegions::iterator MemoryRegionsIter;
  typedef MemoryRegions::const_iterator MemoryRegionsConstIter;
  MemoryRegions mMemoryRegions;
};

}

#endif
