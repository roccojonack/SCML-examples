/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_CONST_ITERATOR_H
#define SCML2_MEMORY_CONST_ITERATOR_H

#include <scml2/memory_iterator_base.h>

#include <scml2/memory_index_reference.h>

namespace scml2 {

template <typename DT> class memory;
template <typename DT> class memory_iterator;
template <typename DT> class memory_const_iterator;
template <typename DT> class memory_index_reference;

template <typename DT>
class memory_const_iterator :
  public memory_iterator_base<DT>
{
public:
  typedef DT data_type;
  typedef memory_iterator_base<DT> base_type;
  typedef DT reference;
  typedef DT const_reference;
  typedef const DT* pointer;
  typedef memory_iterator<DT> iterator;
  typedef memory_const_iterator const_iterator;
  typedef typename base_type::difference_type difference_type;

public:
  memory_const_iterator();
  memory_const_iterator(const memory<DT>* m,
                        unsigned long long index);
  memory_const_iterator(const iterator& i);

  const_reference operator*() const;

  const_reference operator[](difference_type n) const;

  const_iterator& operator+=(difference_type n);
  const_iterator& operator-=(difference_type n);
  const_iterator operator+(difference_type n) const;
  const_iterator operator-(difference_type n) const;

  const_iterator& operator--();
  const_iterator operator--(int);
  const_iterator& operator++();
  const_iterator operator++(int);
};

template <typename DT>
inline
memory_const_iterator<DT>
operator+(typename memory_const_iterator<DT>::difference_type n,
          const memory_const_iterator<DT>& i)
{
  return i + n;
}

template <typename DT>
inline
memory_const_iterator<DT>::
memory_const_iterator() :
  memory_iterator_base<DT>(0, 0)
{
}

template <typename DT>
inline
memory_const_iterator<DT>::
memory_const_iterator(const memory<DT>* m,
                      unsigned long long index) :
  memory_iterator_base<DT>(const_cast<memory<DT>*>(m), index)
{
}

template <typename DT>
inline
memory_const_iterator<DT>::
memory_const_iterator(const iterator& i) :
  memory_iterator_base<DT>(i.mMemory, i.mIndex)
{
}

template <typename DT>
inline
DT
memory_const_iterator<DT>::
operator*() const
{
  return memory_index_reference<DT>(this->mMemory, this->mIndex);
}

template <typename DT>
inline
DT
memory_const_iterator<DT>::
operator[](difference_type n) const
{
  return *(*this + n);
}

template <typename DT>
inline
memory_const_iterator<DT>&
memory_const_iterator<DT>::
operator+=(difference_type n)
{
  this->increment(n);
  return *this;
}

template <typename DT>
inline
memory_const_iterator<DT>&
memory_const_iterator<DT>::
operator-=(difference_type n)
{
  this->increment(-n);
  return *this;
}

template <typename DT>
inline
memory_const_iterator<DT>
memory_const_iterator<DT>::
operator+(difference_type n) const
{
  const_iterator tmp = *this;
  return tmp += n;
}

template <typename DT>
inline
memory_const_iterator<DT>
memory_const_iterator<DT>::
operator-(difference_type n) const
{
  const_iterator tmp = *this;
  return tmp -= n;
}

template <typename DT>
inline
memory_const_iterator<DT>&
memory_const_iterator<DT>::
operator--()
{
  this->decrement();
  return *this;
}

template <typename DT>
inline
memory_const_iterator<DT>
memory_const_iterator<DT>::
operator--(int)
{
  const const_iterator tmp = *this;
  this->decrement();
  return tmp;
}

template <typename DT>
inline
memory_const_iterator<DT>&
memory_const_iterator<DT>::
operator++()
{
  this->increment();
  return *this;
}

template <typename DT>
inline
memory_const_iterator<DT>
memory_const_iterator<DT>::
operator++(int)
{
  const const_iterator tmp = *this;
  this->increment();
  return tmp;
}

}

#endif
