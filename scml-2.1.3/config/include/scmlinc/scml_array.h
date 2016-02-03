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
 * Purpose of file : 
 *
 */

#ifndef SCML_ARRAY_H
#define SCML_ARRAY_H

#include "scmlinc/scml_types.h"
#include "scmlinc/scml_array_base.h"
#include "scmlinc/scml_memory_utils.h"

template< typename DT>
class scml_array : public scml_array_base {
public:
  typedef DT value_type;
  typedef value_type * pointer;
  typedef const value_type * const_pointer;
  typedef value_type * iterator;
  typedef const value_type * const_iterator;
  typedef value_type & reference;
  typedef const value_type & const_reference;
  typedef scml_array_base::size_type size_type;
  typedef scml_array_base::generic_data_pointer_type generic_data_pointer_type;

protected:
  explicit scml_array( size_type n );
public:
  scml_array( value_type * p, size_type n );
  scml_array(const char* name, value_type* p, size_type n);
  virtual ~scml_array();  

  // data access
  const_reference operator[] ( size_type ) const;
  reference operator[] ( size_type a );
  // TODO FIXME add PTS for scml_memory<> & use index_reference
  
  virtual bool get( generic_data_pointer_type destination, size_type index,  
		    unsigned int acSiz, unsigned int offSet) const;
  virtual bool get( generic_data_pointer_type destination, size_type index) const;
  virtual bool put( generic_data_pointer_type source, size_type index);
  virtual bool put( generic_data_pointer_type source, size_type index,
		    unsigned int acSiz, unsigned int offSet);

  pointer getStoragePointer() const;
  generic_data_pointer_type get_storage_pointer() const;

protected:
  void setStoragePointer( pointer);

private:
  // disable
  scml_array( const scml_array & );
  scml_array & operator= ( const scml_array & );

private:
  // data members
  pointer mStorage; // NOT owner
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */

template< typename DT >
inline
scml_array< DT>::
scml_array( value_type * p, size_type n ) :
  scml_array_base( n),
  mStorage( p)
{
}

template< typename DT >
inline
scml_array< DT>::
scml_array(const char* name, value_type* p, size_type n) :
  scml_array_base(name, n),
  mStorage( p)
{
}

template< typename DT >
inline
scml_array< DT>::
scml_array( size_type n ) :
  scml_array_base( n),
  mStorage( 0)
{
}

template< typename DT >
inline
scml_array< DT>::
~scml_array()
{
}

/************************************************************************
 * data access
 */

template< typename DT >
inline
typename scml_array< DT>::const_reference
scml_array< DT>::
operator[] ( size_type i ) const
{
  return mStorage[ i];
}

template< typename DT >
inline
typename scml_array< DT>::reference
scml_array< DT>::
operator[] ( size_type i )
{  
  return mStorage[ i];
}

template< typename DT >
inline
typename scml_array< DT>::generic_data_pointer_type
scml_array< DT>::
get_storage_pointer() const
{
  return mStorage;
}

template< typename DT >
inline
typename scml_array< DT>::pointer 
scml_array< DT>::
getStoragePointer() const
{
  return mStorage;
}

template< typename DT >
inline
void
scml_array< DT>::
setStoragePointer( pointer p)
{
  mStorage = p;
}

template< typename DT >
inline
bool
scml_array< DT>::
get( generic_data_pointer_type destination, size_type index ) const
{
  pointer tmp = static_cast< pointer>( destination);
  *tmp = this->operator[]( index);
  return true;
}

template< typename DT >
inline
bool
scml_array< DT>::
get( generic_data_pointer_type destination, size_type index,  
     unsigned int acSiz, unsigned int offSet) const
{
  if( acSiz > (8 * scml::sizeOf<value_type>())) {
    return false;
  }
  switch( acSiz ) {
  case 8:
    {
      unsigned char * tmp = static_cast< unsigned char *>( destination);
      const unsigned char tmpVal =
        scml::convert<value_type, unsigned char>(this->operator[]( index) >> offSet) &
	scml_memory_utils::getBitsMask<unsigned char>(acSiz);
      *tmp = tmpVal; 
    }
    return true;

  case 16:
    {
      unsigned short * tmp = static_cast< unsigned short *>( destination);
      const unsigned short tmpVal =
        scml::convert<value_type, unsigned short>(this->operator[]( index) >> offSet) &
	scml_memory_utils::getBitsMask<unsigned short>(acSiz);
      *tmp = tmpVal; 
    }
    return true;

  case 32:
    {
      unsigned int * tmp = static_cast< unsigned int *>( destination);
      const unsigned int tmpVal =
        scml::convert<value_type, unsigned int>(this->operator[]( index) >> offSet) &
	scml_memory_utils::getBitsMask<unsigned int>(acSiz);
      *tmp = tmpVal; 
    }
    return true;    

  case 64:
    {
      unsigned long long * tmp = static_cast< unsigned long long *>( destination);
      const unsigned long long tmpVal =
        scml::convert<value_type, unsigned long long>(this->operator[]( index) >> offSet) &
	scml_memory_utils::getBitsMask<unsigned long long>(acSiz);
      *tmp = tmpVal; 
    }
    return true;

  case 128:
    {
      sc_dt::sc_biguint<128> * tmp = static_cast< sc_dt::sc_biguint<128> *>( destination);
      *tmp =
        scml::convert<value_type, sc_dt::sc_biguint<128> >(this->operator[]( index) >> offSet) &
        scml_memory_utils::getBitsMask<sc_dt::sc_biguint<128> >(acSiz);
    }
    return true;

  case 256:
    {
      sc_dt::sc_biguint<256> * tmp = static_cast< sc_dt::sc_biguint<256> *>( destination);
      *tmp =
        scml::convert<value_type, sc_dt::sc_biguint<256> >(this->operator[]( index) >> offSet) &
        scml_memory_utils::getBitsMask<sc_dt::sc_biguint<256> >(acSiz);
    }
    return true;

  case 512:
    {
      sc_dt::sc_biguint<512> * tmp = static_cast< sc_dt::sc_biguint<512> *>( destination);
      *tmp =
        scml::convert<value_type, sc_dt::sc_biguint<512> >(this->operator[]( index) >> offSet) &
        scml_memory_utils::getBitsMask<sc_dt::sc_biguint<512> >(acSiz);
    }
    return true;

  default:
    break;
  }
  return false;
}

template< typename DT >
inline
bool
scml_array< DT>::
put( generic_data_pointer_type source, size_type index)
{
  pointer tmp = static_cast< pointer>( source);
  this->operator[]( index) = *tmp;
  return true;
}

template< typename DT >
inline
bool
scml_array< DT>::
put( generic_data_pointer_type source, size_type index,
     unsigned int acSiz, unsigned int offSet)
{
  if( acSiz > (8 * scml::sizeOf<value_type>())) {
    return false;
  }
  value_type a;
  switch( acSiz ) {
  case 8:
    a = scml::convert<unsigned char, value_type>(*(static_cast<unsigned char*>(source)));
    break;
  case 16:
    a = scml::convert<unsigned short, value_type>(*(static_cast<unsigned short*>(source)));
    break;
  case 32:
    a = scml::convert<unsigned int, value_type>(*(static_cast<unsigned int*>(source)));
    break;
  case 64:
    a = scml::convert<unsigned long long, value_type>(*(static_cast<unsigned long long*>(source)));
    break;
  case 128:
    a = scml::convert<sc_dt::sc_biguint<128>, value_type>(*(static_cast<sc_dt::sc_biguint<128>*>(source)));
    break;
  case 256:
    a = scml::convert<sc_dt::sc_biguint<256>, value_type>(*(static_cast<sc_dt::sc_biguint<256>*>(source)));
    break;
  case 512:
    a = scml::convert<sc_dt::sc_biguint<512>, value_type>(*(static_cast<sc_dt::sc_biguint<512>*>(source)));
    break;
  default: 
    return false;
  }
  const value_type mask( scml_memory_utils::getBitsMask<value_type>(acSiz));
  const value_type zeroMask( ~(mask << offSet));
  const value_type update( (a & mask) << offSet);
  const value_type untouched( zeroMask & this->operator[]( index ));
  this->operator[]( index) = update | untouched; 
  return true;
}

#endif
