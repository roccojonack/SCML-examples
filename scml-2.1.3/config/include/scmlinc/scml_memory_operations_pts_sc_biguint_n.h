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

#ifndef SCML_MEMORY_OPERATIONS_PTS_SC_BIGUINT_N_H
#define SCML_MEMORY_OPERATIONS_PTS_SC_BIGUINT_N_H

#include <string>

/************************************************************************
 * partial template specialisation
 *
 * see scml_memory.h 
 *
 */

template <int N> 
class scml_memory_operations< sc_dt::sc_biguint<N> > : 
  public scml_memory_operations_podt_common< sc_dt::sc_biguint<N> >
{
public:
  typedef sc_dt::sc_biguint<N> value_type;
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

  typedef scml_memory_base::TypeID TypeID;

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

   std::string getDocumentationImp() const;

public:
  // virtuals queries for clients for scml_memory_base
  //FIXME
  virtual TypeID getType() const { return scml_memory_base::MEM_TYPE_BIGUINT; }
  virtual bool isWriteable() const { return true; }
  virtual const char * getDocumentation() const;
  
  // virtual getter setter for instrumentation
  //FIXME
};

template <int N>
inline typename scml_memory_operations< sc_dt::sc_biguint<N> >::this_reference_type
scml_memory_operations< sc_dt::sc_biguint<N> >::operator= ( value_type a )
{
  this->put( a);
  return *this;
}

#endif
