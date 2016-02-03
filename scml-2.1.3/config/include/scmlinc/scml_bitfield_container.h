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
 * Modifications :
 *
 * Purpose of file : Definition of bitfield container
 *
 */

#ifndef SCML_BITFIELD_CONTAINER_H
#define SCML_BITFIELD_CONTAINER_H

#include <vector>
#include "scmlinc/scml_bitfield.h"
#include "scmlinc/scml_memory_utils.h"

class scml_bitfield_container : public scml_bitfield_container_if {
public: 
  typedef scml_bitfield_container_if::value_type value_type;
  typedef scml_bitfield_container_if::size_type size_type;
  typedef scml_bitfield_container_if::scml_bitfield_container_entry scml_bitfield_container_entry;
  // constructor & destructor
  scml_bitfield_container();
  virtual ~scml_bitfield_container();

  // see scml_bitfield_container_if
  virtual bool registerBitfields( scml_bitfield_container_entry );
  virtual bool updateReadBlockingProperty( bool isBlocking );
  virtual bool updateWriteBlockingProperty( bool isBlocking );
  virtual value_type getBitfieldValue( size_type offset, size_type size);
  virtual void setBitfieldValue( value_type, size_type offset, size_type size);

  // bit fields support read & write
  template <typename DT>
  DT read( unsigned int accessSize, unsigned int offset);
  template <typename DT>
  DT write( const DT& wData, unsigned int accessSize, unsigned int offset);
 
  typedef scml_bitfield_base::bitfield_pointer_container bitfield_pointer_container;
  bool getBitfieldPointers( bitfield_pointer_container & ) const;
  bool hasCallbacks();
  bool hasReadCallbacks();
  bool hasWriteCallbacks();

  bool hasReadBehaviourAttached();
  bool hasWriteBehaviourAttached();
  bool hasBehaviourAttached();

  scml_bitfield_container_entry findBitfield(const std::string& name) const;
  scml_bitfield_container_entry findOverlap(scml_bitfield_container_entry b) const;

private:
  // disable
  scml_bitfield_container( const scml_bitfield_container & );
  scml_bitfield_container & operator= ( const scml_bitfield_container & );

private:
  // data members
  typedef ::std::vector< scml_bitfield_container_entry > container_type;
  typedef container_type::iterator iterator_type;
  typedef container_type::const_iterator const_iterator_type;

  container_type fields;
};

#endif
