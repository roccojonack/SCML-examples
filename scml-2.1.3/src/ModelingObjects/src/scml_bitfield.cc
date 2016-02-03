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
 * Purpose of file : Implementation of scml_bitfield modeling object
 *
 */

#include "scml_bitfield.h"
#include "scml_memory_utils.h"

scml_bitfield::~scml_bitfield()
{
}

scml_bitfield::scml_bitfield( const char * n,
			      scml_bitfield_container_if & c,
			      size_type offs,
			      size_type siz ) :
  bitFieldName( n),
  container( c),
  offset( offs),
  size( siz),
  readModule( 0),
  rcb( 0),
  readIsBlocking( false ),
  writeModule( 0),
  wcb( 0),
  writeIsBlocking( false )
{
  set_allowed_operations(OPERATIONS_ALLOW_READ | OPERATIONS_ALLOW_WRITE);
  c.registerBitfields( this );
}

/************************************************************************
 * read & write trigger attached call backs
 */
scml_bitfield::value_type 
scml_bitfield::read() const
{
    if (hasRegisteredReadCallBack()) {
	(void)/*return value not used*/((this->readModule)->*(this->rcb) ) ();
    }
    return get();
}

void
scml_bitfield::write( value_type a)
{
  const value_type v(a & scml_memory_utils::getBitsMask<value_type>(getSize()));
  if( hasRegisteredWriteCallBack()) {
      ((this->writeModule)->*(this->wcb) ) ( v);
  } else {
    put( v );
  }
}

/************************************************************************
 * user id info
 */

scml_bitfield::user_id_data_type
scml_bitfield::getReadUserID() const
{
  return readUid;
}  

scml_bitfield::user_id_data_type
scml_bitfield::getWriteUserID() const
{
  return writeUid;
}

/************************************************************************
 * Allowed operations
 */

unsigned int scml_bitfield::get_allowed_operations() const
{
  return m_AllowedOperationsType;
}

void scml_bitfield::set_allowed_operations(unsigned int a)
{
  m_AllowedOperationsType = a;
}

void scml_bitfield::set_read_only()
{
  unsigned int oper(get_allowed_operations() & ~OPERATIONS_ALLOW_WRITE);
  set_allowed_operations(oper);
}

void scml_bitfield::set_write_only()
{
  unsigned int oper(get_allowed_operations() & ~OPERATIONS_ALLOW_READ);
  set_allowed_operations(oper);
}

bool scml_bitfield::is_reading_allowed() const
{
  return (get_allowed_operations() & OPERATIONS_ALLOW_READ);
}

bool scml_bitfield::is_writing_allowed() const
{
  return (get_allowed_operations() & OPERATIONS_ALLOW_WRITE);
}

void scml_bitfield::unregisterReadCB()
{
  readModule = 0;
  rcb = 0;
  readIsBlocking = false;
  mReadCallBackName = "";
  mReadCallBackModuleName = "";
  container.updateReadBlockingProperty( false );
}

void scml_bitfield::unregisterWriteCB()
{
  writeModule = 0;
  wcb = 0;
  writeIsBlocking = false;
  mWriteCallBackName = "";
  mWriteCallBackModuleName = "";
  container.updateWriteBlockingProperty( false );
}
