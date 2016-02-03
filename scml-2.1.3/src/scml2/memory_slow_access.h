/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_SLOW_ACCESS_H
#define SCML2_MEMORY_SLOW_ACCESS_H

#include <scml2/memory_slow_access_base.h>

namespace scml2 {

template <typename DT, typename I>
class memory_slow_access : public memory_slow_access_base<DT>
{
public:
  memory_slow_access(I impl);

  virtual unsigned char* get_fast_backdoor() const;

  virtual void put(unsigned long long address,
                   const unsigned char* data,
                   unsigned int dataLength,
                   const unsigned char* byteEnablePtr,
                   unsigned int byteEnableLength,
                   bool isDebug = false);
  virtual void get(unsigned long long address,
                   unsigned char* data,
                   unsigned int dataLength,
                   const unsigned char* byteEnablePtr,
                   unsigned int byteEnableLength,
                   bool isDebug = false) const;

  virtual void put(unsigned long long index,
                   DT data,
                   unsigned int size,
                   unsigned int offset,
                   bool isDebug = false);
  virtual void put(unsigned long long index,
                   DT data,
                   bool isDebug = false);
  virtual DT get(unsigned long long index,
                 unsigned int size,
                 unsigned int offset,
                 bool isDebug = false) const;
  virtual DT get(unsigned long long index,
                 bool isDebug = false) const;

  virtual void doAdd(unsigned long long index, DT rhs);
  virtual void doSubtract(unsigned long long index, DT rhs);
  virtual void doDivide(unsigned long long index, DT rhs);
  virtual void doMultiply(unsigned long long index, DT rhs);
  virtual void doModulo(unsigned long long index, DT rhs);
  virtual void doXor(unsigned long long index, DT rhs);
  virtual void doAnd(unsigned long long index, DT rhs);
  virtual void doOr(unsigned long long index, DT rhs);
  virtual void doShiftRight(unsigned long long index, DT rhs);
  virtual void doShiftLeft(unsigned long long index, DT rhs);

  virtual void doPreDecrement(unsigned long long index);
  virtual DT doPostDecrement(unsigned long long index);
  virtual void doPreIncrement(unsigned long long index);
  virtual DT doPostIncrement(unsigned long long index);

protected:
  I mImpl;
};

template <typename DT, typename I>
inline
memory_slow_access_base<DT>*
create_slow_access(I impl)
{
  return new memory_slow_access<DT, I>(impl);
}

template <typename DT, typename I>
inline
memory_slow_access<DT, I>::
memory_slow_access(I impl) :
  mImpl(impl)
{
}

template <typename DT, typename I>
inline
unsigned char*
memory_slow_access<DT, I>::
get_fast_backdoor() const
{
  return mImpl.get_fast_backdoor();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
put(unsigned long long address,
    const unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength,
    bool isDebug)
{
  this->ref();
  mImpl.put(address, data, dataLength, byteEnablePtr, byteEnableLength, isDebug);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
get(unsigned long long address,
    unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength,
    bool isDebug) const
{
  this->ref();
  mImpl.get(address, data, dataLength, byteEnablePtr, byteEnableLength, isDebug);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
put(unsigned long long index,
    DT data,
    unsigned int size,
    unsigned int offset,
    bool isDebug)
{
  this->ref();
  mImpl.put(index, data, size, offset, isDebug);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
put(unsigned long long index,
    DT data,
    bool isDebug)
{
  this->ref();
  mImpl.put(index, data, isDebug);
  this->unref();
}

template <typename DT, typename I>
inline
DT
memory_slow_access<DT, I>::
get(unsigned long long index,
    unsigned int size,
    unsigned int offset,
    bool isDebug) const
{
  this->ref();
  const DT tmp =  mImpl.get(index, size, offset, isDebug);
  this->unref();
  return tmp;
}

template <typename DT, typename I>
inline
DT
memory_slow_access<DT, I>::
get(unsigned long long index,
    bool isDebug) const
{
  this->ref();
  const DT tmp = mImpl.get(index, isDebug);
  this->unref();
  return tmp;
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doAdd(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) + rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doSubtract(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) - rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doDivide(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) / rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doMultiply(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) * rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doModulo(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) % rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doXor(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) ^ rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doAnd(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) & rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doOr(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) | rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doShiftRight(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) >> rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doShiftLeft(unsigned long long index, DT rhs)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) << rhs);
  this->unref();
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doPreDecrement(unsigned long long index)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) - 1);
  this->unref();
}

template <typename DT, typename I>
inline
DT
memory_slow_access<DT, I>::
doPostDecrement(unsigned long long index)
{
  this->ref();
  DT tmp = mImpl.get(index);
  mImpl.put(index, tmp - 1);
  this->unref();
  return tmp;
}

template <typename DT, typename I>
inline
void
memory_slow_access<DT, I>::
doPreIncrement(unsigned long long index)
{
  this->ref();
  mImpl.put(index, mImpl.get(index) + 1);
  this->unref();
}

template <typename DT, typename I>
inline
DT
memory_slow_access<DT, I>::
doPostIncrement(unsigned long long index)
{
  this->ref();
  DT tmp = mImpl.get(index);
  mImpl.put(index, tmp + 1);
  this->unref();
  return tmp;
}

}

#endif
