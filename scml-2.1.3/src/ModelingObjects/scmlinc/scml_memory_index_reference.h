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
 * Purpose of file : Definition of scml_memory reference compositor
 *
 */

#ifndef SCML_MEMORY_INDEX_REFERENCE_H
#define SCML_MEMORY_INDEX_REFERENCE_H

#include "scmlinc/scml_memory_operations.h"

/************************************************************************
 * Defined here
 */
template< typename DT > class scml_memory_index_reference;

/************************************************************************
 * Summary of non included knowledge
 */
template< typename DT > class scml_memory;
template< typename DT > class scml_memory_iterator;

/************************************************************************
 * Generic Template
 */
template< typename DT > class scml_memory_index_reference {
public:
  typedef DT value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef unsigned long long size_type;
  typedef ptrdiff_t difference_type;

  typedef scml_memory_index_reference< value_type > this_type;
  typedef this_type & this_reference_type;
  typedef const this_type & const_this_reference_type;

  // constructor
  scml_memory_index_reference( scml_memory< DT > * p, size_type i );

  // defaults OK
  // ~scml_memory_index_reference();  
  // scml_memory_index_reference( const scml_memory_index_reference & );

  // assignment
  // this_reference_type operator=( const scml_memory_operations< DT > & );
  this_reference_type operator=( value_type );

  // primitive variable behaviour
  operator value_type() const { return mp->get( index ); }

  this_reference_type operator= (const_this_reference_type );

  this_reference_type operator += ( value_type );
  this_reference_type operator -= ( value_type );
  this_reference_type operator /= ( value_type );
  this_reference_type operator *= ( value_type );
  this_reference_type operator %= ( value_type );
  this_reference_type operator ^= ( value_type );
  this_reference_type operator &= ( value_type );
  this_reference_type operator |= ( value_type );
  this_reference_type operator <<= ( value_type );
  this_reference_type operator >>= ( value_type );

  scml_memory_iterator<DT> operator& ();

  // read & write
  value_type read();
  void write( value_type );

private:
  // disable
  scml_memory_index_reference();

private:
  // data member
  scml_memory< DT > * mp;
  size_type index ;
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */
template< typename DT >
inline
scml_memory_index_reference< DT >::
scml_memory_index_reference( scml_memory< DT > * p, size_type i ) :
  mp( p),
  index( i ) 
{
}  

/************************************************************************
 * 
 */

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator=( value_type a )
{ 
  mp->put( a, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator= (const_this_reference_type v)
{
  *this = (value_type)v;
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator += ( value_type a ) {
  value_type b( mp->get( index ));
  b += a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator -= ( value_type a ) {
  value_type b( mp->get( index ));
  b -= a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator /= ( value_type a ) {
  value_type b( mp->get( index ));
  b /= a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator *= ( value_type a ) {
  value_type b( mp->get( index ));
  b *= a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator %= ( value_type a ) {
  value_type b( mp->get( index ));
  b %= a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator ^= ( value_type a ) {
  value_type b( mp->get( index ));
  b ^= a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator &= ( value_type a ) {
  value_type b( mp->get( index ));
  b &= a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator |= ( value_type a ) {
  value_type b( mp->get( index ));
  b |= a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator <<= ( value_type a ) {
  value_type b( mp->get( index ));
  b <<= a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
typename scml_memory_index_reference< DT >::this_reference_type
scml_memory_index_reference< DT >::operator >>= ( value_type a ) {
  value_type b( mp->get( index ));
  b >>= a;
  mp->put( b, index );
  return *this;
}

template< typename DT >
inline
scml_memory_iterator< DT >
scml_memory_index_reference< DT >::operator& ()
{
  return scml_memory_iterator<DT>(mp, index);
}


template< typename DT >
inline
typename scml_memory_index_reference< DT >::value_type
scml_memory_index_reference< DT >::read()
{
  return mp->read( index);
}

template< typename DT >
inline  
void 
scml_memory_index_reference< DT >::write( value_type v )
{
  mp->write( v, index);
}

#endif
