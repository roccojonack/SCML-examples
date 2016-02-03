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
// Purpose of file : implementation of class scml_memory_map_facade
//
*/

#include "scml_memory_map_facade.h"

scml_memory_map_facade & scml_memory_map_facade::instance()
{
  static scml_memory_map_facade inst;
  return inst;
}

scml_memory_map_facade::scml_memory_map_facade()
{
}

scml_memory_map_facade::~scml_memory_map_facade()
{
}

void
scml_memory_map_facade::
on_memory_map_changed()
const
{
  for( vector_observer_type::const_iterator it = mObservers.begin(),
	 end = mObservers.end();
       it != end; ++it) {
    (*it)->memory_map_changed();
  }
}

void scml_memory_map_facade::registerObserver( scml_memory_map_observer_if * p )
{
  mObservers.push_back( p);
}

void scml_memory_map_facade::unregisterObserver( scml_memory_map_observer_if * p )
{
  for( vector_observer_type::iterator it = mObservers.begin(),
	 end = mObservers.end();
       it != end; ++it) {
    if (*it == p) {
      mObservers.erase(it);
      return;
    }
  }
}
