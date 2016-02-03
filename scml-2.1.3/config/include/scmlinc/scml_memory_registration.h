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
// Purpose of file : definition of class scml_memory_registration
//
*/

#ifndef SCML_MEMORY_REGISTRATION_H
#define SCML_MEMORY_REGISTRATION_H

#include <map>
#include <vector>
#include "scmlinc/scml_memory_base.h"

class scml_memory_registration {
public:
  static scml_memory_registration & instance();

  // registration of memory objects
  typedef scml_memory_base::this_pointer_type memory_pointer_type;
  bool registerMemory( memory_pointer_type);
  void unRegisterMemory( memory_pointer_type);
  size_t collectMemories( ::std::vector< memory_pointer_type >& );

  memory_pointer_type findMemoryByName( const ::std::string & );

private:
  scml_memory_registration();
  ~scml_memory_registration();

private:
  // data members
  typedef std::map<std::string, memory_pointer_type> MemoryRegions;
  typedef MemoryRegions::iterator MemoryRegionsIter;
  typedef MemoryRegions::const_iterator MemoryRegionsConstIter;
  MemoryRegions mMemoryRegions;

private:
  // disable
  scml_memory_registration( const scml_memory_registration & );
  scml_memory_registration & operator= ( const scml_memory_registration & );
};

#endif
