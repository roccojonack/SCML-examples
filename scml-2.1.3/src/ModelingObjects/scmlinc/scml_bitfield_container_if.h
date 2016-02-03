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
 * Purpose of file : Definition of interface for adding a bitfield
 *
 */

#ifndef SCML_BITFIELD_CONTAINER_IF_H
#define SCML_BITFIELD_CONTAINER_IF_H

#include "scmlinc/scml_bitfield_base.h"

class scml_bitfield_container_if {
public: 
  typedef scml_bitfield_base::size_type size_type;
  typedef scml_bitfield_base::data_type data_type;
  typedef scml_bitfield_base::value_type value_type;
  typedef scml_bitfield_base::scml_bitfield_container_entry scml_bitfield_container_entry;

public: 
  virtual bool registerBitfields( scml_bitfield_container_entry ) = 0;
  virtual bool updateReadBlockingProperty( bool isBlocking ) = 0;
  virtual bool updateWriteBlockingProperty( bool isBlocking ) = 0;
  virtual value_type getBitfieldValue( size_type offset, size_type size) = 0;
  virtual void setBitfieldValue( value_type a, size_type offset, size_type size) = 0;

protected:
  scml_bitfield_container_if() {}
  virtual ~scml_bitfield_container_if() {}
private:
  // disable
  scml_bitfield_container_if( const scml_bitfield_container_if & );
  scml_bitfield_container_if & operator= ( const scml_bitfield_container_if & );
};

#endif
