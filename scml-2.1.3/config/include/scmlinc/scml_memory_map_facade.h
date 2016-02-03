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
// Purpose of file : definition of class scml_memory_map_facade
//                   facade between scml_memory and Liberty System
//
*/

#ifndef SCML_MEMORY_MAP_FACADE_H
#define SCML_MEMORY_MAP_FACADE_H

#include <vector>
#include "scmlinc/scml_memory_map_observer_if.h"
#include <utility>

class scml_memory_map_facade {
public:
  static scml_memory_map_facade & instance();
  void on_memory_map_changed() const;

  void registerObserver( scml_memory_map_observer_if * );
  void unregisterObserver( scml_memory_map_observer_if * );

private:
  scml_memory_map_facade();
  ~scml_memory_map_facade();

private:
  // data members
  typedef ::std::vector< scml_memory_map_observer_if * > vector_observer_type;
  vector_observer_type mObservers;

private:
  // disable
  scml_memory_map_facade( const scml_memory_map_facade & );
  scml_memory_map_facade & operator= ( const scml_memory_map_facade & );
};

#endif
