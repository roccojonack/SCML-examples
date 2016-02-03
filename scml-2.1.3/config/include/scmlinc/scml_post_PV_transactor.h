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

#ifndef SCML_POST_PV_TRANSACTOR_H
#define SCML_POST_PV_TRANSACTOR_H

#include <queue>
#include "systemc.h"
#include "scmlinc/scml_array.h"
#include "scmlinc/scml_post_if.h"
#include "scmlinc/scml_transaction_request.h"
#include <PV/PV.h>
#include <scml2_logging/stream.h>
#include <scml2_logging/severity.h>

template< typename DT = unsigned int, typename AT = unsigned int>
class scml_post_PV_transactor;

template< typename DT, typename AT >
class scml_post_PV_transactor : public sc_module,
				virtual public scml_post_if< DT, AT> {
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

public:
  // ports
  PVInitiator_port< DT, AT > port;

public:
  SC_HAS_PROCESS( scml_post_PV_transactor);
  explicit scml_post_PV_transactor( sc_module_name name );
  virtual ~scml_post_PV_transactor();

  virtual bool post( scml_transaction_request< DT, AT> & tra);

private: 
  // disable
  scml_post_PV_transactor( const scml_post_PV_transactor & );
  scml_post_PV_transactor & operator= ( const scml_post_PV_transactor & );

private:
  void transportEngine();

private: 
  mutable scml2::logging::stream mError;
  sc_event transportEngineEvent;
  ::std::queue< transaction_request_pointer_type > request_queue;
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */

template< typename DT, typename AT >
inline
scml_post_PV_transactor< DT, AT>::
scml_post_PV_transactor( sc_module_name n ) : 
  sc_module( n),
  port( "PVInitiator_port"),
  mError(this->name(), scml2::logging::severity::error())
{
  SC_HAS_PROCESS( scml_post_PV_transactor);
  SC_THREAD( transportEngine);
  sensitive << transportEngineEvent;
}

template< typename DT, typename AT >
inline
scml_post_PV_transactor< DT, AT>::
~scml_post_PV_transactor()
{
}

template< typename DT, typename AT >
inline
bool
scml_post_PV_transactor< DT, AT>::
post( scml_transaction_request< DT, AT> & tra)
{
  transaction_request_pointer_type p( & tra);
  request_queue.push( p);
  transportEngineEvent.notify( SC_ZERO_TIME );
  return true;
}

template< typename DT, typename AT >
inline
void
scml_post_PV_transactor< DT, AT>::
transportEngine()
{
  while( true) {
    while( !request_queue.empty()) {
      transaction_request_pointer_type pTra( request_queue.front());
      const PVType reqType( pTra->getType());
      const size_type startIndex( pTra->getStartIndex());
      const unsigned int burstCount( pTra->getBurstCount()); 
      data_manager_pointer_type pDm( pTra->getDataManager());
      if( pvWrite == reqType) {
	pDm->claim_data( startIndex, burstCount);
	pv_response_type resp( port.transport( *pTra));
	pDm->nb_release_space( startIndex, burstCount);	
      } else if( pvRead == reqType) {
	pDm->claim_space( startIndex, burstCount);
	pv_response_type resp( port.transport( *pTra));
	pDm->nb_release_data( startIndex, burstCount);
      } else {
	SCML2_LOG(mError) << "Unknown Request" << ::std::endl;
      }
      pTra->notifyEndEvent();
      request_queue.pop();			     
    }
    wait();    
  }
}

#endif
