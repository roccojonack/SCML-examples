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

#ifndef SCML_MEMORY_H
#define SCML_MEMORY_H

#include "scmlinc/scml_memory_index_reference.h"
#include "scmlinc/scml_memory_iterator.h"

/************************************************************************
 * scml_memory defined here
 */

template< typename DT > class scml_memory;

/************************************************************************
 * partial template specialisation
 *
 */

#define SCML_MEMORY_PTS_FOR_PODT(ptype)\
\
template< > \
class scml_memory< ptype > : public scml_memory_operations< ptype > { \
public: \
  typedef ptype value_type; \
  typedef value_type* pointer; \
  typedef const value_type* const_pointer; \
  typedef value_type* iterator; \
  typedef const value_type* const_iterator; \
  typedef value_type& reference; \
  typedef const value_type& const_reference; \
  typedef unsigned long long size_type; \
  typedef ptrdiff_t difference_type; \
 \
  typedef scml_memory< value_type > this_type; \
  typedef this_type & this_reference_type; \
 \
  typedef scml_memory_pv32_if::request_type request32_type ; \
  typedef scml_memory_pv32_if::response_type response32_type; \
 \
  scml_memory() {} \
  explicit scml_memory( value_type ); \
  explicit scml_memory( const ::std::string & n ); \
  explicit scml_memory( const char * n ); \
  explicit scml_memory( scml_memsize ); \
  scml_memory( const ::std::string & n, scml_memsize s); \
  scml_memory( const char * n, scml_memsize s); \
  virtual ~scml_memory() {} \
 \
private: \
  /* disabled default implementation */ \
  scml_memory( const scml_memory &); \
public: \
  this_reference_type operator=( const scml_memory & ); \
  this_reference_type operator=( value_type ); \
 \
  scml_memory( scml_memory & a, size_type offset, size_type size ); \
  scml_memory( const char * n, scml_memory & a, size_type offset, size_type size ); \
  scml_memory( const ::std::string &, scml_memory & a, size_type offset, size_type size ); \
 \
  scml_memory_index_reference< value_type > operator[] ( size_type ); \
\
  scml_memory_iterator< value_type > begin(); \
  scml_memory_iterator< value_type > end(); \
\
}; \
 \
inline scml_memory< ptype >::scml_memory( value_type a ) : \
  scml_memory_operations< ptype > ( a )\
{} \
 \
inline \
scml_memory< ptype >::scml_memory( const char * n ) : \
  scml_memory_operations< ptype > ( n )\
{} \
 \
inline \
scml_memory< ptype >::scml_memory( const ::std::string & n ) : \
  scml_memory_operations< ptype > ( n.c_str()) \
{} \
 \
inline \
scml_memory< ptype >::scml_memory( scml_memsize a ) : \
  scml_memory_operations< ptype > ( a ) \
{} \
 \
inline \
scml_memory< ptype >::scml_memory( const char * n, scml_memsize a ) : \
  scml_memory_operations< ptype > ( n, a ) \
{} \
 \
inline \
scml_memory< ptype >::scml_memory( const ::std::string & n, scml_memsize a ) : \
  scml_memory_operations< ptype > ( n.c_str(), a ) \
{} \
 \
inline scml_memory< ptype >:: \
scml_memory( scml_memory & a, size_type offset, size_type size ) : \
  scml_memory_operations< ptype > ( a, offset, size ) \
{} \
 \
inline scml_memory< ptype >:: \
scml_memory( const char * n, scml_memory & a, size_type offset, size_type size ) : \
  scml_memory_operations< ptype > ( n, a, offset, size ) \
{} \
 \
inline scml_memory< ptype >:: \
scml_memory( const ::std::string & n,\
	     scml_memory & a,\
	     size_type offset,\
	     size_type size ) : \
  scml_memory_operations< ptype > ( n.c_str(), a, offset, size ) \
{} \
 \
inline scml_memory< ptype >::this_reference_type \
scml_memory< ptype >::operator= ( const scml_memory & a ) \
{ \
  scml_memory_operations< ptype >::operator= ( value_type( a)); return *this; \
} \
 \
inline scml_memory< ptype >::this_reference_type \
scml_memory< ptype >::operator= ( value_type a ) \
{ \
  scml_memory_operations< ptype >::operator= ( a ); return *this; \
} \
 \
inline \
scml_memory_index_reference< scml_memory< ptype >::value_type > \
scml_memory< ptype >::operator[] ( size_type a ) \
{ \
  scml_memory_index_reference< value_type > c( this, a); \
  return c; \
} \
 \
inline \
scml_memory_iterator< scml_memory< ptype >::value_type > \
scml_memory< ptype >::begin ( ) \
{ \
  scml_memory_iterator< value_type > c( this, 0); \
  return c; \
} \
 \
inline \
scml_memory_iterator< scml_memory< ptype >::value_type > \
scml_memory< ptype >::end ( ) \
{ \
  scml_memory_iterator< value_type > c( this, size()); \
  return c; \
} \

SCML_MEMORY_PTS_FOR_PODT(bool);
SCML_MEMORY_PTS_FOR_PODT(char);
// SCML_MEMORY_PTS_FOR_PODT(float);
// SCML_MEMORY_PTS_FOR_PODT(double);
// SCML_MEMORY_PTS_FOR_PODT(long double);

SCML_MEMORY_PTS_FOR_PODT(signed char);
SCML_MEMORY_PTS_FOR_PODT(signed short int);
SCML_MEMORY_PTS_FOR_PODT(signed int);
SCML_MEMORY_PTS_FOR_PODT(signed long int);
SCML_MEMORY_PTS_FOR_PODT(signed long long);

SCML_MEMORY_PTS_FOR_PODT(unsigned char);
SCML_MEMORY_PTS_FOR_PODT(unsigned short int);
SCML_MEMORY_PTS_FOR_PODT(unsigned int);
SCML_MEMORY_PTS_FOR_PODT(unsigned long int);
SCML_MEMORY_PTS_FOR_PODT(unsigned long long);

SCML_MEMORY_PTS_FOR_PODT(sc_dt::sc_biguint<128>);
SCML_MEMORY_PTS_FOR_PODT(sc_dt::sc_biguint<256>);
SCML_MEMORY_PTS_FOR_PODT(sc_dt::sc_biguint<512>);

#undef SCML_MEMORY_PTS_FOR_PODT

/************************************************************************
 * Generic Template
 */

// template< typename DT > 
// class scml_memory : public scml_memory_operations< DT > {
// private:
//   // disable
//   scml_memory();
//   virtual ~scml_memory();
//   scml_memory( const scml_memory & );
//   scml_memory & operator= ( const scml_memory & );
// };

#endif
