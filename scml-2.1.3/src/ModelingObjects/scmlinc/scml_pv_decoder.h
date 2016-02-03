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
 * Purpose of file : Definition of cnsc decoder modeling object
 *
 */

#ifndef SCML_PV_DECODER_H
#define SCML_PV_DECODER_H

#include "systemc.h"
#include "scmlinc/scml_memory_pv_if.h"
#include "scmlinc/scml_pv_decoder_port.h"

template< unsigned int address_width = 32, 
	  unsigned int data_width = 64 >
class scml_pv_decoder : 
  public sc_module, 
  public virtual PV_if< typename PV::dataWidth2Type< data_width >::result,
			typename PV::dataWidth2Type< address_width >::result >
{
public:
  typedef typename PV::dataWidth2Type< data_width >::result data_type;
  typedef typename PV::dataWidth2Type< address_width >::result address_type;
  typedef PVReq< data_type, address_type > request_type; 
  typedef PVResp< data_type > response_type; 
  typedef PV_if< data_type, address_type > interface_type; 
  typedef interface_type * interface_pointer_type ; 
  typedef data_type value_type;
  typedef PVTarget_port< data_type, address_type > bus_port_type;
  typedef scml_pv_decoder_port< address_width, data_width > peripheral_port_type;
					 
  // port list
  bus_port_type bus_port;
  peripheral_port_type mem_port; 

public:
  SC_HAS_PROCESS( scml_pv_decoder ); 
  explicit scml_pv_decoder( sc_module_name n );
  
  // default destrctor OK
  // ~scml_pv_decoder();
  using PV_if<typename PV::dataWidth2Type<data_width>::result,
              typename PV::dataWidth2Type<address_width>::result>::transport;
  virtual response_type transport( const request_type & );
  response_type nonVirtualTransport( const request_type & );

private:
  // disable
  scml_pv_decoder();          
  scml_pv_decoder( const scml_pv_decoder & );          
  scml_pv_decoder & operator= ( const scml_pv_decoder & );
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */
template< unsigned int address_width, 
	  unsigned int data_width >
inline
scml_pv_decoder< address_width, data_width> ::
scml_pv_decoder( sc_module_name n ) :
  sc_module( n ),
  bus_port( sc_gen_unique_name( "bus_port")),
  mem_port( sc_gen_unique_name( "mem_port"))
{
  SC_HAS_PROCESS( scml_pv_decoder);
  REGISTER_PVSLAVE( bus_port, nonVirtualTransport);
}

template< unsigned int address_width, 
	  unsigned int data_width >
inline
typename scml_pv_decoder< address_width, data_width>::response_type 
scml_pv_decoder< address_width, data_width>::
transport( const request_type & req )
{
  return nonVirtualTransport( req );
}

template< unsigned int address_width, 
	  unsigned int data_width >
inline
typename scml_pv_decoder< address_width, data_width>::response_type 
scml_pv_decoder< address_width, data_width>::
nonVirtualTransport( const request_type & req )
{
  const address_type a( req.getAddress());
  address_type local_address;
  int index = mem_port.getPortIndexForAddress( a, local_address);
  if( -1 == index) {
    response_type resp( req.obtainResp());
    resp.setResponse( pvError);
    return resp;   
  } else {
    req.m_address = local_address;
    return mem_port[ index ]->transport( req);
  }
}

#endif
