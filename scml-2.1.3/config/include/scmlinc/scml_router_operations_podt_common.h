/*****************************************************************************
 *                   Copyright (C) 1996-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML_ROUTER_OPERATIONS_PODT_COMMON_H
#define SCML_ROUTER_OPERATIONS_PODT_COMMON_H

#include <iostream>

#include "scmlinc/scml_memory_base.h"
#include "scmlinc/scml_memory_user.h"
#include "scmlinc/scml_memsize.h"
#include "scmlinc/scml_transport_if.h"
#include "scmlinc/scml_mapable_if.h"
#include "scmlinc/scml_transport_callback.h"
#include "scmlinc/scml_mapped_ranges_observers.h"

#include "scmlinc/scml_memory_registration.h"
#include "scmlinc/scml_memory_utils.h"
#include <scml2_logging/stream.h>
#include <list>
#include <vector>

class scml_mapped_range;
template <typename DT, typename AT> class scml_post_port;
template <typename DT> class scml_mapable_if_to_T;

/************************************************************************ 
 *
 * operation on scml_router shared by plain old data types
 *
 * see scml_router.h 
 *
 */

template< typename DT > 
class scml_router_operations_podt_common :
  public scml_memory_base
{
public:
  typedef DT value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef scml_memory_base::uint64 size_type;
  typedef ptrdiff_t difference_type;

  typedef scml_router_operations_podt_common< value_type > this_type;
  typedef this_type * this_pointer_type;
  typedef const this_type * const_this_pointer_type;
  typedef this_type & this_reference_type;

  typedef scml_memory_pv_32_32_if::request_type request_32_32_type;
  typedef scml_memory_pv_32_32_if::response_type response_32_32_type;

  typedef scml_memory_pv_32_64_if::request_type request_32_64_type;
  typedef scml_memory_pv_32_64_if::response_type response_32_64_type;

  typedef scml_memory_pv_32_128_if::request_type request_32_128_type;
  typedef scml_memory_pv_32_128_if::response_type response_32_128_type;

  typedef scml_memory_pv_32_256_if::request_type request_32_256_type;
  typedef scml_memory_pv_32_256_if::response_type response_32_256_type;

  typedef scml_memory_pv_32_512_if::request_type request_32_512_type;
  typedef scml_memory_pv_32_512_if::response_type response_32_512_type;

  typedef scml_memory_pv_64_32_if::request_type request_64_32_type;
  typedef scml_memory_pv_64_32_if::response_type response_64_32_type;

  typedef scml_memory_pv_64_64_if::request_type request_64_64_type;
  typedef scml_memory_pv_64_64_if::response_type response_64_64_type;

  typedef scml_memory_pv_64_128_if::request_type request_64_128_type;
  typedef scml_memory_pv_64_128_if::response_type response_64_128_type;

  typedef scml_memory_pv_64_256_if::request_type request_64_256_type;
  typedef scml_memory_pv_64_256_if::response_type response_64_256_type;

  typedef scml_memory_pv_64_512_if::request_type request_64_512_type;
  typedef scml_memory_pv_64_512_if::response_type response_64_512_type;

  // backwards compatibility
  typedef request_32_32_type request32_type;
  typedef response_32_32_type response32_type;
  typedef request_32_64_type request64_type;
  typedef response_32_64_type response64_type;
  typedef request_32_128_type request128_type;
  typedef response_32_128_type response128_type;
  typedef request_32_256_type request256_type;
  typedef response_32_256_type response256_type;
  typedef request_32_512_type request512_type;
  typedef response_32_512_type response512_type;


  typedef scml_memory_user::user_id_data_type user_id_data_type;
  typedef scml_memory_base::uint64 uint64;

  typedef scml_memory_base::ErrorCode ErrorCode;
     
  typedef std::list<scml_mapped_range*> MappedRanges;
  typedef typename MappedRanges::iterator MappedRangesIter;
  typedef typename MappedRanges::const_iterator MappedRangesConstIter;

  typedef scml_memory_base::PVInterfaceType PVInterfaceType;

protected:
  // constructors & destructor
  scml_router_operations_podt_common();
  explicit scml_router_operations_podt_common( const char * n );
  explicit scml_router_operations_podt_common( scml_memsize );  
  scml_router_operations_podt_common( const char * n, scml_memsize );
  virtual ~scml_router_operations_podt_common();

private:
  // disable copy and assignment
  scml_router_operations_podt_common( const scml_router_operations_podt_common & );
  scml_router_operations_podt_common& operator=( const scml_router_operations_podt_common & );

public:
  // conversion operator to scml_mapable_if
  template <typename T> friend class scml_mapable_if_to_T;
  operator scml_mapable_if&();
  operator const scml_mapable_if&() const;

  virtual const char* getName() const { return scml_memory_base::getName(); }

  value_type read( size_type a = 0 );
  value_type read( size_type, unsigned int acSiz, unsigned int offSet);
  value_type readDebug( size_type a = 0);
  value_type readDebug( size_type, unsigned int acSiz, unsigned int offSet);
  void write( value_type, size_type a = 0 );
  void write( value_type, size_type, unsigned int acSiz, unsigned int offSet);
  void writeDebug( value_type, size_type a = 0);
  void writeDebug( value_type, size_type, unsigned int acSiz, unsigned int offSet);
  

  virtual bool isRouter() const { return true; }

  virtual bool trigger_behaviour_on_debug_read() const;
  virtual bool trigger_behaviour_on_debug_write() const;

  size_type size() const;
  void set_endianness( scml_endian a );
  scml_endian get_endianness() const;
  void set_addressing_mode( unsigned int a );
  unsigned int get_addressing_mode() const;

  // address & index relations
  size_type addressToIndex( uint64 ) const;
  size_type addressToIndex( uint64 a,
			    unsigned int accessSize,
			    unsigned int & offSet) const;
  uint64 indexToAddress( size_type ) const;
  uint64 indexToByteAddress( size_type ) const;
  uint64 indexToByteAddress( size_type i,
			     unsigned int accessSize,
			     unsigned int offSet) const;

  // virtuals queries for clients for scml_memory_base
  virtual size_type getSize() const;
  virtual TypeID getType() const;
  virtual bool isWriteable() const;
  virtual const char * getDocumentation() const;
  virtual bool isBoundToPort() const;

  // queries for alias relations
  virtual bool isAlias() const;
  virtual size_type getTotalOffset() const;
  virtual this_pointer_type getParent() const;
  virtual unsigned int getWordSize() const { return scml::sizeOf<DT>(); }

  // default latency setting for PV response
  unsigned int get_default_response_latency() const;
  void set_default_response_latency( unsigned int l);

  // Virtual PV transport interface
  #define DECLARE_TRANSPORT(IF) \
    virtual IF::response_type transport(const IF::request_type& );
  SCML_FOR_EACH_PV_INTERFACE_TYPE(DECLARE_TRANSPORT)
  #undef DECLARE_TRANSPORT

  void unregisterCB();

  template< typename MOD, typename REQ, typename RESP >
  void registerTransportCB( MOD * m,
			    RESP (MOD::*f) ( const REQ & ),
			    bool isBlocking = true,
			    user_id_data_type id = 0,
                            const std::string& cbName = "");

  virtual bool updateBlockingProperty( bool isBlocking );

  // see sc_interface
  virtual void register_port( sc_port_base & port_, const char* if_typename_ );

  // see cwrSdiCallback
  virtual void debug_read(uint64 address,
                          int size,
                          std::vector<unsigned char>& data,
                          const char* target = NULL);
  virtual void debug_write(uint64 address,
                           int size,
                           const std::vector<unsigned char>& data,
                           const char* target = NULL);

  // Mapping ranges
  bool checkOverlap(size_type base, size_type size) const;
  bool checkRange(size_type base, size_type size) const;

  bool map(size_type base, size_type size, scml_mapable_if& d, size_type offset);
  bool map_read(size_type base, size_type size, scml_mapable_if& d, size_type offset);
  bool map_write(size_type base, size_type size, scml_mapable_if& d, size_type offset);

  bool unmap(size_type base);
  bool unmap_read(size_type base);
  bool unmap_write(size_type base);
  void unmap_all();
 
  unsigned int collect_mapped_read_ranges(std::vector<scml_mapped_range*>& v) const;
  scml_mapped_range* get_mapped_read_range(size_type address) const;
  unsigned int collect_mapped_write_ranges(std::vector<scml_mapped_range*>& v) const;
  scml_mapped_range* get_mapped_write_range(size_type address) const;

  void dumpMappedRanges(::std::ostream& os) const;

  static scml_mapped_range* getMappedRange(MappedRanges&, size_type address);
  

  // additional queries on memories
  virtual bool hasTransportCallBack() const;

   // serialized getter/setter
  virtual ErrorCode getRegisterValueVec(::std::vector< uint8 >& result,
                                        uint64 elementIndex = 0,
                                        uint32 elementCount = 1);
  virtual ErrorCode setRegisterValue(const ::std::vector<  uint8 >& result,
                                     uint64 elementIndex = 0); 

  bool register_mapped_ranges_observer(scml_mapped_ranges_observer* o);
  bool unregister_all_mapped_ranges_observers();
  bool unregister_mapped_ranges_observer(scml_mapped_ranges_observer* o);

protected:

  // helpers for PV
  template <typename IF>
  typename IF::response_type transportProp( const typename IF::request_type & );
  template <typename IF>
  typename IF::response_type transportImp( const typename IF::request_type & );
  template <typename IF>
  typename IF::response_type burstUnrollingTransportImp( const typename IF::request_type & );

  // helper functions
  void cleanUp();
  bool hasRegisteredCallBack() const;
  bool hasRegisteredTransportCallBack() const;
  bool hasBehaviourAttached() const;

  value_type readProp(size_type, unsigned int acSiz, unsigned int offSet, bool isDebug);
  template< typename IF >
  value_type readImp(size_type, unsigned int acSiz, unsigned int offSet, bool isDebug);
  void writeProp(value_type, size_type, unsigned int acSiz, unsigned int offSet, bool isDebug);
  template< typename IF >
  void writeImp(value_type, size_type, unsigned int acSiz, unsigned int offSet, bool isDebug);


  bool isValidIndex( size_type i) const;

  // Methods that work on mapped ranges
  bool checkOverlap(const MappedRanges&, size_type base, size_type size) const;
  bool unmap(MappedRanges& ranges, size_type base);
  void dumpMappedRanges(const MappedRanges& ranges, ::std::ostream& os) const;


  bool checkPVInterfaceType(PVInterfaceType pvInterfaceType) const;
  virtual void setPVInterfaceType(PVInterfaceType pvInterfaceType);
  virtual PVInterfaceType getPVInterfaceType() const;

  // query callbacks
  virtual CallBackType getCallBackType() const;
  virtual bool getTransportCallBackName(std::string& name) const;

  template <typename REQ>
  void checkBurstAccess(const REQ& req) const;

private:
  mutable scml2::logging::stream mError;
  mutable scml2::logging::stream mWarning;
  // data members
  size_type memOffset;
  size_type memSize;
  cwrEnd endianness;
  bool mHasHostEndianness;
  unsigned int addressingMode;

  // PV transport like call back functionality
  sc_module * mModule;
  scml_transport_if* mTransportCb;

  bool mBlocking;
  user_id_data_type mUserId;
  std::string mTransportCallBackName;

  PVInterfaceType mPVInterfaceType;
  bool mIsBoundToPort;
  unsigned int mDefaultRespLatency;

  mutable MappedRanges mMappedReadRanges, mMappedWriteRanges;

  scml_mapable_if* mMapableIf;

  scml_mapped_ranges_observers mMappedRangesObservers;
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 *
 * PV transport like call back registration
 */

template< typename DT >
template< typename MOD, typename REQ, typename RESP >
inline
void
scml_router_operations_podt_common< DT >::
registerTransportCB( MOD * mod,
		     RESP (MOD::*f) ( const REQ & ),
		     bool isBlocking,
		     user_id_data_type id,
                     const std::string& cbName)
{
  typedef RESP (sc_module::*TransportFuncPtr)(const REQ&);
  typedef typename scml::Types2If<typename REQ::data_type, typename REQ::address_type>::result IF;
  
  setPVInterfaceType((PVInterfaceType)scml::If2PVInterfaceType<IF>::result);

  if( 0 == mod) {
    return;
  }
  mModule = mod;
  mUserId = id;
  delete mTransportCb;
  mTransportCb = new scml_transport_callback<IF>(mod, static_cast<TransportFuncPtr>(f));
  mTransportCallBackName = cbName;
  updateBlockingProperty(isBlocking);
}

template< typename DT > 
inline
typename scml_router_operations_podt_common<DT>::uint64 
scml_router_operations_podt_common<DT>::indexToByteAddress( size_type i,
		                                            unsigned int accessSize,
      			                                    unsigned int offSet) const
{
  const unsigned int size( scml::sizeOf<value_type>());
  int correction( 0);
  switch( get_endianness()) {
    case  cwrLitend:
      correction = (offSet >> 3);
      break;
    case  cwrBigend:
      correction = size - ((accessSize + offSet) >> 3);
      break;
    default:
      assert( false);
      break;
  }  
  return (( i * size) + correction);
}

#endif
