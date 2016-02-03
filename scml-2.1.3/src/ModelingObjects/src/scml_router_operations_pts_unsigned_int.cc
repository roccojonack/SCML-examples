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

scml_router_operations< unsigned int >::
scml_router_operations() :
  scml_router_operations_podt_common< unsigned int >()
{
}


/************************************************************************
 * named default
 */

scml_router_operations< unsigned int >::
scml_router_operations( const char * n ) :
  scml_router_operations_podt_common< unsigned int >( n)
{
}

/************************************************************************
 * constructors for memory array
 */

scml_router_operations< unsigned int >::
scml_router_operations( scml_memsize a ) :
  scml_router_operations_podt_common< unsigned int >( a )
{
}


scml_router_operations< unsigned int >::
scml_router_operations( const char * n,
                        scml_memsize a ) :
  scml_router_operations_podt_common< unsigned int >( n, a )
{
}

/************************************************************************
 * virtual getter setter for instrumentation
 *
 * see scml_memory_base.h
 */

scml_memory_base::ErrorCode
scml_router_operations< unsigned int >::
getRegisterValueUint32( uint32 & result,
                        uint64 elementIndex)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  result = 0;
  for (unsigned int byte = 0; byte < 4; ++byte) {
    result |= (this->readDebug( i, 8, byte * 8) << (byte * 8));
  }
  return scml_memory_base::noError;
}


scml_memory_base::ErrorCode
scml_router_operations< unsigned int >::
setRegisterValueUint32( uint32 result, uint64 elementIndex)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  for (unsigned int byte = 0; byte < 4; ++byte) {
    this->writeDebug( result >> (byte * 8), i, 8, byte * 8);
  }
  return scml_memory_base::noError;
}


scml_memory_base::ErrorCode
scml_router_operations< unsigned int >::
getRegisterValueVecUint32( ::std::vector< uint32 > & result,
                           uint64 elementIndex,
                           uint32 elementCount) 
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
    uint32 tmp = 0;
    for (unsigned int byte = 0; byte < 4; ++byte) {
      tmp |= (this->readDebug( i, 8, byte * 8) << (byte * 8));
    }
    result.push_back( tmp);
  }
  return scml_memory_base::noError;
}

#if __WORDSIZE != 64

scml_memory_base::ErrorCode
scml_router_operations< unsigned int >::
getRegisterValueUint32( unsigned long int & result,
                        uint64 elementIndex)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  result = 0;
  for (unsigned int byte = 0; byte < 4; ++byte) {
    result |= (this->readDebug( i, 8, byte * 8) << (byte * 8));
  }
  return scml_memory_base::noError;
}

scml_memory_base::ErrorCode
scml_router_operations< unsigned int >::
getRegisterValueVecUint32( ::std::vector< unsigned long int > & result,
                           uint64 elementIndex,
                           uint32 elementCount) 
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
    unsigned long int tmp = 0;
    for (unsigned int byte = 0; byte < 4; ++byte) {
      tmp |= (this->readDebug( i, 8, byte * 8) << (byte * 8));
    }
    result.push_back( tmp);
  }
  return scml_memory_base::noError;
}

#endif
