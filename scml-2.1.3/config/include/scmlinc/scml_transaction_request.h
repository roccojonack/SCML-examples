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

#ifndef SCML_TRANSACTION_REQUEST_H
#define SCML_TRANSACTION_REQUEST_H

#include "PV/PV.h"
#include "scmlinc/scml_types.h"
#include "scmlinc/scml_array_base.h"


#ifdef _WIN32
// avoid macro expansion on Windows
#define SCML_MIN (std::min)
#else
#define SCML_MIN std::min
#endif 

class scml_array_base;

template< typename DT = unsigned int, typename AT = unsigned int>
class scml_transaction_request;

template <typename T>
class scv_extensions;

template <typename DT, typename AT, bool>
class scv_extensions_post;

template< typename DT, typename AT>
class scml_post_port;

template<typename DT, typename AT> 
class scml_transaction_request : public PVReq< DT, AT>
{
public:
  typedef DT data_type;
  typedef AT address_type;
  typedef PVReq< data_type, address_type> pv_request_type;
  typedef scml_array_base data_manager_type;
  typedef data_manager_type * data_manager_pointer_type;
  typedef data_manager_type & data_manager_reference_type;
  typedef scml_array_base::size_type size_type;

  template <typename T>
  friend class scv_extensions;
  template <typename DT_, typename AT_, bool>
  friend class scv_extensions_post;
  template<typename DT_, typename AT_>
  friend class scml_post_port;

public:
  // constructor
  scml_transaction_request();
  virtual ~scml_transaction_request();

  // attribute access
  int getPriority() const;
  void setPriority( const int);

  data_manager_pointer_type getDataManager() const;
  void setDataManager( data_manager_pointer_type );
  void setDataManager( data_manager_reference_type);

  const sc_event & end_event() const;
  void notifyEndEvent();

  scml_endian getEndianness() const;
  void setEndianness( scml_endian a);
  
  size_type getStartIndex() const;
  void setStartIndex( size_type a );

  virtual void setBurstCount( unsigned int burstCount);

  // progress indicators
  address_type getAcquiredAddress() const;
  size_type getAcquiredBurstCountTodo() const;
  size_type acquireBurstCount( size_type c);
  size_type resetAcquireBurstCount( size_type c);

private:  
  // disable
  scml_transaction_request( const scml_transaction_request & );
  scml_transaction_request & operator= ( const scml_transaction_request & );

private:  
  // helper consistency between array & pv
  void updatePVdataPointers();

private:  
  // data members
  int m_priority;
  data_manager_pointer_type m_data_manager; // not owner
  sc_event m_end_event;
  scml_endian m_endian;
  size_type m_start_index;
  size_type m_acquired_burstcount;
};

/************************************************************************
 * INLINE IMPLEMENTATONS
 */

template< typename DT, typename AT> 
inline
scml_transaction_request< DT, AT>::
scml_transaction_request() : 
  m_priority( 0),
  m_data_manager( 0),
  m_endian( scml_little_endian),
  m_start_index( 0),
  m_acquired_burstcount( 0)
{
}

template< typename DT, typename AT> 
inline
scml_transaction_request< DT, AT>::
~scml_transaction_request()
{
}

template< typename DT, typename AT> 
inline
int
scml_transaction_request< DT, AT>::
getPriority() const
{
  return m_priority;
}

template< typename DT, typename AT> 
inline
void
scml_transaction_request< DT, AT>::
setPriority( const int p)
{   
  m_priority = p; 
}

template< typename DT, typename AT> 
inline
typename scml_transaction_request< DT, AT>::data_manager_pointer_type
scml_transaction_request< DT, AT>::
getDataManager() const
{
  return m_data_manager;  
}

template< typename DT, typename AT> 
inline
void
scml_transaction_request< DT, AT>::
setDataManager( data_manager_pointer_type p)
{
  m_data_manager = p;
  this->updatePVdataPointers();
}

template< typename DT, typename AT> 
inline
void
scml_transaction_request< DT, AT>::
setDataManager( data_manager_reference_type r)
{
  m_data_manager = &r;
  this->updatePVdataPointers();
}

template< typename DT, typename AT> 
inline
const sc_event &
scml_transaction_request< DT, AT>::
end_event() const
{
  return m_end_event;
}

template< typename DT, typename AT> 
inline
void
scml_transaction_request< DT, AT>::
notifyEndEvent()
{
  m_end_event.notify( SC_ZERO_TIME);
}

template< typename DT, typename AT> 
inline
scml_endian 
scml_transaction_request< DT, AT>::
getEndianness() const
{
  return m_endian; 
}

template< typename DT, typename AT> 
inline
void
scml_transaction_request< DT, AT>::
setEndianness( scml_endian a) 
{ 
  m_endian = a;
}
  
template< typename DT, typename AT> 
inline
typename scml_transaction_request< DT, AT>::size_type 
scml_transaction_request< DT, AT>::
getStartIndex() const
{ 
  return m_start_index;
}

template< typename DT, typename AT> 
inline
void
scml_transaction_request< DT, AT>::
setStartIndex( size_type a )
{ 
  m_start_index = a;
  this->updatePVdataPointers();
}

// setting burst count resets the progress indicator

template< typename DT, typename AT> 
inline
void
scml_transaction_request< DT, AT>::
setBurstCount( unsigned int burstCount)
{
  pv_request_type::setBurstCount( burstCount);
  this->resetAcquireBurstCount( 0);
}

// progress indicators

template< typename DT, typename AT> 
inline
typename scml_transaction_request< DT, AT>::address_type
scml_transaction_request< DT, AT>::getAcquiredAddress() const
{
  address_type a( this->getAddress());
  a += m_acquired_burstcount * (this->getDataSize() / 8);
  return a; 
}

template< typename DT, typename AT> 
inline
typename scml_transaction_request< DT, AT>::size_type
scml_transaction_request< DT, AT>::getAcquiredBurstCountTodo() const
{ 
  const size_type todo( this->getBurstCount() - m_acquired_burstcount);  
  return todo;
}

template< typename DT, typename AT> 
inline
typename scml_transaction_request< DT, AT>::size_type
scml_transaction_request< DT, AT>::acquireBurstCount( size_type c)
{ 
  const size_type res( SCML_MIN( c, this->getAcquiredBurstCountTodo()));
  m_acquired_burstcount += res;
  return res;
}

template< typename DT, typename AT> 
inline
typename scml_transaction_request< DT, AT>::size_type
scml_transaction_request< DT, AT>::resetAcquireBurstCount( size_type c)
{ 
  m_acquired_burstcount = c;
  return m_acquired_burstcount;
}

template< typename DT, typename AT> 
inline
void
scml_transaction_request< DT, AT>::updatePVdataPointers()
{ 
  data_type * pStorage( 0);
  data_manager_pointer_type pDm( this->getDataManager());
  if( 0 != pDm ) {
    pStorage = static_cast< data_type *>( this->getDataManager()->get_storage_pointer());
  }    
  if( 0 != pStorage) {
    data_type * pData = &( pStorage[ getStartIndex() ]);
    this->setWriteDataSource( pData);
    this->setReadDataDestination( pData);
  } else {
    this->setWriteDataSource( 0);
    this->setReadDataDestination( 0);    
  }
}


#endif
