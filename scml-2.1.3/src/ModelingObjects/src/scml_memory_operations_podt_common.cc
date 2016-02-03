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

#include "scmlinc/scml_memory_operations_podt_common.h"
#include "scmlinc/scml_memory_registration.h"
#include "scmlinc/scml_synchroniser_registry.h"
#include "scmlinc/scml_mapable_if_to_T.h"
#include <scml2_logging/stream.h>
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

template<typename DT, typename I>
    class scml_memory_operations_impl;
    
namespace scml_memory_operations_impl_helpers {
  template<typename DT>
  class FastNoSwap
  {
    public:
      typedef DT value_type;
      typedef unsigned long long size_type;
    public:
      FastNoSwap(unsigned char* data, size_type memOffset) :
        mData(reinterpret_cast<value_type*>(data)+memOffset) {}
      ~FastNoSwap() {}
      
      value_type getData(size_type index = 0) const { return mData[index]; }
      void setData(value_type value, size_type index = 0) { mData[index] = value; }

    private:
      value_type* mData;
  };

  template<int N>
  class FastNoSwap<sc_dt::sc_biguint<N> >
  {
    public:
      typedef sc_dt::sc_biguint<N> value_type;
      typedef unsigned long long size_type;
    public:
      FastNoSwap(unsigned char* data, size_type memOffset) :
        mData(data + memOffset * sizeOf<value_type>()) {}
      ~FastNoSwap() {}
      
      value_type getData(size_type index = 0) const
      {
        value_type tmp;
        copyFromArray(tmp, mData + index * sizeOf<value_type>());
        return tmp;
      }
      void setData(value_type value, size_type index = 0)
      {
        copyToArray(value, mData + index * sizeOf<value_type>());
      }

    private:
    unsigned char* mData;
  };
  
  template<typename DT>
  class FastSwap
  {
    public:
      typedef DT value_type;
      typedef unsigned long long size_type;
    public:
      FastSwap(unsigned char* data, size_type memOffset) :
        mData(reinterpret_cast<value_type*>(data)+memOffset) {}
      ~FastSwap() {}
      
      value_type getData(size_type index = 0) const { return scml_memory_utils::swap_bytes(mData[index]); }
      void setData(value_type value, size_type index = 0) { mData[index] = scml_memory_utils::swap_bytes(value); }

    private:
      value_type* mData;
  };

  template<int N>
  class FastSwap<sc_dt::sc_biguint<N> >
  {
    public:
      typedef sc_dt::sc_biguint<N> value_type;
      typedef unsigned long long size_type;
    public:
      FastSwap(unsigned char* data, size_type memOffset) :
        mData(data + memOffset * sizeOf<value_type>()) {}
      ~FastSwap() {}
      
      value_type getData(size_type index = 0) const
      {
        value_type tmp;
        swapFromArray(tmp, mData + index * sizeOf<value_type>());
        return tmp;
      }
      void setData(value_type value, size_type index = 0)
      {
        swapToArray(value, mData + index * sizeOf<value_type>());
      }

    private:
    unsigned char* mData;
  };

  template <typename DT>
  class Normal
  {
    public:
      typedef DT value_type;
      typedef typename scml_memory_operations_podt_common<DT>::vector_value_type vector_value_type;
      typedef unsigned long long size_type;
    public:
      Normal(vector_value_type& vector, size_type index) : mVector(vector), mOffset(index) {}
      ~Normal() {}
      
      value_type getData(size_type index = 0) const { return mVector[mOffset+index]; }
      void setData(value_type value, size_type index = 0) { mVector[mOffset+index] = value; }
      
    private:
      vector_value_type&           mVector;
      unsigned int                 mOffset;
  };
  
  
  // Helper class that allows us to automatically delegate 'normal'
  // and 'bool' implementation to something different.
  template <typename DT>
  class ImplSelector
  {
    public:
      typedef DT value_type;
      typedef typename scml_memory_operations_podt_common<DT>::vector_value_type vector_value_type;
      typedef unsigned long long size_type;
        
      typedef FastNoSwap<DT> Selected;
      static Selected createImpl(vector_value_type& v, size_type index)
      { return Selected(reinterpret_cast<unsigned char*>(&v[index]), 0); } 
      typedef FastSwap<DT> SelectedSwap;
      static SelectedSwap createImplSwap(vector_value_type& v, size_type index)
      { return SelectedSwap(reinterpret_cast<unsigned char*>(&v[index]), 0); } 
  };

  template <>
  class ImplSelector<bool>
  {
    public:
      typedef bool value_type;
      typedef scml_memory_operations_podt_common<bool>::vector_value_type vector_value_type;
      typedef unsigned long long size_type;
          
      typedef Normal<bool> Selected;
      static Selected createImpl(vector_value_type& v, size_type index) { return Selected(v, index); } 
      typedef Normal<bool> SelectedSwap;
      static SelectedSwap createImplSwap(vector_value_type& v, size_type index) { return SelectedSwap(v, index); } 
  };

  template <int N>
  class ImplSelector<sc_dt::sc_biguint<N> >
  {
    public:
      typedef sc_dt::sc_biguint<N> value_type;
      typedef typename scml_memory_operations_podt_common<sc_dt::sc_biguint<N> >::vector_value_type vector_value_type;
      typedef unsigned long long size_type;
          
      typedef Normal<sc_dt::sc_biguint<N> > Selected;
      static Selected createImpl(vector_value_type& v, size_type index) { return Selected(v, index); } 
      typedef Normal<sc_dt::sc_biguint<N> > SelectedSwap;
      static SelectedSwap createImplSwap(vector_value_type& v, size_type index) { return SelectedSwap(v, index); } 
  };
  
  
  
  template<typename I>
      class NotWatching
  {
    public:
      typedef typename I::value_type  value_type;
      typedef unsigned long long size_type;
    public:
      NotWatching(I impl) : mImpl(impl) {}
      ~NotWatching() { }
      
      value_type getData(size_type index=0) const 
      {
        return mImpl.getData(index);
      }
      
      value_type getDataDebug(size_type index=0) const 
      {
        return mImpl.getData(index);
      }
      
      void setData(value_type value, size_type index=0)
      {
        mImpl.setData(value, index);
      }
    
      void setDataDebug(value_type value, size_type index=0)
      {
        mImpl.setData(value, index);
      }
      
    private:
      I mImpl;
  };
  
  
  // Helper functions
  template <typename I>
  scml_memory_operations_impl_base<typename I::value_type>* create_scml_memory_operations_impl(const I& i)
  {
    return new scml_memory_operations_impl<typename I::value_type, I>(i); 
  }
  
  
  template <typename I, typename T>
  NotWatching<I>  create_NotWatching(T&, const I& i)
  {
    return NotWatching<I>(i); 
  }
}

using namespace scml_memory_operations_impl_helpers;

template<typename DT, typename I>
class scml_memory_operations_impl : public scml_memory_operations_impl_base<DT>
{
  public:
    typedef DT value_type;
    typedef unsigned long long size_type;
    
  public:
    scml_memory_operations_impl(I data) : mData(data) {}
    virtual ~scml_memory_operations_impl() {}
    
    virtual value_type getValue() const
    {
      return mData.getData();
    }
    
    virtual void setValue(const value_type rhs)
    {
      mData.setData(rhs);
    }

    virtual value_type getValueDebug(size_type index, unsigned int offset, unsigned int acSize) const
    {
      value_type v = mData.getDataDebug(index);
      return scml_memory_utils::extractBits(v, offset, acSize);
    }
    
    virtual value_type getValueDebug(size_type index=0) const
    {
      return mData.getDataDebug(index);
    }

    virtual void setValueDebug(const value_type rhs, size_type index, unsigned int offset, unsigned int acSize)
    {
      value_type v = mData.getDataDebug(index);
      mData.setDataDebug(scml_memory_utils::insertBits(rhs, v, offset, acSize), index);
    }
        
    virtual void setValueDebug(const value_type rhs, size_type index=0)
    {
      mData.setDataDebug(rhs, index);
    }
    
    virtual value_type getValue(size_type index) const
    {
      return mData.getData(index);
    }
    
    virtual void setValue(const value_type rhs, size_type index)
    {
      mData.setData(rhs, index);
    }
    
    
    virtual value_type getBits(size_type index, unsigned int offset, unsigned int acSize) const
    {
      value_type v = mData.getData(index);
      return scml_memory_utils::extractBits(v, offset, acSize);
    }
    
    virtual void setBits(const value_type rhs, size_type index, unsigned int offset, unsigned int acSize)
    {
      value_type v = mData.getDataDebug(index);
      mData.setData(scml_memory_utils::insertBits(rhs, v, offset, acSize), index);
    }
    
    virtual void doMultiply(const value_type rhs)
    {
      mData.setData(mData.getData() * rhs);
    }
    
    virtual void doDivide(const value_type rhs)
    {
      mData.setData(mData.getData() / rhs);
    }
    
    virtual void doAdd(const value_type rhs)
    {
      mData.setData(mData.getData() + rhs);
    }
    
    virtual void doSubtract(const value_type rhs)
    {
      mData.setData(mData.getData() - rhs);
    }
    
    virtual void doModulo(const value_type rhs)
    {
      mData.setData(mData.getData() % rhs);
    }
    
    virtual void doAnd(const value_type rhs)
    {
      mData.setData(mData.getData() & rhs);
    }
    
    virtual void doOr(const value_type rhs)
    {
      mData.setData(mData.getData() | rhs);
    }
    
    virtual void doXor(const value_type rhs)
    {
      mData.setData(mData.getData() ^ rhs);
    }
    
    virtual void doShiftLeft(const value_type rhs)
    {
      mData.setData(mData.getData() << rhs);
    }
    
    virtual void doShiftRight(const value_type rhs)
    {
      mData.setData(mData.getData() >> rhs);
    }
    
    virtual value_type doPostIncrement()
    {
      value_type v = mData.getData();
      mData.setData(scml_memory_utils::do_inc(v));
      return v;
    }

    virtual value_type doPostDecrement()
    {
      value_type v = mData.getData();
      mData.setData(scml_memory_utils::do_dec(v));
      return v;
    }
    
    virtual void doPreIncrement()
    {
      mData.setData(scml_memory_utils::do_inc(mData.getData()));
    }
    
    virtual void doPreDecrement()
    {
      mData.setData(scml_memory_utils::do_dec(mData.getData()));
    }    

  private:
    I mData;
};


/************************************************************************
 * INLINE IMPLEMENTATIONS
 */

template< typename DT >
scml_memory_operations_podt_common< DT >::~scml_memory_operations_podt_common()
{
  cleanUp();
}

template< typename DT >
void
scml_memory_operations_podt_common<DT>::updateFastAccess()
{
  delete mFastAccess;
  mFastAccess = 0;

  // First, try to get a backdoor pointer
  if(mSharedData->spm != 0) {
    if(mSharedData->mHasHostEndianness) {
        mFastAccess = create_scml_memory_operations_impl(
                        create_NotWatching(*this, ImplSelector<value_type>::createImpl(*mSharedData->spm, memOffset)));
    } else {
        mFastAccess = create_scml_memory_operations_impl(
                        create_NotWatching(*this, ImplSelector<value_type>::createImplSwap(*mSharedData->spm, memOffset)));
    }
  } else {
    SCML2_LOG(mSharedData->mError) << "No storage found for scml_memory " << getName() << std::endl;
  }

}

template< typename DT >
void
scml_memory_operations_podt_common<DT>::propagateUpdateFastAccess()
{
  updateFastAccess();

  typename vector_alias_pointer_type::iterator it = aliases.begin();
  typename vector_alias_pointer_type::iterator end = aliases.end(); 
  for( ; it != end ; ++it) {
    (*it)->propagateUpdateFastAccess();
  }  
}


template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
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
scml_memory_operations_podt_common< DT >::
setPVInterfaceType(PVInterfaceType pvInterfaceType)
{
  if (pvInterfaceType == PV_INTERFACE_UNKNOWN) {
    return;
  }

  if (!checkPVInterfaceType(pvInterfaceType)) {
    SCML2_LOG(mSharedData->mError)
      << "It is not possible to mix different types"
      << " of transport callbacks. The registered callback must be of the"
      << " same kind as the PV port to which the scml_memory is bound."
      << std::endl;
  }
  mSharedData->mPVInterfaceType = pvInterfaceType;
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::PVInterfaceType
scml_memory_operations_podt_common< DT >::
getPVInterfaceType() const
{
  return mSharedData->mPVInterfaceType;
}

template< typename DT >
template< typename REQ >
void
scml_memory_operations_podt_common< DT >::
checkBurstAccess(const REQ& req) const
{
  if (req.getBurstCount() > 1) {
    // Only pvIncr is supported
    if (req.getBurstType() != pvIncr) {
      SCML2_LOG(mSharedData->mError)
        << "Illegal burstType, only pvIncr is supported!" << std::endl;
    }

    // Access size must be equal to the size of the underlying memory
    if (req.getDataSize() != sizeOf<DT>() * 8) {
      SCML2_LOG(mSharedData->mError)
        << "Illegal access size. For burst accesses, "
        << "the access size must be equal to the data size of the underlying memory!"
        << std::endl;
    }
  }
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::
checkRange(size_type index, unsigned int burstCount) const
{
  const size_type lastIndex = (burstCount ? (index + burstCount - 1) : index);
  if (lastIndex >= size() || lastIndex < index) {
    SCML2_LOG(mSharedData->mError)
      << "Access out of range @ " << sc_time_stamp() << "\n"
      << " - memory size: " << size() << "\n"
      << " - access: index = " << index << ", burstCount = " << burstCount << "\n"
      << "The error may be caused because the size of the scml_memory is bigger than the size specified in the 'mem_map' file for this target location."
      << std::endl;
  }
}

/************************************************************************
 * Queries for callbacks
 */

template< typename DT >
typename scml_memory_operations_podt_common< DT >::CallBackType
scml_memory_operations_podt_common< DT >::getCallBackType() const
{
  if (!mModule) {
    return CB_TYPE_NONE;
  }

  if (mTransportCb) {
    return CB_TYPE_TRANSPORT;
  }

  if (mReadCb && mWriteCb) {
    return CB_TYPE_READWRITE;
  }

  if (mReadCb) {
    return CB_TYPE_READ;
  }

  if (mWriteCb) {
    return CB_TYPE_WRITE;
  }

  // Should not happen;
  assert(0);
  return CB_TYPE_NONE;
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
getTransportCallBackName(std::string& name) const
{
  if (getCallBackType() == CB_TYPE_TRANSPORT) {
    name = mTransportCallBackName;
    return true;
  }
  return false;
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
getReadCallBackName(std::string& name) const
{
  const CallBackType t = getCallBackType();
  if (t == CB_TYPE_READ || t == CB_TYPE_READWRITE) {
    name = mReadCallBackName;
    return true;
  }
  return false;
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
getWriteCallBackName(std::string& name) const
{
  const CallBackType t = getCallBackType();
  if (t == CB_TYPE_WRITE || t == CB_TYPE_READWRITE) {
    name = mWriteCallBackName;
    return true;
  }
  return false;
}

/************************************************************************
 * Shared Data
 */

template< typename DT >
scml_memory_operations_podt_common< DT >::
SharedData::SharedData(const std::string& toplevelName) :
  mError(toplevelName, scml2::logging::severity::error()),
  mWarning(toplevelName, scml2::logging::severity::warning()),
  spm(0),
  endianness(cwrLitend),
  mHasHostEndianness(scml_memory_utils::hasHostEndianness(endianness)),
  addressingMode(8),
  mPVInterfaceType(PV_INTERFACE_UNKNOWN)
{
}

template< typename DT >
scml_memory_operations_podt_common< DT >::
SharedData::~SharedData()
{
  delete spm;
}

/************************************************************************
 * constructors for forward migration
 * behaviour is do as value_type does
 */

template< typename DT >
scml_memory_operations_podt_common< DT >::
scml_memory_operations_podt_common() :
  scml_memory_base( scml_memory_base::defaultName()),
  mSharedData(new SharedData(getName())),
  memOffset( 0),
  memSize( 1),
  mFastAccess(0),
  mModule( 0),
  mTransportCb(0),
  mReadCb( 0), mWriteCb( 0),
  mBlockingRead( false ),
  mBlockingWrite( false ),
  mUserId( 0),
  parent( 0 ),
  bitfieldContainer( 0 ),
  mIsBoundToPort( false),
  mStoreAfterReadCall( true),
  mDefaultRespLatency( 0),
  mDefaultRespStatus( pvOk),
  mTriggerBehaviourOnDebugRead( false),
  mTriggerBehaviourOnDebugWrite( false),
  mToplevel(this),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{

  mSharedData->spm = new vector_value_type(1);

  updateFastAccess();
}

template< typename DT >
scml_memory_operations_podt_common< DT >::
scml_memory_operations_podt_common( value_type a ) :
  scml_memory_base( scml_memory_base::defaultName()),
  mSharedData(new SharedData(getName())),
  memOffset( 0),
  memSize( 1),
  mFastAccess(0),
  mModule( 0),
  mTransportCb(0),
  mReadCb( 0), mWriteCb( 0),
  mBlockingRead( false ),
  mBlockingWrite( false ),
  mUserId( 0),
  parent( 0 ),
  bitfieldContainer( 0 ),
  mIsBoundToPort( false),
  mStoreAfterReadCall( true),
  mDefaultRespLatency( 0),
  mDefaultRespStatus( pvOk),
  mTriggerBehaviourOnDebugRead( false),
  mTriggerBehaviourOnDebugWrite( false),
  mToplevel(this),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{

  mSharedData->spm = new vector_value_type(1, a);

  updateFastAccess();
  put( a);
}

/************************************************************************
 * named default
 */
template< typename DT >
scml_memory_operations_podt_common< DT >::
scml_memory_operations_podt_common( const char * n ) :
  scml_memory_base( n),
  mSharedData(new SharedData(getName())),
  memOffset( 0),
  memSize( 1),
  mFastAccess(0),
  mModule( 0),
  mTransportCb(0),
  mReadCb( 0), mWriteCb( 0),
  mBlockingRead( false ),
  mBlockingWrite( false ),
  mUserId( 0),
  parent( 0 ),
  bitfieldContainer( 0 ),
  mIsBoundToPort( false),
  mStoreAfterReadCall( true),
  mDefaultRespLatency( 0),
  mDefaultRespStatus( pvOk),
  mTriggerBehaviourOnDebugRead( false),
  mTriggerBehaviourOnDebugWrite( false),
  mToplevel(this),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{

  mSharedData->spm = new vector_value_type(1);

  updateFastAccess();
}

/************************************************************************
 * constructors for memory array
 */
template< typename DT >
scml_memory_operations_podt_common< DT >::
scml_memory_operations_podt_common( scml_memsize a ) :
  scml_memory_base( scml_memory_base::defaultName()),
  mSharedData(new SharedData(getName())),
  memOffset( 0),
  memSize( a),
  mFastAccess(0),
  mModule( 0),
  mTransportCb(0),
  mReadCb( 0), mWriteCb( 0),
  mBlockingRead( false ),
  mBlockingWrite( false ),
  mUserId( 0),
  parent( 0 ),
  bitfieldContainer( 0 ),
  mIsBoundToPort( false),
  mStoreAfterReadCall( true),
  mDefaultRespLatency( 0),
  mDefaultRespStatus( pvOk),
  mTriggerBehaviourOnDebugRead( false),
  mTriggerBehaviourOnDebugWrite( false),
  mToplevel(this),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{

  mSharedData->spm = new vector_value_type(a);

  updateFastAccess();
}

template< typename DT > 
scml_memory_operations_podt_common< DT >::
scml_memory_operations_podt_common( const char * n,
                                    scml_memsize a ) :
  scml_memory_base( n ),
  mSharedData(new SharedData(getName())),
  memOffset( 0),
  memSize( a),
  mFastAccess(0),
  mModule( 0),
  mTransportCb(0),
  mReadCb( 0), mWriteCb( 0),
  mBlockingRead( false ),
  mBlockingWrite( false ),
  mUserId( 0),
  parent( 0 ),
  bitfieldContainer( 0 ),
  mIsBoundToPort( false),
  mStoreAfterReadCall( true),
  mDefaultRespLatency( 0),
  mDefaultRespStatus( pvOk),
  mTriggerBehaviourOnDebugRead( false),
  mTriggerBehaviourOnDebugWrite( false),
  mToplevel(this),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{

  mSharedData->spm = new vector_value_type(a);

  updateFastAccess();
}

/************************************************************************
 * alias constructors
 */

template< typename DT >
scml_memory_operations_podt_common< DT >::
scml_memory_operations_podt_common( scml_memory_operations_podt_common & a, 
                                    size_type offset, size_type size ) :
  scml_memory_base( scml_memory_base::defaultName()),
  mSharedData(a.mSharedData),
  memOffset( a.memOffset + offset ),
  memSize( size ),
  mFastAccess(0),
  mModule( 0),
  mTransportCb(0),
  mReadCb( 0), mWriteCb( 0),
  mBlockingRead( false ),
  mBlockingWrite( false ),
  mUserId( 0),
  parent( & a ),
  bitfieldContainer( 0 ),
  mIsBoundToPort( false),
  mStoreAfterReadCall( true),
  mDefaultRespLatency( 0),
  mDefaultRespStatus( pvOk),
  mTriggerBehaviourOnDebugRead( false),
  mTriggerBehaviourOnDebugWrite( false),
  mToplevel(a.mToplevel),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{
  a.registerAsAlias( this );
  this->sanityCheckOnAliasRelations();

  updateFastAccess();
}

template< typename DT > 
scml_memory_operations_podt_common< DT >::
scml_memory_operations_podt_common( const char * n,
                                    scml_memory_operations_podt_common & a, 
                                    size_type offset, size_type size ) :
  scml_memory_base( n),
  mSharedData(a.mSharedData),
  memOffset( a.memOffset + offset ),
  memSize( size ),
  mFastAccess(0),
  mModule( 0),
  mTransportCb(0),
  mReadCb( 0), mWriteCb( 0),
  mBlockingRead( false ),
  mBlockingWrite( false ),
  mUserId( 0),
  parent( & a ),
  bitfieldContainer( 0 ),
  mIsBoundToPort( false),
  mStoreAfterReadCall( true),
  mDefaultRespLatency( 0),
  mDefaultRespStatus( pvOk),
  mTriggerBehaviourOnDebugRead( false),
  mTriggerBehaviourOnDebugWrite( false),
  mToplevel(a.mToplevel),
  mMapableIf(new scml_mapable_if_to_T<this_type>(*this))
{
  a.registerAsAlias( this );
  this->sanityCheckOnAliasRelations();

  updateFastAccess();
}

/************************************************************************
 * implicit conversion operator to scml_mapable_if
 */

template< typename DT>
scml_memory_operations_podt_common< DT >::
operator scml_mapable_if& ()
{
  return *mMapableIf;
}

template< typename DT>
scml_memory_operations_podt_common< DT >::
operator const scml_mapable_if& () const
{
  return *mMapableIf;
}

/************************************************************************
 * sanity check
 */
template< typename DT >
void
scml_memory_operations_podt_common< DT >::
sanityCheckOnAliasRelations() const
{
  const this_pointer_type parent( this->getParent()); 
  if( parent == NULL) {
    SCML2_LOG(mSharedData->mWarning)
      << "The memory " << this->getName() << " is an alias but has no parent."
      << ::std::endl;
    return;
  }
  if( parent == this) {
    SCML2_LOG(mSharedData->mError)
      << "The memory " << this->getName() << " is alias for itself."
      << ::std::endl;
  }
  if( this->size() > parent->size()) {
    SCML2_LOG(mSharedData->mWarning)
      << "The memory alias " << this->getName() << " is larger than its parent."
      << ::std::endl;
  }
  if(( this->offset() + this->size()) >
     ( parent->offset() + parent->size())) {
    SCML2_LOG(mSharedData->mWarning)
      << "The memory alias " << this->getName()
      << " addresses memory that is not in the parent."
      << ::std::endl;
  }
}

/************************************************************************
 * endianness
 *
 */
template< typename DT >
void 
scml_memory_operations_podt_common< DT >::
set_endianness( scml_endian a )
{ 
  cwrEnd endianness = scml_memory_utils::convert_scml_to_cwrEnd(a);
  if (endianness != mSharedData->endianness) {
    mSharedData->endianness = endianness;
    mSharedData->mHasHostEndianness = scml_memory_utils::hasHostEndianness(endianness);
    mToplevel->propagateUpdateFastAccess();
  }
}

template< typename DT >
scml_endian 
scml_memory_operations_podt_common< DT >::
get_endianness() const
{
  return scml_memory_utils::convert_cwrEnd_to_scml(mSharedData->endianness); 
}

/************************************************************************
 * addressing mode
 *
 */

template< typename DT >
unsigned int
scml_memory_operations_podt_common< DT >::get_addressing_mode() const 
{ 
  return mSharedData->addressingMode; 
}

template< typename DT >
void 
scml_memory_operations_podt_common< DT >::set_addressing_mode( unsigned int a )
{
  mSharedData->addressingMode = a;  
}

/************************************************************************
 * access
 * read and write
 */

template< typename DT >
template< typename IF >
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::readImp(size_type a,
                                                  unsigned int acSiz,
                                                  unsigned int offSet,
                                                  bool isDebug)
{
  assert(memOffset == 0);
  typename IF::request_type req;
  const uint64 address = indexToAddress(a);
  assert((address == convert<uint64, typename IF::address_type>(address)));
  req.setAddress(address);
  req.setWriteDataSource( 0);
  typename IF::data_type rData = 0;
  req.setReadDataDestination( &rData);
  req.setType( pvRead); 
  req.setDataSize( acSiz);   
  req.setOffset( offSet);
  req.setBurstCount( 1);
  req.setBurstType( pvIncr);
  req.setThreadID( 0);
  req.setMode(isDebug ? pvDebug : pvDefault);

  transportProp<IF>( req );
  return convert<typename IF::data_type, value_type>(rData);
}

template< typename DT >
template< typename IF >
void
scml_memory_operations_podt_common< DT >::writeImp(value_type v,
                                                   size_type a,
                                                   unsigned int acSiz,
                                                   unsigned int offSet,
                                                   bool isDebug)
{
  assert(memOffset == 0);
  typename IF::request_type req;
  const uint64 address = indexToAddress(a);
  assert((address == convert<uint64, typename IF::address_type>(address)));
  req.setAddress(address);
  typename IF::data_type wData = convert<value_type, typename IF::data_type>(v);
  req.setWriteDataSource( &wData);
  req.setReadDataDestination( 0);
  req.setType( pvWrite); 
  req.setDataSize( acSiz);   
  req.setOffset( offSet);    
  req.setBurstCount( 1);
  req.setBurstType( pvIncr);
  req.setThreadID( 0);
  req.setMode(isDebug ? pvDebug : pvDefault);

  transportProp<IF>( req );
  return;
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::readProp(size_type a,
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
scml_memory_operations_podt_common< DT >::writeProp(value_type v,
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
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::read(size_type a,
                                               unsigned int acSiz,
                                               unsigned int offSet)
{ 
  return mToplevel->readProp(a + memOffset, acSiz, offSet, false);
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::read( size_type a )
{ 
  const unsigned int acSiz( 8 * sizeOf<value_type>());
  return read(a, acSiz, 0);
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::readDebug( size_type a,
                                                     unsigned int acSiz,
                                                     unsigned int offSet)
{
  if(this->trigger_behaviour_on_debug_read()) {
    return mToplevel->readProp(a + memOffset, acSiz, offSet, true);

  } else {
    return this->getDebug( a, acSiz, offSet);
  }
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::readDebug( size_type a)
{
  const unsigned int acSiz( 8 * sizeOf<value_type>());
  return readDebug(a, acSiz, 0);
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::write(value_type v,
                                                size_type a,
                                                unsigned int acSiz,
                                                unsigned int offSet) 
{
  mToplevel->writeProp(v, a + memOffset, acSiz, offSet, false);
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::write( value_type v, size_type a ) 
{
  const unsigned int acSiz( 8 * sizeOf<value_type>());
  write(v, a, acSiz, 0);
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::writeDebug( value_type v,
						      size_type a,
                                                      unsigned int acSiz,
                                                      unsigned int offSet)
{
  if( this->trigger_behaviour_on_debug_write()) {
    mToplevel->writeProp(v, a + memOffset, acSiz, offSet, true);

  } else {
    this->putDebug( v, a, acSiz, offSet);
  }
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::writeDebug( value_type v,
						      size_type a)
{
  const unsigned int acSiz( 8 * sizeOf<value_type>());
  writeDebug(v, a, acSiz, 0);
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::
getDebug( size_type index,
	  unsigned int acSiz,
	  unsigned int offSet ) const
{
  return mFastAccess->getValueDebug(index, offSet, acSiz);
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::value_type
scml_memory_operations_podt_common< DT >::
getDebug( size_type a ) const
{
  return mFastAccess->getValueDebug(a);
}

template< typename DT > 
void
scml_memory_operations_podt_common< DT >::
putDebug( value_type v,
	  size_type index,
	  unsigned int acSiz,
	  unsigned int offSet ) 
{
  mFastAccess->setValueDebug(v, index, offSet, acSiz);
}

template< typename DT > 
void
scml_memory_operations_podt_common< DT >::
putDebug( value_type v, size_type a ) 
{
  mFastAccess->setValueDebug(v, a);
}

/************************************************************************
 * default setting for PV response
 */

template< typename DT >
unsigned int
scml_memory_operations_podt_common< DT >::get_default_response_latency() const
{
  return mDefaultRespLatency;
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::
set_default_response_latency( unsigned int l)
{
  mDefaultRespLatency = l;
  typename vector_alias_pointer_type::iterator it = aliases.begin();
  typename vector_alias_pointer_type::iterator end = aliases.end(); 
  for( ; it != end ; ++it) {
    (*it)->set_default_response_latency( l);
  }  
}

template< typename DT >
PVResponse
scml_memory_operations_podt_common< DT >::get_default_response_status() const
{
  return mDefaultRespStatus;
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::
set_default_response_status( PVResponse s)
{
  mDefaultRespStatus = s;
  typename vector_alias_pointer_type::iterator it = aliases.begin();
  typename vector_alias_pointer_type::iterator end = aliases.end(); 
  for( ; it != end ; ++it) {
    (*it)->set_default_response_status( s);
  }  
}

/************************************************************************
 * PV Transport virtual function
 * see tlm_if
 *
 * can only be called on orignal memory
 */

template< typename DT >
template< typename IF >
inline
typename IF::response_type
scml_memory_operations_podt_common< DT >::nonVirtualTransport(const typename IF::request_type& req) {
  if(isAliasImp()) {
    SCML2_LOG(mSharedData->mError)
      << "it is not allowed to call transport() on alias " << getName()
      << ::std::endl;
  }
  return transportProp<IF>(req);
}

#define DEFINE_TRANSPORT(IF) \
  template< typename DT > \
  IF::response_type \
  scml_memory_operations_podt_common<DT>::transport(const IF::request_type& req) { \
    return nonVirtualTransport<IF>(req); \
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
scml_memory_operations_podt_common< DT >::
transportProp( const typename IF::request_type & req) {
  const typename IF::address_type globalAddress( req.getAddress());
  const size_type globalIndexLo( addressToIndex( globalAddress ));
  const unsigned int burstCount( req.getBurstCount());
  const unsigned int dataSize( req.getDataSize());
  const unsigned int burstBytes( burstCount * (dataSize / 8));
  const unsigned int remainder( burstBytes % sizeOf<value_type>());
  const unsigned int burstIndices( burstBytes / sizeOf<value_type>()
                                   + ((0 != remainder) ? 1 : 0));
  const size_type globalIndexHi( globalIndexLo + (burstIndices - 1));
  const bool isRead(req.getType() == pvRead);

  this_pointer_type self = this;
  this_pointer_type server = findAliasForIndex( globalIndexLo, globalIndexHi );
  while (self != server) {
    self = server;
    server = server->findAliasForIndex( globalIndexLo, globalIndexHi );
  }

  this_pointer_type p = (isRead ? self->findAncestorWithReadBehaviour() :
                                  self->findAncestorWithWriteBehaviour());
  if( 0 == p) {
    p = self;
  }
  if ( burstCount > 1) {
    const bool hasRefinedBehaviour =
      (isRead ? p->hasRefinedReadBehaviourForIndex(globalIndexLo, globalIndexHi) :
                p->hasRefinedWriteBehaviourForIndex(globalIndexLo, globalIndexHi));
    if (hasRefinedBehaviour) {
      return p->template burstUnrollingTransportImp<IF>( req);
    }
  }

  scml_memory_user& user (scml_memory_user::instance());

  user.set_last_top_level_address( req.getAddress());
  user.set_debug_access( pvDebug == req.getMode());
  req.m_address -= indexToAddress( p->memOffset);
  typename IF::response_type resp = p->template transportImp<IF>( req );
  user.set_debug_access(false);
  return resp;
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
scml_memory_operations_podt_common< DT >::
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
    ++writeDataSource;
    unrolreq.setReadDataDestination( readDataDestination);
    ++readDataDestination;
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
template< typename IF >
void
scml_memory_operations_podt_common< DT >::
writeBitfield(const typename IF::data_type& writeData,
              unsigned int dataSize,
              unsigned int offSet)
{
  const value_type bitfieldData(convert<typename IF::data_type, value_type>(writeData));
  const value_type mask(bitfieldContainer->write(bitfieldData, dataSize, offSet));

  const value_type data(convert<typename IF::data_type, value_type>(writeData));
  const value_type dataMask( scml_memory_utils::getBitsMask<value_type>(dataSize));
  const value_type alignData((data & dataMask) << offSet);
  const value_type inverseDataMask( ~(dataMask << offSet));
  const value_type original( inverseDataMask & getDebug());
  const value_type dataInOriginal( alignData | original);

  const value_type updated(mask & getDebug());
  put( updated | (dataInOriginal & (~mask)));
}

template< typename DT >
template< typename IF >
typename IF::response_type
scml_memory_operations_podt_common< DT >::
transportImp( const typename IF::request_type & req) {
  assert(checkPVInterfaceType((PVInterfaceType)scml::If2PVInterfaceType<IF>::result));

  scml_memory_user& user (scml_memory_user::instance());

  user.set_last_user_id( mUserId);
  user.set_last_memory_pointer( this);
  const typename IF::address_type address( req.getAddress());
  const PVType reqType( req.getType());
  const PVMode reqMode( req.getMode());
  const unsigned int dataSize( req.getDataSize());
  const unsigned int burstCount( req.getBurstCount());
  const unsigned int reqOffSet( req.getOffset());
  unsigned int offSet( 0);
  const size_type index( addressToIndex( address, dataSize, offSet));
  const bool haveBitfields( hasBitfields());
  const bool haveBitfieldsWithCallbacks( haveBitfields
                                         ? bitfieldContainer->hasCallbacks()
                                         : false);
  typename IF::response_type resp( req.obtainResp());
  resp.setLatency( this->get_default_response_latency());
  resp.setResponse( this->get_default_response_status());
  
  if( 0 == offSet) {
    offSet = reqOffSet;
  } else if( 0 != reqOffSet) {
    resp.setResponse( pvError );
    return resp;   
  }

  if ((dataSize & (dataSize - 1)) || // datasize must be power of 2
      dataSize < 8 || dataSize > sizeOf<typename IF::data_type>() * 8) {
    // only valid dataSizes are: 8, 16, 32,... up to sizeof(data_type)
    resp.setResponse( pvError );
    return resp;   
  }

  if( 0 != (offSet % dataSize) || (offSet >= (sizeOf<value_type>() * 8))) {
    resp.setResponse( pvError );
    return resp;   
  }
  if( pvWrite == reqType) {
    if( pvDebug != reqMode || trigger_behaviour_on_debug_write()) {
      if ( !is_writing_allowed()) {
        if( signal_error_on_disallowed_write()) {
          resp.setResponse( pvError );
        }
        return resp;   
      }
      if (mBlockingWrite && (reqMode != pvDebug)) {
        // TLM2 target adaptor does not sync
        //  --> sync before executing blocking callback
        SCML_SYNC_ON_DEMAND();
      }
      if( haveBitfieldsWithCallbacks) {
        writeBitfield<IF>(req.getWriteData(), dataSize, offSet);
        resp.setLatency( this->get_default_response_latency());
        resp.setResponse( this->get_default_response_status());
        return resp;
      }
      if( hasRegisteredTransportCallBack()) {
        assert(mTransportCb);
	return mTransportCb->transport(req);
      }
      if( dataSize > (8 * sizeOf<value_type>())) {
        resp.setResponse( pvError );
        return resp;
      }
      checkBurstAccess(req);
      if( hasRegisteredWriteCallBack()) {
	  (mModule->*mWriteCb) ( convert<typename IF::data_type, value_type>(req.getWriteData( 0)), dataSize, offSet);
        resp.setLatency( this->get_default_response_latency());
        resp.setResponse( this->get_default_response_status());
        return resp;
      }
      if( haveBitfields) { // without call back functions
        writeBitfield<IF>(req.getWriteData(), dataSize, offSet);
        return resp;
      }
    }
    if ((index + burstCount - 1) > size()) {
      SCML2_LOG(mSharedData->mError) << "Access out of range on " << getName() << std::endl;
    }
    for(unsigned int i = 0; i < burstCount; ++i) { 
      put( convert<typename IF::data_type, value_type>(req.getWriteData(i)), index + i, dataSize, offSet);
    }
  } else if( pvRead == reqType) {
    if( pvDebug != reqMode || trigger_behaviour_on_debug_read()) {
      if( !is_reading_allowed()) {
        if( signal_error_on_disallowed_read()) {
          resp.setResponse( pvError );
        }
        resp.setReadData(0);
        return resp;   
      }
      if (mBlockingRead && (reqMode != pvDebug)) {
        // TLM2 target adaptor does not sync
        //  --> sync before executing blocking callback
        SCML_SYNC_ON_DEMAND();
      }
      if( haveBitfieldsWithCallbacks) {
        bitfieldContainer->template read<value_type>( dataSize, offSet);
        resp.setReadData( convert<value_type, typename IF::data_type>(get(index, dataSize, offSet)));
        resp.setLatency( this->get_default_response_latency());
        resp.setResponse( this->get_default_response_status());
        return resp;
      }
      if( hasRegisteredTransportCallBack()) {
	  assert(mTransportCb);
	  typename IF::response_type readResp;
	  readResp = mTransportCb->transport(req);

        if( store_after_read_call()) {
          for( size_t i( 0); i < burstCount; ++i) { 
            put( convert<typename IF::data_type, value_type>(readResp.getReadData( i )), index + i, dataSize, offSet);
          }
        }
        return readResp;
      }
      if( dataSize > (8 * sizeOf<value_type>())) {
        resp.setResponse( pvError );
        return resp;
      }
      checkBurstAccess(req);
      if( hasRegisteredReadCallBack()) {
	  value_type val;
	  val = (mModule->*mReadCb)(dataSize, offSet);      

        const typename IF::data_type readData = convert<value_type, typename IF::data_type>(val);
        if( store_after_read_call()) {
          put( val, index, dataSize, offSet );
        }
        resp.setReadData( readData);
        resp.setLatency( this->get_default_response_latency());
        resp.setResponse( this->get_default_response_status());
        return resp;
      }
      if( haveBitfields) { // without call back functions
        bitfieldContainer->template read<value_type>( dataSize, offSet);
        resp.setReadData( convert<value_type, typename IF::data_type>(get(index, dataSize, offSet)));
        return resp;
      }
    }
    if ((index + burstCount - 1) > size()) {
      SCML2_LOG(mSharedData->mError) << "Access out of range on " << getName() << std::endl;
    }
    for(unsigned int i = 0; i < burstCount; ++i) {
      const typename IF::data_type readData =
        convert<value_type, typename IF::data_type>(get(index + i, dataSize, offSet));
      resp.setReadData(readData, i);
    }
  } else {
    SCML2_LOG(mSharedData->mWarning) << "Invalid PV access type on " << getName() << ::std::endl;    
    resp.setResponse( pvError );
  }
  return resp;
}

/************************************************************************
 * PV Transport function helper
 * find alias for index
 */
template< typename DT >
typename scml_memory_operations_podt_common< DT >::this_pointer_type 
scml_memory_operations_podt_common< DT >::findAliasForIndex( size_type indexLo,
                                                             size_type indexHi ) 
{
  typename vector_alias_pointer_type::iterator it = aliases.begin();
  typename vector_alias_pointer_type::iterator end = aliases.end(); 
  for( ; it != end ; ++it) {
    this_pointer_type alias( *it);
    const size_type low( alias->memOffset); 
    if( low <= indexLo ) {
      const size_type up( low + alias->memSize);
      if( indexHi < up ) {
        return alias;
      }
    }
  }

  return this;
}

/************************************************************************
 * PV Transport function helper
 * starting from this check whether aliases with call backs exist
 */
template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
hasRefinedReadBehaviourForIndex( size_type indexLo,
                                 size_type indexHi )
{
  typename vector_alias_pointer_type::iterator it = aliases.begin();
  typename vector_alias_pointer_type::iterator end = aliases.end(); 
  for( ; it != end ; ++it) {
    this_pointer_type alias( *it);
    const size_type low( alias->memOffset); 
    const size_type up( low + alias->memSize);
    if(( indexHi < low) || (indexLo >= up)) {
      // do nothing
    } else if (hasReadBehaviourAttached() ||
               alias->hasRefinedReadBehaviourForIndex( indexLo, indexHi)) {
      return true;
    }
  }
  return false;
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
hasRefinedWriteBehaviourForIndex( size_type indexLo,
                                  size_type indexHi )
{
  typename vector_alias_pointer_type::iterator it = aliases.begin();
  typename vector_alias_pointer_type::iterator end = aliases.end(); 
  for( ; it != end ; ++it) {
    this_pointer_type alias( *it);
    const size_type low( alias->memOffset); 
    const size_type up( low + alias->memSize);
    if(( indexHi < low) || (indexLo >= up)) {
      // do nothing
    } else if (hasWriteBehaviourAttached() ||
               alias->hasRefinedWriteBehaviourForIndex( indexLo, indexHi)) {
      return true;
    }
  }
  return false;
}

/************************************************************************
 * PV Transport function helper
 * starting from this find the ancestor that has a behavioral call back attached
 */
template< typename DT >
typename scml_memory_operations_podt_common< DT >::this_pointer_type 
scml_memory_operations_podt_common< DT >::findAncestorWithReadBehaviour()
{
  const_this_pointer_type p = this;
  return const_cast<this_pointer_type>(p->findAncestorWithReadBehaviour());
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::const_this_pointer_type 
scml_memory_operations_podt_common< DT >::findAncestorWithReadBehaviour() const
{
  const_this_pointer_type p = this;
  while( 0 != p) {
    if(p->hasReadBehaviourAttached()) {
      return p;
    }
    p = p->getParent();    
  }
  return p;
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::this_pointer_type 
scml_memory_operations_podt_common< DT >::findAncestorWithWriteBehaviour()
{
  const_this_pointer_type p = this;
  return const_cast<this_pointer_type>(p->findAncestorWithWriteBehaviour());
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::const_this_pointer_type 
scml_memory_operations_podt_common< DT >::findAncestorWithWriteBehaviour() const
{
  const_this_pointer_type p = this;
  while( 0 != p) {
    if(p->hasWriteBehaviourAttached()) {
      return p;
    }
    p = p->getParent();    
  }
  return p;
}


/************************************************************************
 * support for bit fields
 */

template< typename DT >
bool
scml_memory_operations_podt_common< DT >:: 
registerBitfields( scml_bitfield_container_entry b )
{
  if( this->size() == 1) { 
    if( 0 == bitfieldContainer ) {
      bitfieldContainer = new scml_bitfield_container();
    }
    if (bitfieldContainer->findBitfield(b->getName())) {
      SCML2_LOG(mSharedData->mWarning)
        << "The memory " << this->getName()
        << " has bitfields with duplicate names: " << b->getName()
        << std::endl;
    }
    scml_bitfield_container_entry overlap = bitfieldContainer->findOverlap(b);
    if (overlap) {
      SCML2_LOG(mSharedData->mWarning)
        << "The memory " << this->getName()
        << " has overlapping bitfields: " << b->getName()
        << " and " << overlap->getName()
        << std::endl;
    }
    bitfieldContainer->registerBitfields( b );    
  } else {
    SCML2_LOG(mSharedData->mError) << "Bit fields can only be attached to size 1 memories." << ::std::endl;
    return false;
  }
  return true;
}

template< typename DT >
scml_bitfield_container_if::value_type
scml_memory_operations_podt_common< DT >::getBitfieldValue( unsigned int offset,
                                                            unsigned int size) 
{
  // Max size of bitfields is 32bit
  assert(size <= 32);
  const value_type d( get());  
  return convert<value_type, scml_bitfield_container_if::value_type>(d >> offset) &
         scml_memory_utils::getBitsMask<scml_bitfield_container_if::value_type>(size);
}

template< typename DT > 
void
scml_memory_operations_podt_common< DT >::
setBitfieldValue( scml_bitfield_container_if::value_type a, 
                  unsigned int offset,
                  unsigned int size) {
  // Max size of bitfields is 32bit
  assert(size <= 32);
  const value_type data =
    convert<scml_bitfield_container_if::value_type, value_type>(a);
  const value_type mask = scml_memory_utils::getBitsMask<value_type>(size);
  const value_type andMask( ~(mask << offset));
  const value_type orMask((data & mask) << offset);
  const value_type d( get());
  const value_type newD((d & andMask) | orMask);
  put( newD);
}


/************************************************************************
 * PRIVATE HELPER FUNCTIONS
 */

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::isValidIndex( size_type i) const
{ 
  return (i < this->size());
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::registerAsAlias( this_pointer_type a )
{ 
  aliases.push_back( a );
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::isAliasImp() const
{ 
  return (0 != this->parent); 
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::hasBitfields() const
{ 
  return (0 != this->bitfieldContainer); 
} 

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
updateReadBlockingProperty( bool isBlocking ) 
{
  return( this->mBlockingRead = (this->mBlockingRead || isBlocking));
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
updateWriteBlockingProperty( bool isBlocking ) 
{
  return (this->mBlockingWrite = (this->mBlockingWrite || isBlocking));
}

template< typename DT >
bool 
scml_memory_operations_podt_common< DT >::hasBehaviourAttached() const
{ 
  if( this->hasRegisteredCallBack() ||
      !this->is_reading_allowed() || !this->is_writing_allowed() ) {
    return true;
  } else if( this->hasBitfields()) {
    return this->bitfieldContainer->hasBehaviourAttached();
  }
  return false;
}

template< typename DT >
bool 
scml_memory_operations_podt_common< DT >::hasReadBehaviourAttached() const
{ 
  if( this->hasRegisteredCallBackForRead() || !this->is_reading_allowed()) {
    return true;
  } else if( this->hasBitfields()) {
    return this->bitfieldContainer->hasReadBehaviourAttached();
  }
  return false;
}

template< typename DT >
bool 
scml_memory_operations_podt_common< DT >::hasWriteBehaviourAttached() const
{ 
  if( this->hasRegisteredCallBackForWrite() || !this->is_writing_allowed()) {
    return true;
  } else if( this->hasBitfields()) {
    return this->bitfieldContainer->hasWriteBehaviourAttached();
  }
  return false;
}

template< typename DT >
bool 
scml_memory_operations_podt_common< DT >::hasRegisteredCallBack() const
{  
  return( this->hasRegisteredTransportCallBack()
          || this->hasRegisteredReadCallBack()
          || this->hasRegisteredWriteCallBack());
}

template< typename DT >
bool 
scml_memory_operations_podt_common< DT >::hasRegisteredCallBackForRead() const
{  
  return( this->hasRegisteredTransportCallBack()
          || this->hasRegisteredReadCallBack());
}

template< typename DT >
bool 
scml_memory_operations_podt_common< DT >::hasRegisteredCallBackForWrite() const
{  
  return( this->hasRegisteredTransportCallBack()
          || this->hasRegisteredWriteCallBack());
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::hasRegisteredReadCallBack() const
{  
  return (( 0 != this->mModule) && (0 != this->mReadCb));
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::hasRegisteredWriteCallBack() const
{  
  return (( 0 != this->mModule) && (0 != this->mWriteCb));
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::hasRegisteredTransportCallBack() const
{  
  return (( 0 != this->mModule) && (0 != this->mTransportCb));
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::release_storage()
{
  if( this->isAliasImp()) {
    // NOP
  } else {
      if( 0 == mSharedData->spm ) {
      } else {
        delete mSharedData->spm;
        mSharedData->spm = 0;
        return true;
      }
  }
  mSharedData->spm = 0;
  return false;
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::cleanUp()
{
  if( this->isAliasImp()) {
    // NOP
  } else {
    delete this->mSharedData;
  }
  delete this->bitfieldContainer;
  delete mFastAccess;
  delete mMapableIf;
}

template< typename DT > 
typename scml_memory_operations_podt_common< DT >::size_type
scml_memory_operations_podt_common< DT >::
addressToIndex( uint64 a,
                unsigned int accessSize,
                unsigned int & offSet) const 
{
  const unsigned int byteAddressingMode( get_addressing_mode() >> 3);
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
typename scml_memory_operations_podt_common< DT >::size_type
scml_memory_operations_podt_common< DT >::
addressToIndex( uint64 a) const 
{
  unsigned int offSet;
  const unsigned int accSize( sizeOf<DT>() << 3);
  return addressToIndex( a, accSize, offSet);
}

template< typename DT > 
typename scml_memory_operations_podt_common< DT >::uint64
scml_memory_operations_podt_common< DT >::
indexToAddress( size_type i ) const {
  const unsigned int byteAddressingMode( get_addressing_mode() >> 3);
  const unsigned int size( sizeOf<value_type>());
  const uint64 byteAddress( i * size);
  return (byteAddress / byteAddressingMode);
}

template< typename DT > 
typename scml_memory_operations_podt_common< DT >::uint64
scml_memory_operations_podt_common< DT >::
indexToByteAddress( size_type i ) const
{
  const unsigned int accSize( sizeOf<DT>() << 3);
  return indexToByteAddress( i, accSize, 0);
}


// see sc_interface

template< typename DT >
void
scml_memory_operations_podt_common< DT >::
register_port( sc_port_base &, const char* if_typename_ )
{
  if (isAlias()) {
    SCML2_LOG(mSharedData->mError)
      << "Aliases (" << getName() << ") can not be bound"
      << " to a PV port, only toplevel scml_memories can do that."
      << std::endl;
  }

  mIsBoundToPort = true;

  const PVInterfaceType pvInterfaceType = determinePVInterfaceType(if_typename_);
  setPVInterfaceType(pvInterfaceType);

}

template< typename DT >
void 
scml_memory_operations_podt_common< DT >::
unregisterCB()
{
  if (!mReadCb && !mWriteCb && !mTransportCb) {
    return;
  }

  mModule = 0;
  delete mTransportCb;
  mTransportCb = 0;
  mReadCb = 0;
  mWriteCb = 0;
  mBlockingRead = false;
  mBlockingWrite = false;
}

template< typename DT >
void 
scml_memory_operations_podt_common< DT >::
unregisterReadCB()
{
  if (!mReadCb) {
    return;
  }

  mReadCb = 0;
  mBlockingRead = false;

  if (!mWriteCb) {
    mModule = 0;
  }

}

template< typename DT >
void 
scml_memory_operations_podt_common< DT >::
unregisterWriteCB()
{
  if (!mWriteCb) {
    return;
  }

  mWriteCb = 0;
  mBlockingWrite = false;

  if (!mReadCb) {
    mModule = 0;
  }

}

/************************************************************************
 * initialize
 */

template< typename DT >
void
scml_memory_operations_podt_common< DT >::
initialize( value_type a )
{
  if (size()) {
    const size_type lastIndex = size() - 1;
    size_type index = 0;
    
    while (index < lastIndex) {
      putDebug(a, index);
      ++index;
    }
    putDebug(a, lastIndex);
  }
}

/************************************************************************
 * queries
 */

template< typename DT >
typename scml_memory_operations_podt_common< DT >::size_type
scml_memory_operations_podt_common< DT >::getSize() const 
{ 
  return this->size();
}

template< typename DT >
scml_memory_base::TypeID
scml_memory_operations_podt_common< DT >::getType() const 
{ 
  return MEM_TYPE_UNKNOWN;
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::isWriteable() const 
{ 
  return true; 
}


template< typename DT >
const char * 
scml_memory_operations_podt_common< DT >::getDocumentation() const 
{ 
  return "Unknown Memory";
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::isBoundToPort() const
{
  return this->mIsBoundToPort;
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::isAlias() const
{ 
  return this->isAliasImp();
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::size_type 
scml_memory_operations_podt_common< DT >::getTotalOffset() const 
{ 
  return this->offset();
}

template< typename DT >
typename scml_memory_operations_podt_common< DT >::this_pointer_type
scml_memory_operations_podt_common< DT >::getParent() const
{ 
  return this->parent;
}

/************************************************************************
 * additional queries on memories
 */
template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
hasReadCallBack() const 
{ 
  return this->hasRegisteredReadCallBack(); 
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
hasWriteCallBack() const 
{ 
  return this->hasRegisteredWriteCallBack(); 
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
hasTransportCallBack() const
{ 
  return this->hasRegisteredTransportCallBack();
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
hasBitfieldsAttached() const 
{
  return this->hasBitfields();
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
getBitfieldPointers( bitfield_pointer_container & v ) const
{
  if (this->hasBitfields()) {
    return this->bitfieldContainer->getBitfieldPointers( v );

  } else {
    return true;
  }
}

/************************************************************************
 * behaviour on debug
 */

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
trigger_behaviour_on_debug_read() const 
{ 
  return this->mTriggerBehaviourOnDebugRead; 
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::
set_trigger_behaviour_on_debug_read( bool b) 
{ 
  this->mTriggerBehaviourOnDebugRead = b; 
}

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::
trigger_behaviour_on_debug_write() const 
{ 
  return this->mTriggerBehaviourOnDebugWrite; 
}

template< typename DT >
void 
scml_memory_operations_podt_common< DT >::
set_trigger_behaviour_on_debug_write( bool b)
{ 
  this->mTriggerBehaviourOnDebugWrite = b; 
}

/************************************************************************
 * storage behaviour on read call back
 */

template< typename DT >
bool
scml_memory_operations_podt_common< DT >::store_after_read_call() const
{ 
  return this->mStoreAfterReadCall; 
}

template< typename DT >
void
scml_memory_operations_podt_common< DT >::set_store_after_read_call( bool  b)
{ 
  this->mStoreAfterReadCall = b; 
}

/************************************************************************
 * virtual getter setter for instrumentation
 *
 * see scml_memory_base.h
 */
template< typename DT >
scml_memory_base::ErrorCode
scml_memory_operations_podt_common< DT >::
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
    const value_type tmp = this->readDebug(i);
    for (unsigned int byte = 0; byte < sizeOf<DT>(); ++byte) {
      result.push_back(convert<DT, uint8>(tmp >> (byte * 8)));
    }
  }
  return scml_memory_base::noError;
}

template< typename DT >
scml_memory_base::ErrorCode
scml_memory_operations_podt_common< DT >::
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
  value_type tmp(0);
  for (unsigned int byte = 0; byte < sizeOf<DT>(); ++byte) {
    tmp |= (convert<uint8, DT>(result[byte]) << (byte * 8));
  }
  this->writeDebug(tmp, i);
  return scml_memory_base::noError;
}

template< typename DT >
unsigned int
scml_memory_operations_podt_common< DT >::
getAliasPointers(memory_pointer_container& v) const
{
  std::copy(aliases.begin(), aliases.end(), std::back_inserter(v));
  return aliases.size();
}

/************************************************************************
 * Explicit Instantiations
 */

template class scml_memory_operations_podt_common< bool >;
template class scml_memory_operations_podt_common< char >;
// template class scml_memory_operations_podt_common< float >;
// template class scml_memory_operations_podt_common< double >;
// template class scml_memory_operations_podt_common< long double >;

template class scml_memory_operations_podt_common< signed char >;
template class scml_memory_operations_podt_common< signed short int >;
template class scml_memory_operations_podt_common< signed int >;
template class scml_memory_operations_podt_common< signed long int >;
template class scml_memory_operations_podt_common< signed long long >;

template class scml_memory_operations_podt_common< unsigned char >;
template class scml_memory_operations_podt_common< unsigned short int >;
template class scml_memory_operations_podt_common< unsigned int >;
template class scml_memory_operations_podt_common< unsigned long int >;
template class scml_memory_operations_podt_common< unsigned long long >;

template class scml_memory_operations_podt_common< sc_dt::sc_biguint<128> >;
template class scml_memory_operations_podt_common< sc_dt::sc_biguint<256> >;
template class scml_memory_operations_podt_common< sc_dt::sc_biguint<512> >;
