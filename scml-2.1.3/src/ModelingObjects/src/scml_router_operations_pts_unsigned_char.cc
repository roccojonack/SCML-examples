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
 * Purpose of file : Definition of scml_memory modeling object
 *
 */

#include "scmlinc/scml_router_operations.h"

/************************************************************************
 * constructors for forward migration
 * behaviour is do as value_type does
 */

scml_router_operations< unsigned char >::
scml_router_operations() :
  scml_router_operations_podt_common< unsigned char >()
{
}


/************************************************************************
 * named default
 */

scml_router_operations< unsigned char >::
scml_router_operations( const char * n ) :
  scml_router_operations_podt_common< unsigned char >( n)
{
}

/************************************************************************
 * constructors for memory array
 */

scml_router_operations< unsigned char >::
scml_router_operations( scml_memsize a ) :
  scml_router_operations_podt_common< unsigned char >( a )
{
}


scml_router_operations< unsigned char >::
scml_router_operations( const char * n,
                        scml_memsize a ) :
  scml_router_operations_podt_common< unsigned char >( n, a )
{
}

/************************************************************************
 * virtual getter setter for instrumentation
 *
 * see scml_memory_base.h
 */

scml_memory_base::ErrorCode
scml_router_operations< unsigned char >::
getRegisterValueUint8( uint8 & result,
                       uint64 elementIndex)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  result = this->readDebug( i);
  return scml_memory_base::noError;
}


scml_memory_base::ErrorCode
scml_router_operations< unsigned char >::
setRegisterValueUint8( uint8 result,
                       uint64 elementIndex)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  this->writeDebug( result, i);
  return scml_memory_base::noError;
}


scml_memory_base::ErrorCode
scml_router_operations< unsigned char >::
getRegisterValueVecUint8( ::std::vector< uint8 > & result,
                          uint64 elementIndex,
                          uint32 elementCount
                          ) 
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  const size_type iEnd( i + elementCount );
  if( !isValidIndex( iEnd - 1)) {
    return scml_memory_base::errorInvalidIndex;
  }  
  result.clear();
  result.reserve( elementCount);
  for( ; i != iEnd; ++i ) {
    result.push_back( this->readDebug( i));
  }
  return scml_memory_base::noError;
}
