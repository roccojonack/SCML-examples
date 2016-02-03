/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_FAST_ACCESS_IMPL_H
#define SCML2_MEMORY_FAST_ACCESS_IMPL_H

#include <scml2/utils.h>

#include <systemc>
#include <cassert>

namespace scml2 {

class memory_fast_access_impl_base
{
public:
  memory_fast_access_impl_base();
  memory_fast_access_impl_base(unsigned char* fastBackdoor);

  unsigned char* get_fast_backdoor() const;
  void set_fast_backdoor(unsigned char* p);

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

protected:
  unsigned char* mFastBackdoor;
};

template <typename DT>
class memory_fast_access_impl :
  public memory_fast_access_impl_base
{
public:
  memory_fast_access_impl();

  memory_fast_access_impl(unsigned char* fastBackdoor);

  using memory_fast_access_impl_base::put;
  using memory_fast_access_impl_base::get;

  void put(unsigned long long index,
           DT data,
           unsigned int size,
           unsigned int offset,
           bool isDebug = false);
  void put(unsigned long long index,
           DT data,
           bool isDebug = false);
  DT get(unsigned long long index,
         unsigned int size,
         unsigned int offset,
         bool isDebug = false) const;
  DT get(unsigned long long index,
         bool isDebug = false) const;

  void doAdd(unsigned long long index, DT rhs);
  void doSubtract(unsigned long long index, DT rhs);
  void doDivide(unsigned long long index, DT rhs);
  void doMultiply(unsigned long long index, DT rhs);
  void doModulo(unsigned long long index, DT rhs);
  void doXor(unsigned long long index, DT rhs);
  void doAnd(unsigned long long index, DT rhs);
  void doOr(unsigned long long index, DT rhs);
  void doShiftRight(unsigned long long index, DT rhs);
  void doShiftLeft(unsigned long long index, DT rhs);

  void doPreDecrement(unsigned long long index);
  DT doPostDecrement(unsigned long long index);
  void doPreIncrement(unsigned long long index);
  DT doPostIncrement(unsigned long long index);
};


template <int N>
class memory_fast_access_impl<sc_dt::sc_biguint<N> > :
  public memory_fast_access_impl_base
{
public:
  memory_fast_access_impl();
  memory_fast_access_impl(unsigned char* fastBackdoor);

  using memory_fast_access_impl_base::put;
  using memory_fast_access_impl_base::get;

  void put(unsigned long long index,
           const sc_dt::sc_biguint<N>& data,
           unsigned int size,
           unsigned int offset,
           bool isDebug = false);
  void put(unsigned long long index,
           const sc_dt::sc_biguint<N>& data,
           bool isDebug = false);
  sc_dt::sc_biguint<N> get(unsigned long long index,
                           unsigned int size,
                           unsigned int offset,
                           bool isDebug = false) const;
  sc_dt::sc_biguint<N> get(unsigned long long index,
                           bool isDebug = false) const;

  void doAdd(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);
  void doSubtract(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);
  void doDivide(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);
  void doMultiply(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);
  void doModulo(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);
  void doXor(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);
  void doAnd(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);
  void doOr(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);
  void doShiftRight(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);
  void doShiftLeft(unsigned long long index, const sc_dt::sc_biguint<N>& rhs);

  void doPreDecrement(unsigned long long index);
  sc_dt::sc_biguint<N> doPostDecrement(unsigned long long index);
  void doPreIncrement(unsigned long long index);
  sc_dt::sc_biguint<N> doPostIncrement(unsigned long long index);
};

//
// memory_fast_access_impl_base
//

inline
memory_fast_access_impl_base::
memory_fast_access_impl_base() :
  mFastBackdoor(0)
{
}

inline
memory_fast_access_impl_base::
memory_fast_access_impl_base(unsigned char* fastBackdoor) :
  mFastBackdoor(fastBackdoor)
{
  mFastBackdoor = fastBackdoor;
}

inline
unsigned char*
memory_fast_access_impl_base::
get_fast_backdoor() const
{
  return mFastBackdoor;
}

inline
void
memory_fast_access_impl_base::
set_fast_backdoor(unsigned char* p)
{
  mFastBackdoor = p;
}

inline
void
memory_fast_access_impl_base::
put(unsigned long long address,
    const unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength,
    bool)
{
  assert(mFastBackdoor);
  copy_data(mFastBackdoor + address,
            data,
            dataLength,
            byteEnablePtr,
            byteEnableLength);
}

inline
void
memory_fast_access_impl_base::
get(unsigned long long address,
    unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength,
    bool) const
{
  assert(mFastBackdoor);
  copy_data(data,
            mFastBackdoor + address,
            dataLength,
            byteEnablePtr,
            byteEnableLength);
}

//
// template <typename DT> class memory_fast_access_impl
//

template <typename DT>
inline
memory_fast_access_impl<DT>::
memory_fast_access_impl() :
  memory_fast_access_impl_base()
{
}

template <typename DT>
inline
memory_fast_access_impl<DT>::
memory_fast_access_impl(unsigned char* fastBackdoor) :
  memory_fast_access_impl_base(fastBackdoor)
{
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
put(unsigned long long index,
    DT data,
    unsigned int size,
    unsigned int offset,
    bool)
{
  assert(mFastBackdoor);
  DT& v = reinterpret_cast<DT*>(mFastBackdoor)[index];
  v = insert_bits(v, data, size * 8, offset * 8);
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
put(unsigned long long index,
    DT data,
    bool)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(mFastBackdoor)[index] = data;
}

template <typename DT>
inline
DT
memory_fast_access_impl<DT>::
get(unsigned long long index,
    unsigned int size,
    unsigned int offset,
    bool) const
{
  assert(mFastBackdoor);
  return extract_bits(reinterpret_cast<DT*>(mFastBackdoor)[index],
                      size * 8,
                      offset * 8);
}

template <typename DT>
inline
DT
memory_fast_access_impl<DT>::
get(unsigned long long index,
    bool) const
{
  assert(mFastBackdoor);
  return reinterpret_cast<DT*>(mFastBackdoor)[index];
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doAdd(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] += rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doSubtract(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] -= rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doDivide(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] /= rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doMultiply(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] *= rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doModulo(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] %= rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doXor(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] ^= rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doAnd(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] &= rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doOr(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] |= rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doShiftRight(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] >>= rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doShiftLeft(unsigned long long index, DT rhs)
{
  assert(mFastBackdoor);
  reinterpret_cast<DT*>(this->mFastBackdoor)[index] <<= rhs;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doPreDecrement(unsigned long long index)
{
  assert(mFastBackdoor);
  --(reinterpret_cast<DT*>(this->mFastBackdoor)[index]);
}

template <typename DT>
inline
DT
memory_fast_access_impl<DT>::
doPostDecrement(unsigned long long index)
{
  assert(mFastBackdoor);
  return (reinterpret_cast<DT*>(this->mFastBackdoor)[index])--;
}

template <typename DT>
inline
void
memory_fast_access_impl<DT>::
doPreIncrement(unsigned long long index)
{
  assert(mFastBackdoor);
  ++(reinterpret_cast<DT*>(this->mFastBackdoor)[index]);
}

template <typename DT>
inline
DT
memory_fast_access_impl<DT>::
doPostIncrement(unsigned long long index)
{
  assert(mFastBackdoor);
  return (reinterpret_cast<DT*>(this->mFastBackdoor)[index])++;
}

//
// template <int N> class memory_fast_access_impl<sc_dt::sc_biguint<N> >
//

template <int N>
inline
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
memory_fast_access_impl() :
  memory_fast_access_impl_base()
{
}

template <int N>
inline
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
memory_fast_access_impl(unsigned char* fastBackdoor) :
  memory_fast_access_impl_base(fastBackdoor)
{
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
put(unsigned long long index,
    const sc_dt::sc_biguint<N>& data,
    unsigned int size,
    unsigned int offset,
    bool)
{
  assert(mFastBackdoor);
  const unsigned long long address = index_to_address<sc_dt::sc_biguint<N> >(index);
  to_char_array(data, mFastBackdoor + address + offset, size, 0);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
put(unsigned long long index,
    const sc_dt::sc_biguint<N>& data,
    bool)
{
  assert(mFastBackdoor);
  const unsigned long long address = index_to_address<sc_dt::sc_biguint<N> >(index);
  to_char_array(data, mFastBackdoor + address, N / 8, 0);
}

template <int N>
inline
sc_dt::sc_biguint<N>
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
get(unsigned long long index,
    unsigned int size,
    unsigned int offset,
    bool) const
{
  assert(mFastBackdoor);
  sc_dt::sc_biguint<N> v(0);
  const unsigned long long address = index_to_address<sc_dt::sc_biguint<N> >(index);
  from_char_array(mFastBackdoor + address + offset, v, size, 0);
  return v;
}

template <int N>
inline
sc_dt::sc_biguint<N>
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
get(unsigned long long index,
    bool) const
{
  assert(mFastBackdoor);
  sc_dt::sc_biguint<N> v(0);
  const unsigned long long address = index_to_address<sc_dt::sc_biguint<N> >(index);
  from_char_array(mFastBackdoor + address, v, N / 8, 0);
  return v;
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doAdd(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) + rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doSubtract(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) - rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doDivide(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) / rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doMultiply(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) * rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doModulo(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) % rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doXor(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) ^ rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doAnd(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) & rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doOr(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) | rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doShiftRight(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) >> rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doShiftLeft(unsigned long long index, const sc_dt::sc_biguint<N>& rhs)
{
  put(index, get(index) << rhs);
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doPreDecrement(unsigned long long index)
{
  put(index, get(index) - 1);
}

template <int N>
inline
sc_dt::sc_biguint<N>
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doPostDecrement(unsigned long long index)
{
  sc_dt::sc_biguint<N> tmp = get(index);
  doPreDecrement(index);
  return tmp;
}

template <int N>
inline
void
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doPreIncrement(unsigned long long index)
{
  put(index, get(index) + 1);
}

template <int N>
inline
sc_dt::sc_biguint<N>
memory_fast_access_impl<sc_dt::sc_biguint<N> >::
doPostIncrement(unsigned long long index)
{
  sc_dt::sc_biguint<N> tmp = get(index);
  doPreIncrement(index);
  return tmp;
}

}

#endif
