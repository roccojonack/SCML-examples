/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_ITERATOR_BASE_H
#define SCML2_MEMORY_ITERATOR_BASE_H

#include <cassert>
#include <iterator>

namespace scml2 {

template <typename DT> class memory;
template <typename DT> class memory_iterator_base;

template <typename DT>
class memory_iterator_base :
  public std::iterator<std::random_access_iterator_tag, DT, long long>
{
public:
  typedef memory_iterator_base this_type;
  typedef std::iterator<std::random_access_iterator_tag, DT, long long> base_type;
  typedef typename base_type::difference_type difference_type;

public:
  memory_iterator_base(memory<DT>* m, unsigned long long index);

  virtual ~memory_iterator_base();

  bool operator==(const this_type& i) const;
  bool operator!=(const this_type& i) const;
  bool operator<(const this_type& i) const;
  bool operator>(const this_type& i) const;
  bool operator<=(const this_type& i) const;
  bool operator>=(const this_type& i) const;

  template <typename _DT>
  friend typename memory_iterator_base<_DT>::difference_type operator-(const memory_iterator_base<_DT>&, const memory_iterator_base<_DT>&);
  
protected:
  void increment();
  void decrement();
  void increment(difference_type n);

protected:
  memory<DT>* mMemory;
  unsigned long long mIndex;
};

template <typename DT>
inline
typename memory_iterator_base<DT>::difference_type
operator-(const memory_iterator_base<DT>& i1,
          const memory_iterator_base<DT>& i2)
{
  assert(i1.mMemory == i2.mMemory);
  return i1.mIndex - i2.mIndex;
}

template <typename DT>
inline
memory_iterator_base<DT>::
memory_iterator_base(memory<DT>* m, unsigned long long index) :
  mMemory(m),
  mIndex(index)
{
}

template <typename DT>
inline
memory_iterator_base<DT>::
~memory_iterator_base()
{
}

template <typename DT>
inline
bool
memory_iterator_base<DT>::
operator==(const this_type& i) const
{
  return mMemory == i.mMemory && mIndex == i.mIndex;
}

template <typename DT>
inline
bool
memory_iterator_base<DT>::
operator!=(const this_type& i) const
{
  return !(*this == i);
}

template <typename DT>
inline
bool
memory_iterator_base<DT>::
operator<(const this_type& i) const
{
  assert(mMemory == i.mMemory);
  return mIndex < i.mIndex;
}

template <typename DT>
inline
bool
memory_iterator_base<DT>::
operator>(const this_type& i) const
{
  return i < *this;
}

template <typename DT>
inline
bool
memory_iterator_base<DT>::
operator<=(const this_type& i) const
{
  return !(i < *this);
}

template <typename DT>
inline
bool
memory_iterator_base<DT>::
operator>=(const this_type& i) const
{
  return !(i < *this);
}

template <typename DT>
inline
void
memory_iterator_base<DT>::
increment()
{
  ++mIndex;
}

template <typename DT>
inline
void
memory_iterator_base<DT>::
decrement()
{
  --mIndex;
}

template <typename DT>
inline
void
memory_iterator_base<DT>::
increment(difference_type n)
{
  mIndex += n;
}

}

#endif
