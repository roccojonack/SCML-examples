/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_INDEX_REFERENCE_H
#define SCML2_MEMORY_INDEX_REFERENCE_H

#include <scml2/memory.h>

#include <cassert>

namespace scml2 {

template <typename DT> class memory;

template <typename DT>
class memory_index_reference
{
public:
  typedef DT data_type;
  typedef memory_index_reference<DT> reference;

public:
  memory_index_reference(memory<DT>* m, unsigned long long index);

  void put(const DT& value);
  DT get() const;

  void put_debug(const DT& value);
  DT get_debug() const;

  operator DT() const;

  reference& operator=(DT value);

  reference& operator+=(DT value);
  reference& operator-=(DT value);
  reference& operator/=(DT value);
  reference& operator*=(DT value);
  reference& operator%=(DT value);
  reference& operator^=(DT value);
  reference& operator&=(DT value);
  reference& operator|=(DT value);
  reference& operator>>=(DT value);
  reference& operator<<=(DT value);

  reference& operator--();
  DT operator--(int);
  reference& operator++();
  DT operator++(int);

protected:
  memory<DT>* mMemory;
  unsigned long long mIndex;
};

template <typename DT>
inline
memory_index_reference<DT>::
memory_index_reference(memory<DT>* m, unsigned long long index) :
  mMemory(m),
  mIndex(index)
{
}

template <typename DT>
inline
void
memory_index_reference<DT>::
put(const DT& value)
{
  assert(mMemory);
  mMemory->put(mIndex, value);
}

template <typename DT>
inline
DT
memory_index_reference<DT>::
get() const
{
  assert(mMemory);
  return mMemory->get(mIndex);
}

template <typename DT>
inline
void
memory_index_reference<DT>::
put_debug(const DT& value)
{
  assert(mMemory);
  mMemory->put_debug(mIndex, value);
}

template <typename DT>
inline
DT
memory_index_reference<DT>::
get_debug() const
{
  assert(mMemory);
  return mMemory->get_debug(mIndex);
}

template <typename DT>
inline
memory_index_reference<DT>::
operator DT() const
{
  return get();
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator=(DT value)
{
  put(value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator+=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doAdd(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator-=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doSubtract(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator/=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doDivide(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator*=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doMultiply(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator%=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doModulo(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator^=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doXor(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator&=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doAnd(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator|=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doOr(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator>>=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doShiftRight(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator<<=(DT value)
{
  assert(mMemory);
  mMemory->mFastAccess.doShiftLeft(mIndex, value);
  return *this;
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator--()
{
  assert(mMemory);
  mMemory->mFastAccess.doPreDecrement(mIndex);
  return *this;
}

template <typename DT>
inline
DT
memory_index_reference<DT>::
operator--(int)
{
  assert(mMemory);
  return mMemory->mFastAccess.doPostDecrement(mIndex);
}

template <typename DT>
inline
memory_index_reference<DT>&
memory_index_reference<DT>::
operator++()
{
  assert(mMemory);
  mMemory->mFastAccess.doPreIncrement(mIndex);
  return *this;
}

template <typename DT>
inline
DT
memory_index_reference<DT>::
operator++(int)
{
  assert(mMemory);
  return mMemory->mFastAccess.doPostIncrement(mIndex);
}

}

#endif
