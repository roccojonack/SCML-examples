/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_FAST_ACCESS_H
#define SCML2_MEMORY_FAST_ACCESS_H

#include <scml2/memory_fast_access_impl.h>
#include <scml2/memory_slow_access_base.h>

#include <tlm.h>
#include <cassert>

namespace scml2 {

template <typename DT>
class memory_fast_access
{
public:
  memory_fast_access();
  virtual ~memory_fast_access();

  virtual void update(memory_slow_access_base<DT>* slowAccess);

  unsigned char* get_fast_backdoor() const;

  void put(unsigned long long address,
           const unsigned char* data,
           unsigned int dataLength,
           const unsigned char* byteEnablePtr,
           unsigned int byteEnableLength,
           bool isDebug = false);
  void get(unsigned long long address,
           unsigned char* data,
           unsigned int dataLength,
           const unsigned char* byteEnablePtr,
           unsigned int byteEnableLength,
           bool isDebug = false) const;

  void put(unsigned long long index,
           const DT& data,
           unsigned int size,
           unsigned int offset,
           bool isDebug = false);
  void put(unsigned long long index,
           const DT& data,
           bool isDebug = false);
  DT get(unsigned long long index,
         unsigned int size,
         unsigned int offset,
         bool isDebug = false) const;
  DT get(unsigned long long index,
         bool isDebug = false) const;

  void transport(tlm::tlm_generic_payload& trans);
  void transport_debug(tlm::tlm_generic_payload& trans);

  void doAdd(unsigned long long index, const DT& rhs);
  void doSubtract(unsigned long long index, const DT& rhs);
  void doDivide(unsigned long long index, const DT& rhs);
  void doMultiply(unsigned long long index, const DT& rhs);
  void doModulo(unsigned long long index, const DT& rhs);
  void doXor(unsigned long long index, const DT& rhs);
  void doAnd(unsigned long long index, const DT& rhs);
  void doOr(unsigned long long index, const DT& rhs);
  void doShiftRight(unsigned long long index, const DT& rhs);
  void doShiftLeft(unsigned long long index, const DT& rhs);

  void doPreDecrement(unsigned long long index);
  DT doPostDecrement(unsigned long long index);
  void doPreIncrement(unsigned long long index);
  DT doPostIncrement(unsigned long long index);

private:
  memory_fast_access_impl<DT> mFastAccessImpl;
  memory_slow_access_base<DT>* mSlowAccess;
};

template <typename DT>
inline
memory_fast_access<DT>::
memory_fast_access() :
  mSlowAccess(0)
{
}

template <typename DT>
inline
memory_fast_access<DT>::
~memory_fast_access()
{
  if (mSlowAccess) {
    mSlowAccess->unref();
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
update(memory_slow_access_base<DT>* slowAccess)
{
  assert(slowAccess);
  if (mSlowAccess) {
    mSlowAccess->unref();
  }
  mSlowAccess = slowAccess;
  mSlowAccess->ref();
  mFastAccessImpl.set_fast_backdoor(mSlowAccess->get_fast_backdoor());
}

template <typename DT>
inline
unsigned char*
memory_fast_access<DT>::
get_fast_backdoor() const
{
  return mFastAccessImpl.get_fast_backdoor();
}

template <typename DT>
inline
void
memory_fast_access<DT>::
put(unsigned long long address,
    const unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength,
    bool isDebug)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.put(address, data, dataLength, byteEnablePtr, byteEnableLength, isDebug);

  } else {
    mSlowAccess->put(address,
                     data,
                     dataLength,
                     byteEnablePtr,
                     byteEnableLength,
                     isDebug);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
get(unsigned long long address,
    unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength,
    bool isDebug) const
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.get(address, data, dataLength, byteEnablePtr, byteEnableLength, isDebug);

  } else {
    mSlowAccess->get(address,
                     data,
                     dataLength,
                     byteEnablePtr,
                     byteEnableLength,
                     isDebug);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
put(unsigned long long index,
    const DT& data,
    unsigned int size,
    unsigned int offset,
    bool isDebug)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.put(index, data, size, offset, isDebug);

  } else {
    mSlowAccess->put(index, data, size, offset, isDebug);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
put(unsigned long long index,
    const DT& data,
    bool isDebug)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.put(index, data, isDebug);

  } else {
    mSlowAccess->put(index, data, isDebug);
  }
}

template <typename DT>
inline
DT
memory_fast_access<DT>::
get(unsigned long long index,
    unsigned int size,
    unsigned int offset,
    bool isDebug) const
{
  if (get_fast_backdoor()) {
    return mFastAccessImpl.get(index, size, offset, isDebug);

  } else {
    return mSlowAccess->get(index, size, offset, isDebug);
  }
}

template <typename DT>
inline
DT
memory_fast_access<DT>::
get(unsigned long long index,
    bool isDebug) const
{
  if (get_fast_backdoor()) {
    return mFastAccessImpl.get(index, isDebug);

  } else {
    return mSlowAccess->get(index, isDebug);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
transport(tlm::tlm_generic_payload& trans)
{
  if (trans.get_streaming_width() >= trans.get_data_length()) {
    if (trans.is_read()) {
      get(trans.get_address(),
          trans.get_data_ptr(),
          trans.get_data_length(),
          trans.get_byte_enable_ptr(),
          trans.get_byte_enable_length());

    } else {
      put(trans.get_address(),
          trans.get_data_ptr(),
          trans.get_data_length(),
          trans.get_byte_enable_ptr(),
          trans.get_byte_enable_length());
    }

  } else {
    if (trans.is_read()) {
      for (unsigned int i = 0; i < trans.get_data_length(); ++i) {
        if (!trans.get_byte_enable_ptr() ||
            trans.get_byte_enable_ptr()[i % trans.get_byte_enable_length()]) {
          get(trans.get_address() + i % trans.get_streaming_width(),
              trans.get_data_ptr() + i,
              1,
              0,
              0);
        }
      }

    } else {
      for (unsigned int i = 0; i < trans.get_data_length(); ++i) {
        if (!trans.get_byte_enable_ptr() ||
            trans.get_byte_enable_ptr()[i % trans.get_byte_enable_length()]) {
          put(trans.get_address() + i % trans.get_streaming_width(),
              trans.get_data_ptr() + i,
              1,
              0,
              0);
        }
      }
    }
  }
  trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

template <typename DT>
inline
void
memory_fast_access<DT>::
transport_debug(tlm::tlm_generic_payload& trans)
{
  if (trans.is_read()) {
    get(trans.get_address(),
        trans.get_data_ptr(),
        trans.get_data_length(),
        0,
        0,
        true);

  } else {
    put(trans.get_address(),
        trans.get_data_ptr(),
        trans.get_data_length(),
        0,
        0,
        true);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doAdd(unsigned long long index,
      const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doAdd(index, rhs);

  } else {
    mSlowAccess->doAdd(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doSubtract(unsigned long long index,
           const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doSubtract(index, rhs);

  } else {
    mSlowAccess->doSubtract(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doDivide(unsigned long long index,
         const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doDivide(index, rhs);

  } else {
    mSlowAccess->doDivide(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doMultiply(unsigned long long index,
           const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doMultiply(index, rhs);

  } else {
    mSlowAccess->doMultiply(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doModulo(unsigned long long index,
         const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doModulo(index, rhs);

  } else {
    mSlowAccess->doModulo(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doXor(unsigned long long index,
      const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doXor(index, rhs);

  } else {
    mSlowAccess->doXor(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doAnd(unsigned long long index,
      const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doAnd(index, rhs);

  } else {
    mSlowAccess->doAnd(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doOr(unsigned long long index,
     const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doOr(index, rhs);

  } else {
    mSlowAccess->doOr(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doShiftRight(unsigned long long index,
             const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doShiftRight(index, rhs);

  } else {
    mSlowAccess->doShiftRight(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doShiftLeft(unsigned long long index,
            const DT& rhs)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doShiftLeft(index, rhs);

  } else {
    mSlowAccess->doShiftLeft(index, rhs);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doPreDecrement(unsigned long long index)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doPreDecrement(index);

  } else {
    mSlowAccess->doPreDecrement(index);
  }
}

template <typename DT>
inline
DT
memory_fast_access<DT>::
doPostDecrement(unsigned long long index)
{
  if (get_fast_backdoor()) {
    return mFastAccessImpl.doPostDecrement(index);

  } else {
    return mSlowAccess->doPostDecrement(index);
  }
}

template <typename DT>
inline
void
memory_fast_access<DT>::
doPreIncrement(unsigned long long index)
{
  if (get_fast_backdoor()) {
    mFastAccessImpl.doPreIncrement(index);

  } else {
    mSlowAccess->doPreIncrement(index);
  }
}

template <typename DT>
inline
DT
memory_fast_access<DT>::
doPostIncrement(unsigned long long index)
{
  if (get_fast_backdoor()) {
    return mFastAccessImpl.doPostIncrement(index);

  } else {
    return mSlowAccess->doPostIncrement(index);
  }
}

}

#endif
