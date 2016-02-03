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

#ifndef SCML_ROUTER_OPERATIONS_PTS_UNSIGNED_INT_H
#define SCML_ROUTER_OPERATIONS_PTS_UNSIGNED_INT_H

/************************************************************************
 * partial template specialisation
 *
 * see scml_router.h 
 *
 */

template< > 
class scml_router_operations< unsigned int > : 
  public scml_router_operations_podt_common< unsigned int >
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
  virtual TypeID getType() const { return MEM_TYPE_UINT32; }
  //virtual bool isWriteable() const { return true; }
  virtual const char * getDocumentation() const { return "UInt32 Router";}
  
  // virtual getter setter for instrumentation
  virtual ErrorCode getRegisterValueUint32( uint32 & result,
					    uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueUint32( uint32 result,
					    uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueVecUint32( ::std::vector< uint32 > & result,
					       uint64 elementIndex = 0,
					       uint32 elementCount = 1);

#if __WORDSIZE != 64
  // The following methods should be avoided since they are not portable
  // between 32 bit and 64 bit hosts.
  virtual ErrorCode getRegisterValueUint32(unsigned long int & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueVecUint32(::std::vector< unsigned long int > & result,
                                              uint64 elementIndex = 0,
                                              uint32 elementCount = 1);
#endif  
};

#endif
