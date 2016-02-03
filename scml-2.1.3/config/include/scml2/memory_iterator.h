/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_ITERATOR_H
#define SCML2_MEMORY_ITERATOR_H

#include <scml2/memory_iterator_base.h>

#include <scml2/memory_index_reference.h>
#include <scml2/memory_const_iterator.h>

namespace scml2 {

template <typename DT> class memory;
template <typename DT> class memory_iterator;
template <typename DT> class memory_const_iterator;
template <typename DT> class memory_index_reference;

template <typename DT>
class memory_iterator :
  public memory_iterator_base<DT>
{
public:
  typedef DT data_type;
  typedef memory_iterator_base<DT> base_type;
  typedef memory_index_reference<DT> reference;
  typedef DT const_reference;
  typedef memory_index_reference<DT>* pointer;
  typedef memory_iterator iterator;
  typedef typename base_type::difference_type difference_type;

public:
  memory_iterator();
  memory_iterator(memory<DT>* m, unsigned long long index);

  reference operator*() const;

  reference operator[](difference_type n) const;

  iterator& operator+=(difference_type n);
  iterator& operator-=(difference_type n);
  iterator operator+(difference_type n) const;
  iterator operator-(difference_type n) const;

  iterator& operator--();
  iterator operator--(int);
  iterator& operator++();
  iterator operator++(int);

  friend class memory_const_iterator<DT>;
};

template <typename DT>
inline
memory_iterator<DT>
operator+(typename memory_iterator<DT>::difference_type n,
          const memory_iterator<DT>& i)
{
  return i + n;
}

template <typename DT>
inline
memory_iterator<DT>::
memory_iterator() :
  memory_iterator_base<DT>(0, 0)
{
}

template <typename DT>
inline
memory_iterator<DT>::
memory_iterator(memory<DT>* memory, unsigned long long index) :
  memory_iterator_base<DT>(memory, index)
{
}

template <typename DT>
inline
memory_index_reference<DT>
memory_iterator<DT>::
operator*() const
{
  return memory_index_reference<DT>(this->mMemory, this->mIndex);
}

template <typename DT>
inline
memory_index_reference<DT>
memory_iterator<DT>::
operator[](difference_type n) const
{
  return *(*this + n);
}

template <typename DT>
inline
memory_iterator<DT>&
memory_iterator<DT>::
operator+=(difference_type n)
{
  this->increment(n);
  return *this;
}

template <typename DT>
inline
memory_iterator<DT>&
memory_iterator<DT>::
operator-=(difference_type n)
{
  this->increment(-n);
  return *this;
}

template <typename DT>
inline
memory_iterator<DT>
memory_iterator<DT>::
operator+(difference_type n) const
{
  iterator tmp = *this;
  return tmp += n;
}

template <typename DT>
inline
memory_iterator<DT>
memory_iterator<DT>::
operator-(difference_type n) const
{
  iterator tmp = *this;
  return tmp -= n;
}

template <typename DT>
inline
memory_iterator<DT>&
memory_iterator<DT>::
operator--()
{
  this->decrement();
  return *this;
}

template <typename DT>
inline
memory_iterator<DT>
memory_iterator<DT>::
operator--(int)
{
  const iterator tmp = *this;
  this->decrement();
  return tmp;
}

template <typename DT>
inline
memory_iterator<DT>&
memory_iterator<DT>::
operator++()
{
  this->increment();
  return *this;
}

template <typename DT>
inline
memory_iterator<DT>
memory_iterator<DT>::
operator++(int)
{
  const iterator tmp = *this;
  this->increment();
  return tmp;
}

}

#endif
