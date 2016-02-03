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
 * Purpose of file : Definition of cnsc decoder port modeling object
 *
 */

#ifndef SCML_PV_DECODER_PORT_H
#define SCML_PV_DECODER_PORT_H

#include "systemc.h"
#include "scmlinc/scml_memory_pv_if.h"
#include "scmlinc/scml_pv_multi_port.h"

#include <scml2_logging/stream.h>
#include <scml2_logging/severity.h>
#include <iostream>
#include <map>
#include <utility>

template< unsigned int ADDRESS_WIDTH_ = 32, 
	  unsigned int DATA_WIDTH_ = 64 >
class scml_pv_decoder_port :
  public scml_pv_multi_port< typename PV::dataWidth2Type< DATA_WIDTH_ >::result,
			     typename PV::dataWidth2Type< ADDRESS_WIDTH_ >::result >
{
public:
  typedef typename PV::dataWidth2Type< DATA_WIDTH_ >::result data_type;
  typedef typename PV::dataWidth2Type< ADDRESS_WIDTH_ >::result address_type;
  typedef scml_pv_multi_port< typename PV::dataWidth2Type< DATA_WIDTH_ >::result,
 			      typename PV::dataWidth2Type< ADDRESS_WIDTH_ >::result > base_port_type;
  typedef PVReq< data_type, address_type > request_type; 
  typedef PVResp< data_type > response_type; 
  typedef PV_if< data_type, address_type > interface_type; 
  typedef interface_type * interface_pointer_type ; 
  typedef data_type value_type;

public:
  scml_pv_decoder_port();
  explicit scml_pv_decoder_port( const char * n);
  virtual ~scml_pv_decoder_port();

  // added bind an interface of type IF to this port: 
  void bind( interface_type & i, address_type base, address_type size = 0);
  void operator() ( interface_type & i, address_type base, address_type size = 0);

  // bind an interface of type IF to this port: see sc_port_b
  // bind a parent port with type IF to this port: see sc_port_b

  // overridden virtual functions: see sc_port_base
  virtual const char* kind() const { return "scml_pv_decoder_port" ; }
  virtual void end_of_elaboration();

  // address decoding
  int getPortIndexForAddress( address_type a, address_type & local_address );
  interface_pointer_type decode( address_type a, address_type & local_address );

private:
  // data members
  mutable scml2::logging::stream mError;
  ::std::map< interface_pointer_type, 
	      ::std::pair< address_type, address_type > > memMapIFp2BaseAddr;
  int nInterfaces ;

private:
  // disable
  scml_pv_decoder_port( const scml_pv_decoder_port & );
  scml_pv_decoder_port & operator= ( const scml_pv_decoder_port & );
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */

template< unsigned int ADDRESS_WIDTH_ , 
	  unsigned int DATA_WIDTH_ >
inline 
scml_pv_decoder_port< ADDRESS_WIDTH_, DATA_WIDTH_>::
scml_pv_decoder_port() : 
  base_port_type(),
  mError(this->name(), scml2::logging::severity::error()),
  memMapIFp2BaseAddr(),
  nInterfaces( 0)
{
}

template< unsigned int ADDRESS_WIDTH_ , 
	  unsigned int DATA_WIDTH_ >
inline 
scml_pv_decoder_port< ADDRESS_WIDTH_, DATA_WIDTH_>::
scml_pv_decoder_port(  const char * n) :
  base_port_type( n ),
  mError(this->name(), scml2::logging::severity::error()),
  memMapIFp2BaseAddr(),
  nInterfaces( 0)
{
}

template< unsigned int ADDRESS_WIDTH_ , 
	  unsigned int DATA_WIDTH_ >
inline 
scml_pv_decoder_port< ADDRESS_WIDTH_, DATA_WIDTH_>::
~scml_pv_decoder_port()
{
}

/************************************************************************
 * at end of elaboration
 * build address decoder data structure
 */

template< unsigned int ADDRESS_WIDTH_ , 
	  unsigned int DATA_WIDTH_ >
inline 
void
scml_pv_decoder_port< ADDRESS_WIDTH_, DATA_WIDTH_>::
end_of_elaboration()
{ 
  nInterfaces = this->size();
  assert( (int)memMapIFp2BaseAddr.size() == nInterfaces);
}

/************************************************************************
 * Binding
 */

template< unsigned int ADDRESS_WIDTH_ , 
	  unsigned int DATA_WIDTH_ >
inline
void 
scml_pv_decoder_port< ADDRESS_WIDTH_, DATA_WIDTH_ >::
operator() ( interface_type & i,
	     address_type address, 
	     address_type size )
{
  bind( i, address, size );
}

template< unsigned int ADDRESS_WIDTH_ , 
	  unsigned int DATA_WIDTH_ >
inline
void
scml_pv_decoder_port< ADDRESS_WIDTH_, DATA_WIDTH_ >::
bind( interface_type & i,
      address_type address, 
      address_type size )
{
  scml_memory_base* mem = dynamic_cast<scml_memory_base*>(&i);
  if (mem != 0) {
    const uint64 memSize = mem->getSize() * mem->getWordSize() / (mem->get_addressing_mode() / 8);
    if (memSize < size) {
      SCML2_LOG(mError)
        << "ERROR: The size of memory '" << mem->getName() << "'"
        << " is only 0x" << std::hex << memSize << " bytes,"
        << " but the size specified when it is bound to the scml_pv_decoder"
        << " is 0x" << size << std::dec << " bytes."
        << std::endl;
    }
  }

  memMapIFp2BaseAddr[ &i ] = std::make_pair( address, size );
  scml_pv_decoder_port::base_port_type::bind( i ); 
}

/************************************************************************
 * Address Decoding
 *
 * Proof of concept address decoder.
 * TODO FIXME optimised implementation goes here
 */

template< unsigned int ADDRESS_WIDTH_ , 
	  unsigned int DATA_WIDTH_ >
inline
int
scml_pv_decoder_port< ADDRESS_WIDTH_, DATA_WIDTH_ >::
getPortIndexForAddress( address_type a, address_type & local_address )
{
  for( int i = 0; i < nInterfaces; ++i ) {
    std::pair< address_type, address_type > & memRegion
      = memMapIFp2BaseAddr[ this->operator[] ( i )];
    const address_type base( memRegion.first);
    const address_type size( memRegion.second);
    if(( base <= a) && ( a <= (base + (size - 1)))) {
      local_address = a - base;
      return i;
    }
  }
  return -1;
}

template< unsigned int ADDRESS_WIDTH_ , 
	  unsigned int DATA_WIDTH_ >
inline
typename scml_pv_decoder_port< ADDRESS_WIDTH_, DATA_WIDTH_ >::interface_pointer_type
scml_pv_decoder_port< ADDRESS_WIDTH_, DATA_WIDTH_ >::
decode( address_type a, address_type & local_address )
{
  return this->operator[] ( getPortIndexForAddress( a, local_address ));
}

#endif
