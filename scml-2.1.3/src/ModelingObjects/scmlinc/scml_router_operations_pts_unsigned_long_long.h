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

#ifndef SCML_ROUTER_OPERATIONS_PTS_UNSIGNED_LONG_LONG_H
#define SCML_ROUTER_OPERATIONS_PTS_UNSIGNED_LONG_LONG_H

/************************************************************************
 * partial template specialisation
 *
 * see scml_router.h 
 *
 */

template< > 
class scml_router_operations< unsigned long long > : 
  public scml_router_operations_podt_common< unsigned long long >
{
public:
  typedef unsigned long long value_type;
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

public:
  // virtuals queries for clients for scml_memory_base
  virtual TypeID getType() const { return MEM_TYPE_UINT64; }
  //virtual bool isWriteable() const { return true; }
  virtual const char * getDocumentation() const { return "UInt64 Router";}
  
  // virtual getter setter for instrumentation
  virtual ErrorCode getRegisterValueUint64( uint64 & result,
					    uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueUint64( uint64 result,
					    uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueVecUint64( ::std::vector< uint64 > & result,
					       uint64 elementIndex = 0,
					       uint32 elementCount = 1);
};

#endif
