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

#ifndef SCML_MEMORY_OPERATIONS_PTS_CHAR_H
#define SCML_MEMORY_OPERATIONS_PTS_CHAR_H

/************************************************************************
 * partial template specialisation
 *
 * see scml_memory.h 
 *
 */

template< > 
class scml_memory_operations< char > : 
  public scml_memory_operations_podt_common< char >
{
public:
  typedef char value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef unsigned long long size_type;
  typedef ptrdiff_t difference_type;

  typedef scml_memory_operations< value_type > this_type;
  typedef this_type & this_reference_type;

  typedef scml_memory_base::uint64 uint64;

  typedef scml_memory_base::ErrorCode ErrorCode;

  // constructors & destructor
  scml_memory_operations();
  scml_memory_operations( value_type ); // acceptable conversion
  explicit scml_memory_operations( const char * n );
  explicit scml_memory_operations( scml_memsize );  
  scml_memory_operations( const char * n, scml_memsize );
  virtual ~scml_memory_operations() {}

  // alias constructors
  scml_memory_operations( scml_memory_operations & a,
			  size_type offset, size_type size );
  scml_memory_operations( const char * n,
			  scml_memory_operations & a, 
			  size_type offset, size_type size );

  // value_type variable behaviour
  this_reference_type operator=( value_type );
private:
  // disable copy and assignment
  this_reference_type operator=( const scml_memory_operations & );
  scml_memory_operations( const scml_memory_operations & );

public:
  // virtuals queries for clients for scml_memory_base
  virtual TypeID getType() const ;
  virtual bool isWriteable() const { return true; }
  virtual const char * getDocumentation() const;
  
  // virtual getter setter for instrumentation

#ifdef __CHAR_UNSIGNED__
  virtual ErrorCode getRegisterValueUint8( uint8 & result,
					   uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueUint8( uint8 result,
					   uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueVecUint8( ::std::vector<  uint8 > & result,
					       uint64 elementIndex = 0,
					       uint32 elementCount = 1);
#else
  virtual ErrorCode getRegisterValueInt8( int8 & result,
					  uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueInt8( int8 result,
					  uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueVecInt8( ::std::vector<  int8 > & result,
					     uint64 elementIndex = 0,
					     uint32 elementCount = 1);
#endif
};


inline scml_memory_operations< char >::this_reference_type
scml_memory_operations< char >::operator= ( value_type a )
{
  put( a);
  return *this;
}


#endif // SCML_MEMORY_OPERATIONS_PTS_CHAR_H
