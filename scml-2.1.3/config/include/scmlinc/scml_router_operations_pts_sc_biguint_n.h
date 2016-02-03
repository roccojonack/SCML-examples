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
 * Purpose of file : Definition of scml_router modeling object
 *
 */

#ifndef SCML_ROUTER_OPERATIONS_PTS_SC_BIGUINT_N_H
#define SCML_ROUTER_OPERATIONS_PTS_SC_BIGUINT_N_H

#include <string>

/************************************************************************
 * partial template specialisation
 *
 * see scml_router.h 
 *
 */

template <int N> 
class scml_router_operations< sc_dt::sc_biguint<N> > : 
  public scml_router_operations_podt_common< sc_dt::sc_biguint<N> >
{
public:
  typedef unsigned int value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef unsigned long long size_type;
  typedef ptrdiff_t difference_type;

  typedef scml_router_operations< value_type > this_type;
  typedef this_type & this_reference_type;

  typedef scml_memory_base::uint64 uint64;

  typedef scml_memory_base::ErrorCode ErrorCode;

  typedef scml_memory_base::TypeID TypeID;

  // constructors & destructor
  scml_router_operations();
  explicit scml_router_operations( const char * n );
  explicit scml_router_operations( scml_memsize );  
  scml_router_operations( const char * n, scml_memsize );
  virtual ~scml_router_operations() {}

private:
  // copy and assignment
  this_reference_type operator=( const scml_router_operations & );
  scml_router_operations( const scml_router_operations & );

  std::string getDocumentationImp() const;

public:
  // virtuals queries for clients for scml_memory_base
  virtual TypeID getType() const { return scml_memory_base::MEM_TYPE_BIGUINT; }
  //virtual bool isWriteable() const { return true; }
  virtual const char * getDocumentation() const;
  
  // FIXME
  // virtual getter setter for instrumentation
};

#endif
