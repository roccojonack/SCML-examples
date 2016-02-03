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
// Purpose of file : definition of class scml_memory_user
//
*/

#ifndef SCML_MEMORY_USER_H
#define SCML_MEMORY_USER_H

#include "scmlinc/scml_memory_pv_if.h"
#include "scmlinc/scml_memory_base.h"

template< typename DT > class scml_memory_operations_podt_common;
template< typename DT > class scml_router_operations_podt_common;

class scml_memory_user {
public:
  static scml_memory_user & instance();

  typedef scml_memory_base::uint64 address_type;
  inline address_type get_last_top_level_address() const
  {
    return mLastTopLevelAddress;
  }

  typedef unsigned int user_id_data_type;
  inline user_id_data_type get_last_user_id() const
  {
    return mLastUserId;
  }

  typedef scml_memory_base::this_pointer_type scml_memory_pointer;
  typedef scml_memory_base::this_reference_type scml_memory_reference;
  inline scml_memory_reference get_last_memory_reference() const
  {
    return *mLastMemory;
  }

  typedef scml_bitfield_base::scml_bitfield_container_entry scml_bitfield_pointer;
  typedef scml_bitfield_base::scml_bitfield_reference scml_bitfield_reference;
  inline scml_bitfield_reference get_last_bitfield_reference() const
  {
    return *mLastBitfield;
  }

  inline bool is_debug_access() const
  {
    return mDebug;
  }

private:
  template< typename DT > friend class scml_memory_operations_podt_common;
  template< typename DT > friend class scml_router_operations_podt_common;
  friend class scml_bitfield_container;
  inline void set_last_top_level_address(const address_type a)
  {
    mLastTopLevelAddress = a;
  }
  inline void set_last_user_id(const user_id_data_type i)
  {
    mLastUserId = i;
  }
  inline void set_last_memory_pointer(scml_memory_pointer m)
  {
    mLastMemory = m;
  }
  inline void set_last_bitfield_pointer(scml_bitfield_pointer m)
  {
    mLastBitfield = m;
  }
  inline void set_debug_access(bool b)
  {
    mDebug = b;
  }

private:
  scml_memory_user();
  ~scml_memory_user();

private:
  // disable
  scml_memory_user( const scml_memory_user & );
  scml_memory_user & operator= ( const scml_memory_user & );

private:
  // data members
  address_type mLastTopLevelAddress;
  user_id_data_type mLastUserId;
  scml_memory_pointer mLastMemory;
  scml_bitfield_pointer mLastBitfield;
  bool mDebug;
};

#endif
