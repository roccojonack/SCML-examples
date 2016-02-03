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
 * Purpose of file : Definition of scml_memory modeling object
 *
 */

#ifndef SCML_MEMORY_OPERATIONS_PODT_COMMON_H
#define SCML_MEMORY_OPERATIONS_PODT_COMMON_H

#include <scml2_logging/stream.h>
#include <set>
#include <map>
#include <iostream>

#include "scmlinc/scml_bitfield.h"
#include "scmlinc/scml_bitfield_container.h"
#include "scmlinc/scml_memory_base.h"
#include "scmlinc/scml_memory_user.h"
#include "scmlinc/scml_memsize.h"
#include "scmlinc/scml_transport_if.h"
#include "scmlinc/scml_mapable_if.h"
#include "scmlinc/scml_transport_callback.h"

#include "scmlinc/scml_memory_registration.h"
#include "scmlinc/scml_memory_utils.h"


template<typename DT>
class scml_memory_operations_impl_base
{
public:
  typedef DT value_type;
  typedef unsigned long long size_type;
  
public:
  scml_memory_operations_impl_base() {}
  virtual ~scml_memory_operations_impl_base() {}
  
  virtual value_type getValue() const = 0;
  virtual value_type getValue(size_type index) const = 0;
  virtual void setValue(const value_type rhs) = 0;
  virtual void setValue(const value_type rhs, size_type index) = 0;
  
  virtual value_type getBits(size_type index, unsigned int offset, unsigned int acSize) const = 0;
  virtual void setBits(const value_type rhs, size_type index, unsigned int offset, unsigned int acSize) = 0;
  
  virtual value_type getValueDebug(size_type index=0) const = 0;
  virtual value_type getValueDebug(size_type index, unsigned int offset, unsigned int acSize) const = 0;
  virtual void setValueDebug(const value_type rhs, size_type index=0) = 0;
  virtual void setValueDebug(const value_type rhs, size_type index, unsigned int offset, unsigned int acSize) = 0;
  
  virtual void doMultiply(const value_type  rhs) = 0;
  virtual void doDivide(const value_type  rhs) = 0;
  virtual void doAdd(const value_type  rhs) = 0;
  virtual void doSubtract(const value_type  rhs) = 0;
  virtual void doModulo(const value_type  rhs) = 0;
  virtual void doAnd(const value_type  rhs) = 0;
  virtual void doOr(const value_type  rhs) = 0;
  virtual void doXor(const value_type  rhs) = 0;
  virtual void doShiftLeft(const value_type  rhs) = 0;
  virtual void doShiftRight(const value_type  rhs) = 0;
  
  virtual void doPreIncrement() = 0;
  virtual void doPreDecrement() = 0;
  virtual value_type doPostIncrement() = 0;
  virtual value_type doPostDecrement() = 0;
};

namespace scml_memory_operations_impl_helpers
{
  template <typename DT> class Normal;
  template <typename DT> class ImplSelector;
};

template <typename DT> class scml_memory_iterator;
template <typename DT> class scml_mapable_if_to_T;

/************************************************************************ 
 *
 * operation on scml_memory shared by plain old data types
 *
 * see scml_memory.h 
 *
 */

template< typename DT > 
class scml_memory_operations_podt_common :
  public scml_memory_base,
  public scml_bitfield_container_if
{
public:
  typedef DT value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef scml_memory_base::size_type size_type;
  typedef ptrdiff_t difference_type;

  typedef scml_memory_operations_podt_common< value_type > this_type;
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


  typedef value_type (sc_module::*readCbFuncPtr) ( unsigned int accessSize, 
						   unsigned int offset );
  typedef void (sc_module::*writeCbFuncPtr) ( value_type data,
					      unsigned int accessSize, 
					      unsigned int offset );
  typedef scml_memory_user::user_id_data_type user_id_data_type;
  typedef scml_memory_base::uint64 uint64;
  typedef scml_bitfield_container_if::scml_bitfield_container_entry scml_bitfield_container_entry;

  typedef scml_memory_base::ErrorCode ErrorCode;

  typedef scml_memory_base::PVInterfaceType PVInterfaceType;

protected:
  // constructors & destructor
  scml_memory_operations_podt_common();
  explicit scml_memory_operations_podt_common( value_type );
  explicit scml_memory_operations_podt_common( const char * n );
  explicit scml_memory_operations_podt_common( scml_memsize );  
  scml_memory_operations_podt_common( const char * n, scml_memsize );
  virtual ~scml_memory_operations_podt_common();

  // alias constructors
  scml_memory_operations_podt_common( scml_memory_operations_podt_common & a,
				      size_type offset, size_type size );
  scml_memory_operations_podt_common( const char * n,
				      scml_memory_operations_podt_common & a, 
				      size_type offset, size_type size );

private:
  // disable copy and assignment
  scml_memory_operations_podt_common( const scml_memory_operations_podt_common & );
  scml_memory_operations_podt_common& operator=( const scml_memory_operations_podt_common & );

public:
  virtual const char* getName() const { return scml_memory_base::getName(); }

  operator DT() const;
  // conversion operator to scml_mapable_if
  template <typename T> friend class scml_mapable_if_to_T;
  operator scml_mapable_if&();
  operator const scml_mapable_if&() const;

  // access methods
  value_type operator[] ( size_type ) const ;

  value_type get( size_type a = 0 ) const ;
  value_type get( size_type, unsigned int acSiz, unsigned int offSet) const ;
  void put( value_type, size_type a = 0 );
  void put( value_type, size_type, unsigned int acSiz, unsigned int offSet);

  value_type read( size_type a = 0 );
  value_type read( size_type, unsigned int acSiz, unsigned int offSet);
  value_type readDebug( size_type a = 0);
  value_type readDebug( size_type, unsigned int acSiz, unsigned int offSet);
  void write( value_type, size_type a = 0 );
  void write( value_type, size_type, unsigned int acSiz, unsigned int offSet);
  void writeDebug( value_type, size_type a = 0);
  void writeDebug( value_type, size_type, unsigned int acSiz, unsigned int offSet);
  
  // bit access
  void put_bits( value_type val, size_type index, unsigned int offset, unsigned int nBits );
  value_type get_bits( size_type index, unsigned int offset, unsigned int nBits ) const;

  // arithmetic assignments
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

  // decrement & increment
  this_reference_type operator -- (); // prefix
  value_type operator -- ( int);      // postfix
  this_reference_type operator ++ (); // prefix
  value_type operator ++ ( int);      // postfix

  friend class scml_memory_iterator<DT>;
  template <typename T> friend class scml_memory_operations_impl_helpers::ImplSelector;
  template <typename T> friend class scml_memory_operations_impl_helpers::Normal;

  size_type size() const { return this->memSize; }
  size_type offset() const { return this->memOffset; }
  void set_endianness( scml_endian a );
  void set_addressing_mode( unsigned int a );

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
  virtual scml_endian get_endianness() const;
  virtual unsigned int get_addressing_mode() const;


  // queries for alias relations
  virtual bool isAlias() const;
  virtual size_type getTotalOffset() const;
  virtual this_pointer_type getParent() const;
  virtual unsigned int getWordSize() const { return scml::sizeOf<DT>(); }

  virtual bool isRouter() const { return false; }

  // default setting for PV response
  unsigned int get_default_response_latency() const;
  void set_default_response_latency( unsigned int l);
  PVResponse get_default_response_status() const;
  void set_default_response_status( PVResponse s);

  // Non-virtual PV transport interface
  template <typename IF> typename IF::response_type nonVirtualTransport(const typename IF::request_type& req);
  // Virtual PV transport interface
  #define DECLARE_TRANSPORT(IF) \
    virtual IF::response_type transport(const IF::request_type& );
  SCML_FOR_EACH_PV_INTERFACE_TYPE(DECLARE_TRANSPORT)
  #undef DECLARE_TRANSPORT

  void unregisterCB();
  void unregisterReadCB();
  void unregisterWriteCB();

  template< typename MOD, typename REQ, typename RESP >
  void registerTransportCB(MOD * m,
                           RESP (MOD::*f) ( const REQ & ),
                           bool isBlocking = true,
                           user_id_data_type id = 0,
                           const std::string& cbName = "");
  template< typename MOD >
  void registerReadCB( MOD * m, 
		       value_type (MOD::*f) ( unsigned int,
					      unsigned int),		      
		       bool isBlocking = true,
		       user_id_data_type id = 0,
                       const std::string& cbName = "");
  template< typename MOD >
  void registerWriteCB( MOD * m, 
			void (MOD::*f) ( value_type,
					 unsigned int,
					 unsigned int),
			bool isBlocking = true,
			user_id_data_type id = 0,
                        const std::string& cbName = "");
  
  // support for bit fields
  virtual bool registerBitfields( scml_bitfield_container_entry );
  virtual bool updateReadBlockingProperty( bool isBlocking );
  virtual bool updateWriteBlockingProperty( bool isBlocking );
  virtual scml_bitfield_container_if::value_type getBitfieldValue( unsigned int offset,
                                                                   unsigned int size);
  virtual void setBitfieldValue( scml_bitfield_container_if::value_type a, 
				 unsigned int offset,
				 unsigned int size);

  // see sc_interface
  virtual void register_port( sc_port_base & port_, const char* if_typename_ );
  

  bool store_after_read_call() const;
  void set_store_after_read_call( bool  b);

  // additional queries on memories
  virtual bool hasReadCallBack() const;
  virtual bool hasWriteCallBack() const;
  virtual bool hasTransportCallBack() const;
  virtual bool hasBitfieldsAttached() const;
  virtual bool getBitfieldPointers( bitfield_pointer_container & ) const;
  
  // initialisation
  void initialize( value_type a = DT());

  // behaviour on debug
  bool trigger_behaviour_on_debug_read() const;
  void set_trigger_behaviour_on_debug_read( bool );
  bool trigger_behaviour_on_debug_write() const;
  void set_trigger_behaviour_on_debug_write( bool );

  // release storage if owned locally
  bool release_storage();

  // serialized getter/setter
  virtual ErrorCode getRegisterValueVec(::std::vector< uint8 >& result,
                                        uint64 elementIndex = 0,
                                        uint32 elementCount = 1);
  virtual ErrorCode setRegisterValue(const ::std::vector<  uint8 >& result,
                                     uint64 elementIndex = 0);

  typedef scml_memory_base::memory_pointer_container memory_pointer_container;
  virtual unsigned int getAliasPointers(memory_pointer_container&) const;

protected:
  typedef ::std::vector< this_pointer_type > vector_alias_pointer_type;
  typedef ::std::vector< value_type > vector_value_type;

  // helpers for PV
  template <typename IF>
  typename IF::response_type transportProp(const typename IF::request_type&);
  template <typename IF>
  typename IF::response_type transportImp(const typename IF::request_type&);
  template <typename IF>
  typename IF::response_type burstUnrollingTransportImp(const typename IF::request_type &);

  // helper functions
  void cleanUp();
  bool hasRegisteredCallBack() const;
  bool hasRegisteredCallBackForRead() const;
  bool hasRegisteredCallBackForWrite() const;
  bool hasRegisteredReadCallBack() const;
  bool hasRegisteredWriteCallBack() const;
  bool hasRegisteredTransportCallBack() const;
  bool hasBitfields() const;
  bool hasBehaviourAttached() const;
  bool hasReadBehaviourAttached() const;
  bool hasWriteBehaviourAttached() const;
  void registerAsAlias( this_pointer_type a );
  bool isAliasImp() const;
  void sanityCheckOnAliasRelations() const;
  this_pointer_type findAliasForIndex( size_type indexLo, size_type indexHi );
  const_this_pointer_type findAncestorWithReadBehaviour() const;
  this_pointer_type findAncestorWithReadBehaviour();
  const_this_pointer_type findAncestorWithWriteBehaviour() const;
  this_pointer_type findAncestorWithWriteBehaviour();
  bool hasRefinedReadBehaviourForIndex( size_type indexLo, size_type indexHi );
  bool hasRefinedWriteBehaviourForIndex( size_type indexLo, size_type indexHi );

  void updateFastAccess();
  void propagateUpdateFastAccess();

  value_type readProp(size_type, unsigned int acSiz, unsigned int offSet, bool isDebug);
  template< typename IF >
  value_type readImp(size_type, unsigned int acSiz, unsigned int offSet, bool isDebug);
  void writeProp(value_type, size_type, unsigned int acSiz, unsigned int offSet, bool isDebug);
  template< typename IF >
  void writeImp(value_type, size_type, unsigned int acSiz, unsigned int offSet, bool isDebug);

  template< typename IF >
  void writeBitfield(const typename IF::data_type& writeData,
                     unsigned int dataSize,
                     unsigned int offSet);

  void actualReloadAccessDescriptors() const;


  bool isValidIndex( size_type i) const;


  // helpers for access
  value_type getDebug( size_type, unsigned int, unsigned int ) const;
  value_type getDebug( size_type a = 0 ) const;
  void putDebug( value_type, size_type, unsigned int, unsigned int );
  void putDebug( value_type, size_type a = 0 );


  bool checkPVInterfaceType(PVInterfaceType pvInterfaceType) const;
  virtual void setPVInterfaceType(PVInterfaceType pvInterfaceType);
  virtual PVInterfaceType getPVInterfaceType() const;

  // query callbacks
  virtual CallBackType getCallBackType() const;
  virtual bool getTransportCallBackName(std::string& name) const;
  virtual bool getReadCallBackName(std::string& name) const;
  virtual bool getWriteCallBackName(std::string& name) const;

  template <typename REQ>
  void checkBurstAccess(const REQ& req) const;
  void checkRange(size_type index, unsigned int burstCount) const;

private:
  // Shared Data between aliases, owned by toplevel memory
  struct SharedData {
    SharedData(const std::string& toplevelName);
    ~SharedData();

    mutable scml2::logging::stream mError;
    mutable scml2::logging::stream mWarning;

    vector_value_type* spm;
    cwrEnd endianness;
    bool mHasHostEndianness;
    unsigned int addressingMode;
    PVInterfaceType mPVInterfaceType;
  };

private:
  // data members
  SharedData* mSharedData; // owner if NOT alias
  size_type memOffset;
  size_type memSize;
  scml_memory_operations_impl_base<value_type>* mFastAccess;

  // PV transport like call back functionality
  sc_module * mModule;
  scml_transport_if* mTransportCb;

  readCbFuncPtr mReadCb;
  writeCbFuncPtr mWriteCb;
  bool mBlockingRead;
  bool mBlockingWrite;
  user_id_data_type mUserId;
  std::string mTransportCallBackName;
  std::string mReadCallBackName;
  std::string mWriteCallBackName;

  // alias bookkeeping
  this_pointer_type parent;
  vector_alias_pointer_type aliases;

  // support for bitfields
  scml_bitfield_container * bitfieldContainer; // owner
  
  bool mIsBoundToPort;
  bool mStoreAfterReadCall;
  unsigned int mDefaultRespLatency;
  PVResponse mDefaultRespStatus;
  bool mTriggerBehaviourOnDebugRead;
  bool mTriggerBehaviourOnDebugWrite;

  // pointer to toplevel scml_memory
  this_pointer_type mToplevel;
  scml_mapable_if* mMapableIf;
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
scml_memory_operations_podt_common< DT >::
registerTransportCB(MOD * mod,
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
  if(( 0 == mReadCb) && (0 == mWriteCb)) { // NOP
  } else {
    SCML2_LOG(mSharedData->mWarning)
      << "Registering a tranport call back on " << mod->name()
      << " disables the previously registered call backs."
      << ::std::endl;
  }
  mReadCb = 0;
  mWriteCb = 0;
  mModule = mod;
  mUserId = id;
  delete mTransportCb;
  mTransportCb = new scml_transport_callback<IF>(mod, static_cast<TransportFuncPtr>(f));
  mTransportCallBackName = cbName;
  updateReadBlockingProperty( isBlocking);
  updateWriteBlockingProperty( isBlocking);
}

template< typename DT >
template< typename MOD >
inline
void
scml_memory_operations_podt_common< DT >::
registerReadCB( MOD * mod, 
		value_type (MOD::*f) ( unsigned int,
				       unsigned int),		      
		bool isBlocking,
		user_id_data_type id,
                const std::string& cbName)
{
  if( 0 == mod) {
    return;
  }
  if( 0 == mTransportCb) { // NOP
  } else { 
    SCML2_LOG(mSharedData->mWarning)
      << "Registering a read call back on " << mod->name()
      << " disables the previously registered transport call back."
      << ::std::endl;
  }
  delete mTransportCb;
  mTransportCb = 0;
  mModule = mod;
  mUserId = id;
  mReadCb = static_cast < readCbFuncPtr > ( f);
  mReadCallBackName = cbName;
  updateReadBlockingProperty( isBlocking);
}

template< typename DT > 
template< typename MOD >
inline
void
scml_memory_operations_podt_common< DT >::
registerWriteCB( MOD * mod, 
		 void (MOD::*f) ( value_type,
				  unsigned int,
				  unsigned int),
		 bool isBlocking,
		 user_id_data_type id,
                 const std::string& cbName)
{
  if( 0 == mod) {
    return;
  }
  if( 0 == mTransportCb) { // NOP
  } else {
    SCML2_LOG(mSharedData->mWarning)
      << "Registering a write call back on " << mod->name()
      << " disables the previously registered transport call back."
      << ::std::endl;
  }
  delete mTransportCb;
  mTransportCb = 0;
  mModule = mod;
  mUserId = id;
  mWriteCb = static_cast < writeCbFuncPtr > ( f);
  mWriteCallBackName = cbName;
  updateWriteBlockingProperty( isBlocking);
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common<DT>::uint64 
scml_memory_operations_podt_common<DT>::indexToByteAddress( size_type i,
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




/************************************************************************
 * arithmetic assignments
 */
template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator += ( value_type a )
{
  mFastAccess->doAdd(a);
  return *this;
}

template< typename DT > 
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator -= ( value_type a )
{
  mFastAccess->doSubtract(a);
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator /= ( value_type a )
{
  mFastAccess->doDivide(a);
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator *= ( value_type a )
{
  mFastAccess->doMultiply(a);
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator %= ( value_type a )
{
  mFastAccess->doModulo(a);
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator ^= ( value_type a )
{
  mFastAccess->doXor(a);
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator &= ( value_type a )
{
  mFastAccess->doAnd(a);
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator |= ( value_type a )
{
  mFastAccess->doOr(a);
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator <<= ( value_type a )
{
  mFastAccess->doShiftLeft(a);
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator >>= ( value_type a )
{
  mFastAccess->doShiftRight(a);
  return *this;
}

/************************************************************************
 * increment & decrement
 */
template< typename DT >
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator -- ()
{
  mFastAccess->doPreDecrement();
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::operator -- ( int)
{
  return mFastAccess->doPostDecrement();
}

template< typename DT >
inline
typename scml_memory_operations_podt_common< DT >::this_reference_type
scml_memory_operations_podt_common< DT >::operator ++ ()
{
  mFastAccess->doPreIncrement();
  return *this;
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::operator ++ ( int)
{
  return mFastAccess->doPostIncrement(); 
}

/************************************************************************
 * bit access
 * get and put
 */

template< typename DT >
inline
void
scml_memory_operations_podt_common< DT >::put_bits( value_type val,
    size_type index,
    unsigned int offset,
    unsigned int nBits )
{
  mFastAccess->setBits(val, index, offset, nBits);
}

template< typename DT >
inline
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::get_bits( size_type index,
    unsigned int offset,
    unsigned int nBits ) const
{
  return mFastAccess->getBits(index ,offset, nBits);
}

/************************************************************************
 * access
 * get and put
 * read and write
 */

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::get( size_type a ) const
{
  return mFastAccess->getValue(a);
}

template< typename DT >
inline
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::operator[] ( size_type a ) const
{
  return get( a );
}

template< typename DT > 
inline
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::get( size_type a,
    unsigned int acSiz,
    unsigned int offSet ) const
{
  return mFastAccess->getBits(a, offSet, acSiz);
}

template< typename DT >
inline
void
scml_memory_operations_podt_common< DT >::put( value_type v,
    size_type a ) 
{
  mFastAccess->setValue(v, a);
}

template< typename DT >
inline
void
scml_memory_operations_podt_common< DT >::put( value_type v,
    size_type a,
    unsigned int acSiz,
    unsigned int offSet )
{
  mFastAccess->setBits(v, a, offSet, acSiz);
}

/************************************************************************
 * value type operator
 */
template< typename DT >
inline
scml_memory_operations_podt_common< DT >::
operator DT() const
{
  return mFastAccess->getValue();
}

#endif
