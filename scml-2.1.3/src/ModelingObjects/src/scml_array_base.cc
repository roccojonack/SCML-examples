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

#include "scml_array_base.h"

scml_array_base::scml_array_base( size_type n ) :
  sc_object( sc_gen_unique_name( "scml_array" )),
  mLockedSpace( n, false ),
  mValidData( n, false ),
  m_last_released_data_index( 0),
  m_last_released_data_length( 0),
  m_last_released_space_index( 0),
  m_last_released_space_length( 0)
{
}

scml_array_base::scml_array_base(const char* name, size_type n) :
  sc_object(name),
  mLockedSpace( n, false ),
  mValidData( n, false ),
  m_last_released_data_index( 0),
  m_last_released_data_length( 0),
  m_last_released_space_index( 0),
  m_last_released_space_length( 0)
{
}

scml_array_base::~scml_array_base()
{
}

/************************************************************************
 * non-blocking synchronization claim space
 */

bool
scml_array_base::nb_can_claim_space( size_type index, size_type length ) const
{
  return !isLockedSpaceAtLeastOne( index, length);
}

bool 
scml_array_base::nb_claim_space( size_type index, size_type length )
{
  if( nb_can_claim_space( index, length )) {
    return lockSpace( index, length);
  }    
  return false;    
}

const sc_event &
scml_array_base::ok_to_claim_space() const
{
  return m_ok_to_claim_space;
}

/************************************************************************
 * non-blocking synchronization claim data
 */

bool 
scml_array_base::nb_can_claim_data( size_type index, size_type length ) const
{
  return isValidDataAll( index, length);
}

bool 
scml_array_base::nb_claim_data( size_type index, size_type length )
{
  if( nb_can_claim_data( index, length )) {
    return setDataInvalid( index, length);
  }
  return false;
}

const sc_event & 
scml_array_base::ok_to_claim_data() const
{
  return m_ok_to_claim_data;
}

/************************************************************************
 * non-blocking synchronization release
 */

bool 
scml_array_base::nb_release_data( size_type index, size_type length )
{
  m_last_released_data_index = index;
  m_last_released_data_length = length;
  setDataValid(index, length );
  m_ok_to_claim_data.notify( SC_ZERO_TIME );
  notify_claim_data_subscribers();
  return true;
}

bool 
scml_array_base::nb_release_space( size_type index, size_type length )
{
  m_last_released_space_index = index;
  m_last_released_space_length = length;
  unlockSpace( index, length );
  m_ok_to_claim_space.notify( SC_ZERO_TIME );
  notify_claim_space_subscribers();  
  return true;
}

/************************************************************************
 * blocking synchronization release
 */

void
scml_array_base::claim_data( size_type index, size_type length)
{
  while( !nb_claim_data( index, length)) {
    wait( m_ok_to_claim_data);
  }
}

void
scml_array_base::claim_space( size_type index, size_type length)
{
  while( !nb_claim_space( index, length)) {
    wait( m_ok_to_claim_space);
  }
}

/************************************************************************
 * lock space helpers
 */
bool
scml_array_base::lockSpace( size_type index, size_type length)
{
  for( size_type i( index), n( index + length); i < n; ++i) {
    mLockedSpace[ i] = true;
  }
  return true;  
}

bool
scml_array_base::isLockedSpace( size_type index ) const
{
  return mLockedSpace[ index];
}

bool
scml_array_base::isLockedSpaceAtLeastOne( size_type index, size_type length) const
{
  for( size_type i( index), n( index + length); i < n; ++i) {
    if( mLockedSpace[ i]) {
      return true;
    }
  }
  return false;  
}

bool
scml_array_base::isLockedSpaceAll( size_type index, size_type length) const
{
  for( size_type i( index), n( index + length); i < n; ++i) {
    if( !mLockedSpace[ i]) {
      return false;
    }
  }
  return true;  
}

bool
scml_array_base::unlockSpace( size_type index, size_type length)
{
  for( size_type i( index), n( index + length); i < n; ++i) {
    mLockedSpace[ i] = false;
  }
  return true;
}

/************************************************************************
 * data
 */
bool 
scml_array_base::setDataValid( size_type index, size_type length )
{
  for( size_type i( index), n( index + length); i < n; ++i) {
    mValidData[ i] = true;
  }
  return true;  
}

bool
scml_array_base::isValidData( size_type index ) const
{
  return mValidData[ index];
}

bool
scml_array_base::isValidDataAll( size_type index, size_type length) const
{
  for( size_type i( index), n( index + length); i < n; ++i) {
    if( !mValidData[ i]) {
      return false;
    }
  }
  return true;
}

bool
scml_array_base::isValidDataAtLeastOne( size_type index, size_type length) const
{
  for( size_type i( index), n( index + length); i < n; ++i) {
    if( mValidData[ i]) {
      return true;
    }
  }
  return false;
}

bool
scml_array_base::setDataInvalid( size_type index, size_type length )
{
  for( size_type i( index), n( index + length); i < n; ++i) {
    mValidData[ i] = false;
  }
  return true;
}

/************************************************************************
 * subscribe to claim notification
 */
void 
scml_array_base::subscribe_claim_data( subscribers_type a )
{
  mClaimDataSubscribers.insert( a);
}

void 
scml_array_base::subscribe_claim_space( subscribers_type a )
{
  mClaimSpaceSubscribers.insert( a);
}

void 
scml_array_base::notify_claim_data_subscribers()
{
  for( subscribers_iterator_type
	 it  = mClaimDataSubscribers.begin(),
	 end = mClaimDataSubscribers.end();
       it != end;
       ++it) {
    (*it)->claim_data_notification( this);  
  }
}

void 
scml_array_base::notify_claim_space_subscribers()
{
  for( subscribers_iterator_type
	 it  = mClaimSpaceSubscribers.begin(),
	 end = mClaimSpaceSubscribers.end();
       it != end; 
       ++it) {
      (*it)->claim_space_notification( this);  
    }
}

/************************************************************************
 * queries
 */
scml_array_base::size_type
scml_array_base::get_size() const
{
  return mLockedSpace.size();
}

/************************************************************************
 * default (stubbed) implementation for get and put
 */
bool 
scml_array_base::get( generic_data_pointer_type, size_type, unsigned int, unsigned int) const
{
  return false;
}

bool
scml_array_base::get( generic_data_pointer_type, size_type) const
{
  return false;
}

bool
scml_array_base::put( generic_data_pointer_type, size_type)
{
  return false;
}

bool 
scml_array_base::put( generic_data_pointer_type, size_type, unsigned int, unsigned int)
{
  return false;
}

scml_array_base::generic_data_pointer_type
scml_array_base::get_storage_pointer() const
{
  return NULL;
}

/************************************************************************
 * repackage
 */
void
scml_array_base::repackage( size_type destIndex,
			    unsigned int destDataSize,			    
			    this_reference_type srcArray,
			    size_type srcIndex,
			    unsigned int srcDataSize,
			    unsigned int srcDataElements )
{
  this_reference_type destArray( *this );
  const unsigned int destDataElements = srcDataElements * srcDataSize / destDataSize;
  srcArray.claim_data( srcIndex, srcDataElements);
  destArray.claim_space( destIndex, destDataElements);

  for( unsigned int i = 0; i < srcDataElements; ++i) {
    for( unsigned int j = 0; j < srcDataSize / 8; ++j) {
      unsigned char temp;
      srcArray.get( &temp, srcIndex + i, 8, 8 * j);
      destArray.put( &temp, destIndex + (i * srcDataSize / 8 + j) / (destDataSize / 8),
                     8, 8 * ((i * srcDataSize / 8 + j) % (destDataSize / 8)));
    }
  }

  destArray.nb_release_data( destIndex, destDataElements);
  srcArray.nb_release_space( srcIndex, srcDataElements);
}

/************************************************************************
 * get info over last release
 */
scml_array_base::size_type
scml_array_base::get_last_released_data_index() const
{
  return m_last_released_data_index;
}

scml_array_base::size_type
scml_array_base::get_last_released_data_length() const
{
  return m_last_released_data_length;
}

scml_array_base::size_type
scml_array_base::get_last_released_space_index() const
{
  return m_last_released_space_index;
}

scml_array_base::size_type
scml_array_base::get_last_released_space_length() const
{
  return m_last_released_space_length;
}

/************************************************************************
 * sc_object queries
 */

void scml_array_base::print(::std::ostream & os) const
{
  os << ::std::dec << "Space claimed:";
  const size_type n( this->get_size());
  for( size_type i( 0); i < n; ++i) {
    if( isLockedSpace( i )) {
      os << " " << i;      
    }
  }
  os << ::std::endl << "Data released:";
  for( size_type i( 0); i < n; ++i) {
    if( isValidData( i )) {
      os << " " << i;      
    }
  }
}

void scml_array_base::dump(::std::ostream & os) const
{
  print( os);
}

const char * scml_array_base::kind() const
{ 
  return "scml_array";
}
