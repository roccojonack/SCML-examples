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

#ifndef SCML_POST_PORT_H
#define SCML_POST_PORT_H

#include <queue>
#include <map>
#include "systemc.h"
#include "scmlinc/scml_array.h"
#include "scmlinc/scml_array_notify_if.h"
#include "scmlinc/scml_post_if.h"
#include "scmlinc/scml_mapable_if.h"
#include "scmlinc/scml_transaction_request.h"


#include <scml2_logging/stream.h>
#include <scml2_logging/severity.h>

template< typename DT = unsigned int, typename AT = unsigned int>
class scml_post_port;

struct scml_memory_access_descriptor;

template< typename DT, typename AT >
class scml_post_port : public sc_port< scml_post_if< DT, AT> >,
		       public scml_array_notify_if,
		       public scml_mapable_if
{
public:
  typedef AT address_type;
  typedef DT data_type;
  typedef scml_transaction_request< data_type, address_type> transaction_request_type;
  typedef transaction_request_type * transaction_request_pointer_type;
  typedef transaction_request_type & transaction_request_reference_type;
  typedef PVReq< data_type, address_type> pv_request_type;
  typedef PVResp< data_type> pv_response_type;  
  typedef scml_array_notify_if::array_base_pointer_type array_base_pointer_type;
  typedef array_base_pointer_type data_manager_pointer_type;
  typedef scml_array_base::size_type size_type;
  typedef scml_array< data_type > scml_array_type;

public:
  explicit scml_post_port( const char * n,
			   scml_endian endian = scml_little_endian);
  virtual ~scml_post_port();

  void end_of_elaboration();

  virtual bool post( scml_transaction_request< DT, AT> & tra);
  virtual bool post_read( transaction_request_type & tra,
			  scml_array_type & dataStore,
			  size_type startIndex,
			  address_type address,
			  unsigned int dataSize = 8,
			  unsigned int burstCount = 1);
  virtual bool post_write( transaction_request_type & tra,
			   scml_array_type & dataStore,
			   size_type startIndex,
			   address_type address,
			   unsigned int dataSize = 8,
			   unsigned int burstCount = 1);

  using scml_mapable_if::transport;
  virtual pv_response_type transport( const pv_request_type & req);  
  scml_endian get_endianness() const;


public:
  virtual void start_of_simulation();
  virtual void claim_data_notification( array_base_pointer_type );
  virtual void claim_space_notification( array_base_pointer_type );


  virtual const char* getName() const { return this->name(); }

  //FIXME
  virtual void setPVInterfaceType(scml::PVInterfaceType pvInterfaceType);
  virtual scml::PVInterfaceType getPVInterfaceType() const;

private: 
  // disable
  scml_post_port( const scml_post_port & );
  scml_post_port & operator= ( const scml_post_port & );

private:
  typedef ::std::queue< transaction_request_pointer_type > request_queue_type;
  typedef request_queue_type * request_queue_pointer_type;  
  typedef ::std::map< array_base_pointer_type, request_queue_pointer_type> map_type;
  typedef typename map_type::iterator map_iterator_type;

  void callTryOffloadQueue( array_base_pointer_type );
  void tryOffloadQueue( request_queue_pointer_type );
  
  template <typename T1, typename T2> struct SameType { enum { Result = false }; };
  template <typename T> struct SameType<T, T> { enum { Result = true }; };


private:
  // data member
  mutable scml2::logging::stream mWarning;
  mutable scml2::logging::stream mError;
  map_type m_array2queue;
  // request_queue_type m_request_queue;
  scml_endian m_endian;
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */

template< typename DT, typename AT >
inline
scml_post_port< DT, AT>::
scml_post_port( const char * n,
		scml_endian endian ) : 
  sc_port< scml_post_if< DT, AT> >( n),
  mWarning(this->name(), scml2::logging::severity::warning()),
  mError(this->name(), scml2::logging::severity::error()),
  m_array2queue(),
  m_endian( endian)
{
}

template< typename DT, typename AT >
inline
scml_post_port< DT, AT>::~scml_post_port()
{
  for( map_iterator_type
 	 it = m_array2queue.begin(),
 	 end = m_array2queue.end();
       it != end;
       ++it) {
    request_queue_pointer_type p2q = (*it).second;
    delete p2q;
  }
}

template< typename DT, typename AT >
inline
void
scml_post_port< DT, AT>::end_of_elaboration()
{
}

template< typename DT, typename AT >
inline
void
scml_post_port< DT, AT>::
start_of_simulation()
{
}

template< typename DT, typename AT >
inline
scml_endian 
scml_post_port< DT, AT>::
get_endianness() const
{
  return m_endian;
}

template< typename DT, typename AT >
inline
void
scml_post_port< DT, AT>::
callTryOffloadQueue(array_base_pointer_type p)
{
  map_iterator_type it = m_array2queue.find(p);
  if (it != m_array2queue.end()) {
    request_queue_pointer_type p2q = it->second;
    assert(p2q != 0);
    if (!p2q->empty()) {
      tryOffloadQueue(p2q);
    }
    if (p2q->empty()) {
      delete p2q;
      m_array2queue.erase(it);
    }
  }
}

template< typename DT, typename AT >
inline
bool
scml_post_port< DT, AT>::
post( scml_transaction_request< DT, AT> & tra)
{
  if (tra.getMode() == pvDebug) {
    SCML2_LOG(mError)
      << "The 'post' call should not be used for debug accesses."
      << "Use 'transport', 'debug_read' or 'debug'write' instead."
      << std::endl;
  }

  transaction_request_pointer_type p2t( &tra);    
  array_base_pointer_type pDm( tra.getDataManager());
  request_queue_pointer_type p2q = m_array2queue[ pDm ];
  if( 0 == p2q) {
    p2q = new request_queue_type();
    m_array2queue[ pDm ] = p2q;
  }
  p2q->push( p2t);
  callTryOffloadQueue(pDm);
  return true;
}

template< typename DT, typename AT >
inline
void
scml_post_port< DT, AT>::tryOffloadQueue( request_queue_pointer_type p2q )
{
  assert(p2q);
  assert(!p2q->empty());

  transaction_request_pointer_type pTra = p2q->front(); 
    (*this)->post( *pTra);
    p2q->pop();
    return;

}

template< typename DT, typename AT >
inline
void
scml_post_port< DT, AT>::claim_data_notification( array_base_pointer_type p )
{
  callTryOffloadQueue(p);
}

template< typename DT, typename AT >
inline
void
scml_post_port< DT, AT>::claim_space_notification( array_base_pointer_type p)
{
  callTryOffloadQueue(p);
}


/************************************************************************
 * PV convenience layer: blocking transport built on post
 */

template< typename DT, typename AT >
inline
typename scml_post_port< DT, AT>::pv_response_type 
scml_post_port< DT, AT>::transport( const pv_request_type & constReq)
{
    if (constReq.getMode() == pvDebug) {
      // Debug access should not go over the bus
      constReq.obtainResp().setResponse(pvError);
      return constReq.obtainResp();
    }

  // Bus access
  pv_response_type resp( constReq.obtainResp());
  data_type * pDataStore( NULL);
  const PVType reqType( constReq.getType());
  if( pvWrite == reqType) {
    pDataStore = constReq.getWriteDataSource();
  } else if( pvRead == reqType) {
    pDataStore = constReq.getReadDataDestination();
  } else {
    SCML2_LOG(mWarning) << "Invalid PV access type!" << ::std::endl;    
    resp.setResponse( pvError );
    return resp;
  }
  const unsigned int burstCount( constReq.getBurstCount());
  transaction_request_type tra;
  tra.copy_request( constReq);
  tra.obtainResp().copy_response( resp);
  scml_array_type * pArray = new scml_array_type( pDataStore, burstCount );
  if( pvWrite == reqType) {
    pArray->claim_space( 0, burstCount);  // recently allocated => cannot fail
    pArray->nb_release_data( 0, burstCount); // data already provided by PV side
  }
  tra.setDataManager(pArray);
  (*this)->post( tra); // Call post method of interface bound to this port
  wait( tra.end_event());
  if( pvRead == reqType) {
    pArray->claim_data( 0, burstCount);
    pArray->nb_release_space( 0, burstCount);
  }
  delete m_array2queue[pArray];
  m_array2queue.erase(pArray);
  delete pArray;
  resp.copy_response( tra.obtainResp());
  return resp;
}

/************************************************************************
 * post read & write convenience layer
 */

template< typename DT, typename AT >
inline
bool 
scml_post_port< DT, AT>::
post_read( transaction_request_type & tra,
	   scml_array_type & dataStore,
	   size_type startIndex,
	   address_type address,
	   unsigned int dataSize,
	   unsigned int burstCount)
{
  tra.setAddress( address);
  tra.setType( pvRead);
  tra.setDataSize( dataSize);
  tra.setOffset( 0);
  tra.setPriority( 0);
  tra.setEndianness( get_endianness()); 
  // setting data manager and start index sets these pointers
  // tra.setReadDataDestination( NULL);    
  // tra.setWriteDataSource( NULL);    
  tra.setDataManager( dataStore);
  tra.setStartIndex( startIndex);
  tra.setBurstCount( burstCount);
  tra.resetAcquireBurstCount( 0);
  post( tra);
  return true;
}

template< typename DT, typename AT >
inline
bool 
scml_post_port< DT, AT>::
post_write( transaction_request_type & tra,
	    scml_array_type & dataStore,
	    size_type startIndex,
	    address_type address,
	    unsigned int dataSize,
	    unsigned int burstCount)
{
  tra.setAddress( address);
  tra.setType( pvWrite);
  tra.setDataSize( dataSize);
  tra.setOffset( 0);
  tra.setPriority( 0);
  tra.setEndianness( get_endianness()); 
  // setting data manager and start index sets these pointers
  // tra.setReadDataDestination( NULL);    
  // tra.setWriteDataSource( NULL);    
  tra.setDataManager( dataStore);
  tra.setStartIndex( startIndex);
  tra.setBurstCount( burstCount);
  tra.resetAcquireBurstCount( 0);
  post( tra);
  return true;
}


template< typename DT, typename AT >
inline
void
scml_post_port< DT, AT>::
setPVInterfaceType(scml::PVInterfaceType pvInterfaceType)
{
  if (pvInterfaceType == scml::PV_INTERFACE_UNKNOWN) {
    return;
  }
  assert(pvInterfaceType == getPVInterfaceType());
}

template< typename DT, typename AT >
inline
scml::PVInterfaceType
scml_post_port< DT, AT>::
getPVInterfaceType() const
{
  typedef typename scml::Types2If<DT, AT>::result IF;
  return (scml::PVInterfaceType)scml::If2PVInterfaceType<IF>::result;
}

#endif
