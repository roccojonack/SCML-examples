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

#include "scmlinc/scml_memory_operations.h"

/************************************************************************
 * constructors for forward migration
 * behaviour is do as value_type does
 */

scml_memory_operations< signed long long >::
scml_memory_operations() :
  scml_memory_operations_podt_common< signed long long >()
{
}


scml_memory_operations< signed long long >::
scml_memory_operations( value_type a ) :
  scml_memory_operations_podt_common< signed long long >( a)
{
}

/************************************************************************
 * named default
 */

scml_memory_operations< signed long long >::
scml_memory_operations( const char * n ) :
  scml_memory_operations_podt_common< signed long long >( n)
{
}

/************************************************************************
 * constructors for memory array
 */

scml_memory_operations< signed long long >::
scml_memory_operations( scml_memsize a ) :
  scml_memory_operations_podt_common< signed long long >( a )
{
}


scml_memory_operations< signed long long >::
scml_memory_operations( const char * n,
			scml_memsize a ) :
  scml_memory_operations_podt_common< signed long long >( n, a )
{
}

/************************************************************************
 * alias constructors
 */

scml_memory_operations< signed long long >::
scml_memory_operations( scml_memory_operations & a, 
			size_type offset, size_type size ) :
  scml_memory_operations_podt_common< signed long long >( a, offset, size )
{
}


scml_memory_operations< signed long long >::
scml_memory_operations( const char * n,
			scml_memory_operations & a, 
			size_type offset, size_type size ) :
  scml_memory_operations_podt_common< signed long long >( n, a, offset, size )
{
}

/************************************************************************
 * virtual getter setter for instrumentation
 *
 * see scml_memory_base.h
 */

scml_memory_base::ErrorCode
scml_memory_operations< signed long long >::
getRegisterValueInt64(int64 & result, uint64 elementIndex)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  result = getDebug(i);
  return scml_memory_base::noError;
}


scml_memory_base::ErrorCode
scml_memory_operations< signed long long >::
setRegisterValueInt64(int64 result, uint64 elementIndex)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  putDebug(result, i);
  return scml_memory_base::noError;
}


scml_memory_base::ErrorCode
scml_memory_operations< signed long long >::
getRegisterValueVecInt64(::std::vector< int64 > & result,
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
    result.push_back(getDebug(i));
  }
  return scml_memory_base::noError;
}

#if __WORDSIZE == 64

scml_memory_base::ErrorCode
scml_memory_operations< signed long long >::
getRegisterValueInt64(signed long int & result, uint64 elementIndex)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  result = getDebug(i);
  return scml_memory_base::noError;
}

scml_memory_base::ErrorCode
scml_memory_operations< signed long long >::
getRegisterValueVecInt64(::std::vector< signed long int > & result,
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
    result.push_back(getDebug(i));
  }
  return scml_memory_base::noError;
}

#endif  
