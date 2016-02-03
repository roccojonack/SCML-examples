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

#include "scmlinc/scml_router_operations_podt_common.h"
#include "scmlinc/scml_memory_registration.h"
#include "scmlinc/scml_synchroniser_registry.h"
#include "scmlinc/scml_mapable_if_to_T.h"
#include "scmlinc/scml_mapped_range.h"
#include <scml2_logging/severity.h>
#include <map>
#include <iomanip>
#include <algorithm>
#include <iterator>

#ifdef _WIN32
// Disable warning for unreachable code; in the code below often something like 
// bool my_fun()
// {
//    assert(false);
//    return true;
// }
// is used !!!
#pragma warning (disable : 4702)
#endif

using namespace scml;

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */

template< typename DT >
scml_router_operations_podt_common< DT >::~scml_router_operations_podt_common()
{
  cleanUp();
}


template< typename DT >
bool
scml_router_operations_podt_common< DT >::
checkPVInterfaceType(PVInterfaceType pvInterfaceType) const
{
  if (getPVInterfaceType() == PV_INTERFACE_UNKNOWN ||
      pvInterfaceType == PV_INTERFACE_UNKNOWN ||
      getPVInterfaceType() == pvInterfaceType) {
    return true;
  }
  return false;
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::
setPVInterfaceType(PVInterfaceType pvInterfaceType)
{
  if (pvInterfaceType == PV_INTERFACE_UNKNOWN) {
    return;
  }

  if (!checkPVInterfaceType(pvInterfaceType)) {
    SCML2_LOG(mError)
      << "It is not possible to mix different data types."
      << "The data type of the registered callback must be the same as the data type"
      << " of the PV port to which the scml_router is bound. And the destination of "
      << " mapped regions must also use the same data type as this scml_router object."
      << std::endl;
  }
  mPVInterfaceType = pvInterfaceType;
}

template< typename DT >
typename scml_router_operations_podt_common< DT >::PVInterfaceType
scml_router_operations_podt_common< DT >::
getPVInterfaceType() const
{
  return mPVInterfaceType;
}

template< typename DT >
template< typename REQ >
void
scml_router_operations_podt_common< DT >::
checkBurstAccess(const REQ& req) const
{
  if (req.getBurstCount() > 1) {
    // Only pvIncr is supported
    if (req.getBurstType() != pvIncr) {
      SCML2_LOG(mError) << "Illegal burstType, only pvIncr is supported!"
                      << std::endl;
    }
  
    // Access size must be equal to the size of the underlying memory
    if (req.getDataSize() != sizeOf<DT>() * 8) {
      SCML2_LOG(mError)
        << "Illegal access size. For burst accesses, "
        << "the access size must be equal to the data size of the underlying memory!"
        << std::endl;
    }
  }
}

/************************************************************************
 * Queries for callbacks
 */

template< typename DT >
typename scml_router_operations_podt_common< DT >::CallBackType
scml_router_operations_podt_common< DT >::getCallBackType() const
{
  if (mModule && mTransportCb) {
    return CB_TYPE_TRANSPORT;
  }

  return CB_TYPE_NONE;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
getTransportCallBackName(std::string& name) const
{
  if (getCallBackType() == CB_TYPE_TRANSPORT) {
    name = mTransportCallBackName;
    return true;
  }
  return false;
}

/************************************************************************
 * constructors for forward migration
 * behaviour is do as value_type does
 */

template< typename DT >
scml_router_operations_podt_common< DT >::
scml_router_operations_podt_common() :
  scml_memory_base( scml_memory_base::defaultName()),
  mError(getName(), scml2::logging::severity::error()),
  mWarning(getName(), scml2::logging::severity::warning()),
  memOffset( 0),
  memSize( 1),
  endianness( cwrLitend),
  mHasHostEndianness( scml_memory_utils::hasHostEndianness( endianness)),
  addressingMode( 8 ),
  mModule( 0),
  mTransportCb(0),
  mBlocking( false ),
  mUserId( 0),
  mPVInterfaceType(PV_INTERFACE_UNKNOWN),
  mIsBoundToPort( false),
  mDefaultRespLatency( 0),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{
}

/************************************************************************
 * named default
 */
template< typename DT >
scml_router_operations_podt_common< DT >::
scml_router_operations_podt_common( const char * n ) :
  scml_memory_base( n),
  mError(getName(), scml2::logging::severity::error()),
  mWarning(getName(), scml2::logging::severity::warning()),
  memOffset( 0),
  memSize( 1),
  endianness( cwrLitend),
  mHasHostEndianness( scml_memory_utils::hasHostEndianness( endianness)),
  addressingMode( 8 ),
  mModule( 0),
  mTransportCb(0),
  mBlocking( false ),
  mUserId( 0),
  mPVInterfaceType(PV_INTERFACE_UNKNOWN),
  mIsBoundToPort( false),
  mDefaultRespLatency( 0),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{
}

/************************************************************************
 * constructors for memory array
 */
template< typename DT >
scml_router_operations_podt_common< DT >::
scml_router_operations_podt_common( scml_memsize a ) :
  scml_memory_base( scml_memory_base::defaultName()),
  mError(getName(), scml2::logging::severity::error()),
  mWarning(getName(), scml2::logging::severity::warning()),
  memOffset( 0),
  memSize( a),
  endianness( cwrLitend),
  mHasHostEndianness( scml_memory_utils::hasHostEndianness( endianness)),
  addressingMode( 8 ),
  mModule( 0),
  mTransportCb(0),
  mBlocking( false ),
  mUserId( 0),
  mPVInterfaceType(PV_INTERFACE_UNKNOWN),
  mIsBoundToPort( false),
  mDefaultRespLatency( 0),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{
}

template< typename DT > 
scml_router_operations_podt_common< DT >::
scml_router_operations_podt_common( const char * n,
				      scml_memsize a ) :
  scml_memory_base( n ),
  mError(getName(), scml2::logging::severity::error()),
  mWarning(getName(), scml2::logging::severity::warning()),
  memOffset( 0),
  memSize( a),
  endianness( cwrLitend),
  mHasHostEndianness( scml_memory_utils::hasHostEndianness( endianness)),
  addressingMode( 8 ),
  mModule( 0),
  mTransportCb(0),
  mBlocking( false ),
  mUserId( 0),
  mPVInterfaceType(PV_INTERFACE_UNKNOWN),
  mIsBoundToPort( false),
  mDefaultRespLatency( 0),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{
}

/************************************************************************
 * implicit conversion operator to scml_mapable_if
 */

template< typename DT>
scml_router_operations_podt_common< DT >::
operator scml_mapable_if& ()
{
  return *mMapableIf;
}

template< typename DT>
scml_router_operations_podt_common< DT >::
operator const scml_mapable_if& () const
{
  return *mMapableIf;
}

/************************************************************************
 * endianness
 *
 */
template< typename DT >
void 
scml_router_operations_podt_common< DT >::
set_endianness( scml_endian a )
{ 
  endianness = scml_memory_utils::convert_scml_to_cwrEnd( a);
}

template< typename DT >
scml_endian 
scml_router_operations_podt_common< DT >::
get_endianness() const
{
  return scml_memory_utils::convert_cwrEnd_to_scml( endianness); 
}

/************************************************************************
 * addressing mode
 *
 */

template< typename DT >
unsigned int
scml_router_operations_podt_common< DT >::get_addressing_mode() const 
{ 
  return this->addressingMode; 
}

template< typename DT >
void 
scml_router_operations_podt_common< DT >::set_addressing_mode( unsigned int a )
{
  addressingMode = a;
}

/************************************************************************
 * access
 * read and write
 */

template< typename DT >
template< typename IF >
typename scml_router_operations_podt_common< DT >::value_type
scml_router_operations_podt_common< DT >::readImp(size_type a,
                                                  unsigned int acSiz,
                                                  unsigned int offSet,
                                                  bool isDebug)
{
  assert(memOffset == 0);
  // Split up access in byte accesses
  // requests may be forwarded to scml_memories with smaller data type (of PV Interface)
  typename IF::request_type req;
  req.setWriteDataSource(0);
  typename IF::data_type rData = 0;
  req.setReadDataDestination(&rData);
  req.setType(pvRead);
  req.setDataSize(8);
  req.setOffset(0);
  req.setBurstCount(1);
  req.setBurstType(pvIncr);
  req.setThreadID(0);
  req.setMode(isDebug ? pvDebug : pvDefault);

  value_type result = 0;
  for (unsigned int i = 0; i < acSiz / 8; ++i) {
    //FIXME: only byte addressing supported for scml_router
    const uint64 address = indexToByteAddress(a, acSiz, offSet + i*8);
    assert((address == convert<uint64, typename IF::address_type>(address)));
    req.setAddress(address);
    transportProp<IF>( req );
    result |= convert<typename IF::data_type, value_type>(rData) << (i*8);
  }
  return result;
}

template< typename DT >
template< typename IF >
void
scml_router_operations_podt_common< DT >::writeImp(value_type v,
                                                   size_type a,
                                                   unsigned int acSiz,
                                                   unsigned int offSet,
                                                   bool isDebug)
{
  assert(memOffset == 0);
  // Split up access in byte accesses
  // requests may be forwarded to scml_memories with smaller data type (of PV Interface)
  typename IF::request_type req;
  typename IF::data_type wData;
  req.setWriteDataSource(&wData);
  req.setReadDataDestination(0);
  req.setType(pvWrite); 
  req.setDataSize(8);   
  req.setOffset(0);    
  req.setBurstCount(1);
  req.setBurstType(pvIncr);
  req.setThreadID(0);
  req.setMode(isDebug ? pvDebug : pvDefault);

  for (unsigned int i = 0; i < acSiz / 8; ++i) {
    //FIXME: only byte addressing supported for scml_router
    const uint64 address = indexToByteAddress(a, acSiz, offSet + i*8);
    assert((address == convert<uint64, typename IF::address_type>(address)));
    req.setAddress(address);
    wData = convert<value_type, typename IF::data_type>(v >> (i*8));
    transportProp<IF>( req );
  }
  return;
}

template< typename DT >
typename scml_router_operations_podt_common< DT >::value_type
scml_router_operations_podt_common< DT >::readProp(size_type a,
                                                   unsigned int acSiz,
                                                   unsigned int offSet,
                                                   bool isDebug)
{
  switch (getPVInterfaceType()) {
  case PV_INTERFACE_32_32:
    return readImp<scml_memory_pv_32_32_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_32_64:
    return readImp<scml_memory_pv_32_64_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_32_128:
    return readImp<scml_memory_pv_32_128_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_32_256:
    return readImp<scml_memory_pv_32_256_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_32_512:
    return readImp<scml_memory_pv_32_512_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_64_32:
    return readImp<scml_memory_pv_64_32_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_64_64:
    return readImp<scml_memory_pv_64_64_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_64_128:
    return readImp<scml_memory_pv_64_128_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_64_256:
    return readImp<scml_memory_pv_64_256_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_64_512:
    return readImp<scml_memory_pv_64_512_if>(a, acSiz, offSet, isDebug);

  case PV_INTERFACE_UNKNOWN:
  default:
    // use native data type and unsigned long long for address
    typedef typename PV::dataWidth2Type<8 * SizeOf<value_type>::result>::result DataType;
    typedef typename scml::Types2If<DataType , unsigned long long>::result interfaceType;
    return readImp<interfaceType>(a, acSiz, offSet, isDebug);
  };
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::writeProp(value_type v,
                                                    size_type a,
                                                    unsigned int acSiz,
                                                    unsigned int offSet,
                                                    bool isDebug)
{
  switch (getPVInterfaceType()) {
  case PV_INTERFACE_32_32:
    writeImp<scml_memory_pv_32_32_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_32_64:
    writeImp<scml_memory_pv_32_64_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_32_128:
    writeImp<scml_memory_pv_32_128_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_32_256:
    writeImp<scml_memory_pv_32_256_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_32_512:
    writeImp<scml_memory_pv_32_512_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_64_32:
    writeImp<scml_memory_pv_64_32_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_64_64:
    writeImp<scml_memory_pv_64_64_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_64_128:
    writeImp<scml_memory_pv_64_128_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_64_256:
    writeImp<scml_memory_pv_64_256_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_64_512:
    writeImp<scml_memory_pv_64_512_if>(v, a, acSiz, offSet, isDebug);
    break;

  case PV_INTERFACE_UNKNOWN:
  default:
    // use native data type and unsigned long long for address
    typedef typename PV::dataWidth2Type<8 * SizeOf<value_type>::result>::result DataType;
    typedef typename scml::Types2If<DataType , unsigned long long>::result interfaceType;
    writeImp<interfaceType>(v, a, acSiz, offSet, isDebug);
    break;
  };
}

template< typename DT >
typename scml_router_operations_podt_common< DT >::value_type
scml_router_operations_podt_common< DT >::read(size_type a,
                                               unsigned int acSiz,
                                               unsigned int offSet)
{ 
  return readProp(a, acSiz, offSet, false);
}

template< typename DT >
typename scml_router_operations_podt_common< DT >::value_type
scml_router_operations_podt_common< DT >::read( size_type a )
{ 
  const unsigned int acSiz( 8 * sizeOf<value_type>());
  return read(a, acSiz, 0);
}

template< typename DT >
typename scml_router_operations_podt_common< DT >::value_type
scml_router_operations_podt_common< DT >::readDebug(size_type a,
                                                    unsigned int acSiz,
                                                    unsigned int offSet )
{
  return readProp(a, acSiz, offSet, true);
}

template< typename DT >
typename scml_router_operations_podt_common< DT >::value_type
scml_router_operations_podt_common< DT >::readDebug( size_type a )
{
  const unsigned int acSiz( 8 * sizeOf<value_type>());
  return readDebug(a, acSiz, 0);
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::write(value_type v,
                                                size_type a,
                                                unsigned int acSiz,
                                                unsigned int offSet) 
{
  writeProp(v, a, acSiz, offSet, false);
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::write( value_type v, size_type a ) 
{
  const unsigned int acSiz( 8 * sizeOf<value_type>());
  write(v, a, acSiz, 0);
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::writeDebug( value_type v,
						      size_type a,
                                                      unsigned int acSiz,
                                                      unsigned int offSet)
{
  writeProp(v, a, acSiz, offSet, true);
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::writeDebug( value_type v,
						      size_type a)
{
  const unsigned int acSiz( 8 * sizeOf<value_type>());
  writeDebug(v, a, acSiz, 0);
}


/************************************************************************
 * default latency setting for PV response
 */

template< typename DT >
unsigned int
scml_router_operations_podt_common< DT >::get_default_response_latency() const
{
  return mDefaultRespLatency;
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::
set_default_response_latency( unsigned int l)
{
  mDefaultRespLatency = l;
}

/************************************************************************
 * PV Transport virtual function
 * see tlm_if
 *
 * can only be called on orignal memory
 */

#define DEFINE_TRANSPORT(IF) \
  template< typename DT > \
  IF::response_type \
  scml_router_operations_podt_common<DT>::transport(const IF::request_type& req) { \
    return transportProp<IF>(req); \
  }
SCML_FOR_EACH_PV_INTERFACE_TYPE(DEFINE_TRANSPORT)
#undef DEFINE_TRANSPORT

/************************************************************************
 * PV Transport function
 * propagate to implementation
 *
 * function lookup is based on indices in orignal memory
 * address substraction is performed when the implementation is called
 */
template< typename DT >
template< typename IF >
typename IF::response_type
scml_router_operations_podt_common< DT >::
transportProp( const typename IF::request_type & req) {
  const unsigned int burstCount = req.getBurstCount();
  const typename IF::address_type address = req.getAddress();

  MappedRanges& ranges = ( req.getType() == pvRead ? mMappedReadRanges : mMappedWriteRanges);
  scml_mapped_range* range = this->getMappedRange(ranges,address);

  // Mapped range -> forward request
  if (range) {
    if ((burstCount > 1) &&
        !range->contains(address + (burstCount * sizeOf<value_type>()) - 1)) {
      return burstUnrollingTransportImp<IF>(req);
    }
    req.m_address = range->mapped_address(address);
    return range->template transport<IF>(req);
  }
    
  scml_memory_user& user (scml_memory_user::instance());
  user.set_last_top_level_address( address);
  user.set_debug_access( pvDebug == req.getMode());
  return transportImp<IF>( req );
}

/************************************************************************
 * PV Transport function
 * implementation
 *
 * address substraction has been performed
 */
template< typename DT >
template< typename IF >
typename IF::response_type
scml_router_operations_podt_common< DT >::
burstUnrollingTransportImp( const typename IF::request_type & req)
{
  checkBurstAccess(req);

  typename IF::response_type resp( req.obtainResp());
  bool errorResp( false);
  unsigned int totalLatency( 0);
  const unsigned int burstCount( req.getBurstCount());
  typename IF::address_type unrollAddress( req.getAddress());
  typename IF::address_type addressIncr( req.getDataSize() / get_addressing_mode());
  if( 0 == addressIncr) {
    addressIncr = 1;
  }
  typename IF::request_type unrolreq;
  typename IF::response_type unrolresp( unrolreq.obtainResp());
  unrolreq.copy_request( req);
  unrolresp.copy_response( resp);
  unrolreq.setBurstCount( 1);
  unrolreq.setProtocolRespData(req.getProtocolRespData());
  typename IF::data_type * writeDataSource( req.getWriteDataSource());
  typename IF::data_type * readDataDestination( req.getReadDataDestination());
  for( unsigned int beat = 0; beat < burstCount; ++beat ) {
    unrolreq.setAddress( unrollAddress);
    unrollAddress += addressIncr;
    unrolreq.setWriteDataSource( writeDataSource);
    if (writeDataSource) {
      ++writeDataSource;
    }
    unrolreq.setReadDataDestination( readDataDestination);
    if (readDataDestination) {
      ++readDataDestination;
    }
    unrolresp = transportProp<IF>( unrolreq);
    totalLatency += unrolresp.getLatency();
    if( unrolresp.getResponse() != pvOk) {
      errorResp = true;
    }
  }
  resp.setLatency( totalLatency);
  resp.setResponse( errorResp ? pvError : pvOk);
  return resp;
}

/************************************************************************
 * PV Transport function
 * implementation
 *
 * address substraction has been performed
 */
template< typename DT >
template <typename IF>
typename IF::response_type
scml_router_operations_podt_common< DT >::
transportImp( const typename IF::request_type & req) {
  assert(checkPVInterfaceType((PVInterfaceType)scml::If2PVInterfaceType<IF>::result));

  scml_memory_user& user (scml_memory_user::instance());
  user.set_last_user_id( mUserId);
  user.set_last_memory_pointer( this);

  const PVType reqType( req.getType());

  typename IF::response_type resp( req.obtainResp());
  resp.setLatency( this->get_default_response_latency());
  resp.setResponse( pvOk );
  
  if( pvWrite == reqType || pvRead == reqType) {
    if (!hasRegisteredTransportCallBack()) {
      SCML2_LOG(mError) << "No PV callback registered to the router object '"
                      << getName() << "': unmapped address = 0x" << std::hex
                      << req.getAddress() << std::dec << std::endl;
    }
    if (mBlocking && (req.getMode() != pvDebug)) {
      // TLM2 target adaptor does not sync
      //  --> sync before executing blocking callback
      SCML_SYNC_ON_DEMAND();
    }

    assert(mTransportCb);
    return mTransportCb->transport(req);

  } else {
    SCML2_LOG(mWarning) << "Invalid PV access type!" << ::std::endl;    
    resp.setResponse( pvError );
  }
  return resp;
}

template< typename DT > 
bool
scml_router_operations_podt_common< DT >::trigger_behaviour_on_debug_read() const
{
  /* Note: The scml router has always a debug read callback attached. */
  return true;
}

template< typename DT > 
bool
scml_router_operations_podt_common< DT >::trigger_behaviour_on_debug_write() const
{
  /* Note: The scml router has always a debug read callback attached. */
  return true;
}



/************************************************************************
 * PRIVATE HELPER FUNCTIONS
 */

template< typename DT >
bool
scml_router_operations_podt_common< DT >::isValidIndex( size_type i) const
{ 
  return (i < this->size());
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
updateBlockingProperty( bool isBlocking ) 
{
  return( this->mBlocking = (this->mBlocking || isBlocking));
}

template< typename DT >
bool 
scml_router_operations_podt_common< DT >::hasBehaviourAttached() const
{
  return this->hasRegisteredCallBack();
}

template< typename DT >
bool 
scml_router_operations_podt_common< DT >::hasRegisteredCallBack() const
{  
  return this->hasRegisteredTransportCallBack();
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::hasRegisteredTransportCallBack() const
{  
  return ((0 != this->mModule) && (0 != this->mTransportCb));
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::cleanUp()
{
  delete mMapableIf;
}

template< typename DT > 
typename scml_router_operations_podt_common< DT >::size_type
scml_router_operations_podt_common< DT >::
addressToIndex( uint64 a,
		unsigned int accessSize,
		unsigned int & offSet) const 
{
  const unsigned int byteAddressingMode( addressingMode >> 3);
  const unsigned int size( sizeOf<value_type>());
  const uint64 byteAddress( a * byteAddressingMode);
  const unsigned int LEoffSet = (byteAddress % size) << 3;
  switch( get_endianness()) {
  case cwrLitend:
    offSet = LEoffSet;
    break;
  case cwrBigend:
    {
      const unsigned int sizeBits( size << 3);
      const unsigned int correction( accessSize + LEoffSet);
      if( correction < sizeBits) {
	offSet = sizeBits - correction;
      } else {
	offSet = 0;
      }
    }
    break;
  default:
    offSet = LEoffSet;
    assert( false);
    break;
  }
  return (byteAddress / size);
}

template< typename DT > 
typename scml_router_operations_podt_common< DT >::size_type
scml_router_operations_podt_common< DT >::
addressToIndex( uint64 a) const 
{
  unsigned int offSet;
  const unsigned int accSize( sizeOf<DT>() << 3);
  return addressToIndex( a, accSize, offSet);
}

template< typename DT > 
typename scml_router_operations_podt_common< DT >::uint64
scml_router_operations_podt_common< DT >::
indexToAddress( size_type i ) const {
  const unsigned int byteAddressingMode( addressingMode >> 3);
  const unsigned int size( sizeOf<value_type>());
  const uint64 byteAddress( i * size);
  return (byteAddress / byteAddressingMode);
}

template< typename DT > 
typename scml_router_operations_podt_common< DT >::uint64
scml_router_operations_podt_common< DT >::
indexToByteAddress( size_type i ) const
{
  const unsigned int accSize( sizeOf<DT>() << 3);
  return indexToByteAddress( i, accSize, 0);
}


// see sc_interface

template< typename DT >
void
scml_router_operations_podt_common< DT >::
register_port( sc_port_base &, const char* if_typename_ )
{
  mIsBoundToPort = true;

  const PVInterfaceType pvInterfaceType = determinePVInterfaceType(if_typename_);
  setPVInterfaceType(pvInterfaceType);

}

template< typename DT >
void 
scml_router_operations_podt_common< DT >::
unregisterCB()
{
  if (!mTransportCb) {
    return;
  }

  mModule = 0;
  delete mTransportCb;
  mTransportCb = 0;
  mBlocking = false;
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::
debug_read(uint64 address,
           int size,
           std::vector<unsigned char>& data,
           const char*)
{
  // FIXME: unroll to byte accesses (Vmem may do unaligned accesses)
  for (int i = 0; i < size; ++i) {
    unsigned int offset;
    size_type index = this->addressToIndex(address + i, 8, offset);
    value_type v = this->readDebug(index, 8, offset);
    data.push_back(convert<value_type, unsigned char>(v));
  }
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::
debug_write(uint64 address,
            int size,
            const std::vector<unsigned char>& data,
            const char*)
{
  assert(size == (int)data.size());

  // FIXME: unroll to byte accesses (Vmem may do unaligned accesses)
  for (int i = 0; i < size; ++i) {
    unsigned int offset;
    size_type index = this->addressToIndex(address + i, 8, offset);
    this->writeDebug(data[i], index, 8, offset);
  }
}


/************************************************************************
 * Map/Unmap memory ranges
 *
 */

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
checkOverlap(size_type base, size_type size) const
{
  return checkOverlap(mMappedReadRanges, base, size) || checkOverlap(mMappedWriteRanges, base, size);
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
checkOverlap(const MappedRanges& ranges, size_type base, size_type size) const
{
  MappedRangesConstIter it = ranges.begin();
  MappedRangesConstIter end = ranges.end();
  for (; it != end; ++it) {
    const scml_mapped_range* range = *it;
    const size_type iterLow = range->get_base();
    const size_type iterHigh = range->get_base() + (range->get_size() - 1);
    const size_type low = base;
    const size_type high = base + (size - 1);
    if ((iterLow <= high) && (iterHigh >= low)) {
      return true;
    }
  }
  return false;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
checkRange(size_type base, size_type size) const
{
  // Base address must be aligned on wordsize
  if (base % getWordSize()) {
    return false;
  }

  // Mapped size must be a multiple of wordsize
  if (size % getWordSize()) {
    return false;
  }

  // Mapped size must fit into size of scml_router object
  if ((base + size) > indexToByteAddress(this->size())) {
    return false;
  }

  return true;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
map(size_type base, size_type size, scml_mapable_if& dest, size_type offset)
{
  setPVInterfaceType(dest.getPVInterfaceType());
  dest.setPVInterfaceType(getPVInterfaceType());

  if (!checkRange(base, size) || checkOverlap(base, size)) {
    return false;
  }

  // FIXME: new
  mMappedReadRanges.insert(mMappedReadRanges.begin(), new scml_mapped_range(base, size, dest, offset));
  mMappedWriteRanges.insert(mMappedWriteRanges.begin(), new scml_mapped_range(base, size, dest, offset));
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return true;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
map_read(size_type base, size_type size, scml_mapable_if& dest, size_type offset)
{
  setPVInterfaceType(dest.getPVInterfaceType());
  dest.setPVInterfaceType(getPVInterfaceType());

  if (!checkRange(base, size) || checkOverlap(mMappedReadRanges,base, size)) {
    return false;
  }

  // FIXME: new
  mMappedReadRanges.insert(mMappedReadRanges.begin(), new scml_mapped_range(base, size, dest, offset));
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return true;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
map_write(size_type base, size_type size, scml_mapable_if& dest, size_type offset)
{
  setPVInterfaceType(dest.getPVInterfaceType());
  dest.setPVInterfaceType(getPVInterfaceType());

  if (!checkRange(base, size) || checkOverlap(mMappedWriteRanges,base, size)) {
    return false;
  }

  // FIXME: new
  mMappedWriteRanges.insert(mMappedWriteRanges.begin(), new scml_mapped_range(base, size, dest, offset));
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return true;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
unmap(size_type base)
{
  bool r = unmap(mMappedReadRanges, base);
  bool w = unmap(mMappedWriteRanges, base);
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return r || w;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
unmap_read(size_type base)
{
  bool result = unmap(mMappedReadRanges, base);
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return result;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
unmap_write(size_type base)
{
  bool result = unmap(mMappedWriteRanges, base);
  mMappedRangesObservers.notify_mapped_ranges_changed();
  return result;
}


template< typename DT >
bool
scml_router_operations_podt_common< DT >::
unmap(MappedRanges& ranges, size_type base)
{
  MappedRangesIter it = ranges.begin();
  MappedRangesConstIter end = ranges.end();
  for (; it != end; ++it) {
    scml_mapped_range* range = *it;
    if (range->get_base() == base) {
      //FIXME: delete
      delete range;
      ranges.erase(it);
      return true;
    }
  }
  return false;
}


template< typename DT >
void
scml_router_operations_podt_common< DT >::
unmap_all()
{

  // Read
  MappedRangesIter it = mMappedReadRanges.begin();
  MappedRangesConstIter end = mMappedReadRanges.end();
  for (; it != end; ) {
    // FIXME: delete
    delete *it;
    mMappedReadRanges.erase(it++);
  }
  
  // Write
  it = mMappedWriteRanges.begin();
  end = mMappedWriteRanges.end();
  for (; it != end; ) {
    // FIXME: delete
    delete *it;
    mMappedWriteRanges.erase(it++);
  }

}

template< typename DT >
unsigned int
scml_router_operations_podt_common< DT >::
collect_mapped_read_ranges(std::vector<scml_mapped_range*>& v) const
{
  v.clear();
  std::copy(mMappedReadRanges.begin(),
            mMappedReadRanges.end(),
            std::back_insert_iterator<std::vector<scml_mapped_range*> >(v));
  return mMappedReadRanges.size();
}

template< typename DT >
scml_mapped_range*
scml_router_operations_podt_common< DT >::
get_mapped_read_range(size_type address) const
{
  return getMappedRange(mMappedReadRanges, address);
}

template< typename DT >
unsigned int
scml_router_operations_podt_common< DT >::
collect_mapped_write_ranges(std::vector<scml_mapped_range*>& v) const
{
  v.clear();
  std::copy(mMappedWriteRanges.begin(),
            mMappedWriteRanges.end(),
            std::back_insert_iterator<std::vector<scml_mapped_range*> >(v));
  return mMappedWriteRanges.size();
}

template< typename DT >
scml_mapped_range*
scml_router_operations_podt_common< DT >::
get_mapped_write_range(size_type address) const
{
  return getMappedRange(mMappedWriteRanges, address);
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::
dumpMappedRanges(::std::ostream& os) const
{
  dumpMappedRanges(mMappedReadRanges, os);
  dumpMappedRanges(mMappedWriteRanges, os);
}

template< typename DT >
void
scml_router_operations_podt_common< DT >::
dumpMappedRanges(const MappedRanges& ranges,::std::ostream& os) const
{
  MappedRangesConstIter it = ranges.begin();
  MappedRangesConstIter end = ranges.end();

  os << std::setfill('0') << std::hex;
  for (; it != end; ++it) {
    const scml_mapped_range* range = *it;
    os << "     (0x" << std::setw(8) << range->get_base()
       << " - 0x" << std::setw(8) << (range->get_base() + (size_t) (range->get_size() - 1)) << ") -> "
       << range->get_mapped_name()
       << "   (0x" << std::setw(8) << range->get_offset()
       << " - 0x" << std::setw(8) << (range->get_offset() + (size_t) (range->get_size() - 1)) << ")"
       << std::endl;
  }
  os << std::setfill(' ') << std::dec << std::endl;  
}

template< typename DT >
scml_mapped_range*
scml_router_operations_podt_common< DT >::
getMappedRange(MappedRanges& ranges, size_type address)
{
  MappedRangesIter it = ranges.begin();
  MappedRangesConstIter end = ranges.end();
  for (; it != end; ++it) {
    scml_mapped_range* range = *it;
    if (range->contains(address)) {
      // Keep mapped ranges in MRU order
      ranges.insert(ranges.begin(), *it);
      ranges.erase(it);
      return range;
    }
  }
  return 0;
}

/************************************************************************
 * queries
 */

template< typename DT >
typename scml_router_operations_podt_common< DT >::size_type
scml_router_operations_podt_common< DT >::size() const 
{ 
  return this->memSize;
}

template< typename DT >
typename scml_router_operations_podt_common< DT >::size_type
scml_router_operations_podt_common< DT >::getSize() const 
{ 
  return this->size();
}

template< typename DT >
scml_memory_base::TypeID
scml_router_operations_podt_common< DT >::getType() const 
{ 
  return MEM_TYPE_UNKNOWN;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::isWriteable() const 
{ 
  return true; 
}

template< typename DT >
const char * 
scml_router_operations_podt_common< DT >::getDocumentation() const 
{ 
  return "Unknown Multihop object";
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::isBoundToPort() const
{
  return this->mIsBoundToPort;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::isAlias() const
{ 
  return false;
}

template< typename DT >
typename scml_router_operations_podt_common< DT >::size_type 
scml_router_operations_podt_common< DT >::getTotalOffset() const 
{ 
  assert(0 == this->memOffset);
  return 0;
}

template< typename DT >
typename scml_router_operations_podt_common< DT >::this_pointer_type
scml_router_operations_podt_common< DT >::getParent() const
{ 
  return 0;
}

/************************************************************************
 * additional queries on memories
 */
template< typename DT >
bool
scml_router_operations_podt_common< DT >::
hasTransportCallBack() const
{ 
  return this->hasRegisteredTransportCallBack();
}

/************************************************************************
 * virtual getter setter for instrumentation
 *
 * see scml_memory_base.h
 */
template< typename DT >
scml_memory_base::ErrorCode
scml_router_operations_podt_common< DT >::
getRegisterValueVec(::std::vector< uint8 >& result,
                    uint64 elementIndex,
                    uint32 elementCount)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  const size_type iEnd( i + elementCount );
  if( !isValidIndex( iEnd - 1)) {
    return scml_memory_base::errorInvalidIndex;
  }
  result.clear();
  result.reserve( elementCount * sizeOf<DT>());
  for( ; i != iEnd; ++i ) {
    for (unsigned int byte = 0; byte < sizeOf<DT>(); ++byte) {
      result.push_back(convert<DT, uint8>(this->readDebug(i, 8, byte * 8)));
    }
  }
  return scml_memory_base::noError;
}

template< typename DT >
scml_memory_base::ErrorCode
scml_router_operations_podt_common< DT >::
setRegisterValue(const ::std::vector< uint8 >& result,
                 uint64 elementIndex)
{
  size_type i( elementIndex );
  if( !isValidIndex( i)) {
    return scml_memory_base::errorInvalidIndex;
  }
  if (result.size() != sizeOf<DT>()) {
    return scml_memory_base::errorInvalidType;
  }
  for (unsigned int byte = 0; byte < sizeOf<DT>(); ++byte) {
    this->writeDebug(convert<uint8, DT>(result[byte]), i, 8, byte * 8);
  }
  return scml_memory_base::noError;
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
register_mapped_ranges_observer(scml_mapped_ranges_observer* o)
{
  return mMappedRangesObservers.register_observer(o);
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
unregister_all_mapped_ranges_observers()
{
  return mMappedRangesObservers.unregister_all_observers();
}

template< typename DT >
bool
scml_router_operations_podt_common< DT >::
unregister_mapped_ranges_observer(scml_mapped_ranges_observer* o)
{
  return mMappedRangesObservers.unregister_observer(o);
}

/************************************************************************
 * Explicit Instantiations
 */

//template class scml_router_operations_podt_common< bool >;
//template class scml_router_operations_podt_common< char >;
//// template class scml_router_operations_podt_common< float >;
//// template class scml_router_operations_podt_common< double >;
//// template class scml_router_operations_podt_common< long double >;
//
//template class scml_router_operations_podt_common< signed char >;
//template class scml_router_operations_podt_common< signed short int >;
//template class scml_router_operations_podt_common< signed int >;
//template class scml_router_operations_podt_common< signed long int >;
//template class scml_router_operations_podt_common< signed long long >;

template class scml_router_operations_podt_common< unsigned char >;
template class scml_router_operations_podt_common< unsigned short int >;
template class scml_router_operations_podt_common< unsigned int >;
template class scml_router_operations_podt_common< unsigned long int >;
template class scml_router_operations_podt_common< unsigned long long >;

template class scml_router_operations_podt_common< sc_dt::sc_biguint<128> >;
template class scml_router_operations_podt_common< sc_dt::sc_biguint<256> >;
template class scml_router_operations_podt_common< sc_dt::sc_biguint<512> >;

