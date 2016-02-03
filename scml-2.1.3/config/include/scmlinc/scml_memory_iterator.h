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
 * Purpose of file : Definition of scml_memory iterator
 *
 */

#ifndef SCML_MEMORY_ITERATOR_H
#define SCML_MEMORY_ITERATOR_H

#include <iterator>

/************************************************************************
 * Defined here
 */
template< typename DT > class scml_memory_iterator;

/************************************************************************
 * Forward declarations
 */
template< typename DT > class scml_memory_index_reference;
template< typename DT > class scml_memory_operations_podt_common;


/************************************************************************
 * Generic Template
 */
template <typename DT>
class scml_memory_iterator :
  public std::iterator<std::random_access_iterator_tag, DT>
{
public:
  typedef unsigned long long size_type;

  typedef std::iterator<std::random_access_iterator_tag, DT> iterator_type;
  typedef typename iterator_type::value_type value_type;
  typedef typename iterator_type::difference_type difference_type;
  typedef typename iterator_type::pointer pointer_type;
  typedef typename iterator_type::reference reference_type;

  typedef scml_memory_iterator this_type;

  scml_memory_iterator(scml_memory< DT >* m, size_type i);

  DT operator* () const;
  scml_memory_index_reference<DT> operator* ();
  DT operator[](size_type i) const;
  scml_memory_index_reference<DT> operator[](size_type i);

  this_type operator++();
  this_type operator++(int);
  this_type operator--();
  this_type operator--(int);

  this_type operator+=(int);
  this_type operator-=(int);

  this_type operator-(difference_type v) const;
  this_type operator+(difference_type v) const;

  int operator-(const this_type& v) const;

  bool operator==(const this_type& v) const;
  bool operator!=(const this_type& v) const;
  bool operator<(const this_type& v) const;
  bool operator>(const this_type& v) const;
  bool operator<=(const this_type& v) const;
  bool operator>=(const this_type& v) const;

  bool isEnd() const;

protected:
  const scml_memory_operations_podt_common< DT >* getToplevel() const;

  static difference_type distance(const this_type& it1, const this_type& it2);

private:
  // data member
  scml_memory< DT > * mMem;
  size_type mIndex;
};

template <typename DT>
inline
scml_memory_iterator< DT >::
scml_memory_iterator(scml_memory< DT >* m, size_type i) :
  mMem(m),
  mIndex(i)
{
  if (mIndex > mMem->size()) {
    mIndex = mMem->size();
  }
}

template <typename DT>
inline
DT
scml_memory_iterator< DT >::operator*() const
{
  return mMem->get(mIndex);
}

template <typename DT>
inline
scml_memory_index_reference<DT>
scml_memory_iterator< DT >::operator*()
{
  return scml_memory_index_reference<DT>(mMem, mIndex);
}

template <typename DT>
inline
DT
scml_memory_iterator< DT >::operator[](size_type i) const
{
  const this_type tmp = *this + i;
  return *tmp;
}

template <typename DT>
inline
scml_memory_index_reference<DT>
scml_memory_iterator< DT >::operator[](size_type i)
{
  this_type tmp = *this + i;
  return *tmp;
}

template <typename DT>
inline
scml_memory_iterator< DT >
scml_memory_iterator< DT >::operator++()
{
  if (!isEnd()) {
    ++mIndex;
  }
  return *this;
}

template <typename DT>
inline
scml_memory_iterator< DT >
scml_memory_iterator< DT >::operator++(int)
{
  this_type tmp = *this;
  ++(*this);
  return tmp;
}

template <typename DT>
inline
scml_memory_iterator< DT >
scml_memory_iterator< DT >::operator--()
{
  if (mIndex == 0) {
    mIndex = mMem->size();

  } else {
    --mIndex;
  }
  return *this;
}

template <typename DT>
inline
scml_memory_iterator< DT >
scml_memory_iterator< DT >::operator--(int)
{
  this_type tmp = *this;
  --(*this);
  return tmp;
}

template <typename DT>
inline
scml_memory_iterator< DT >
scml_memory_iterator< DT >::operator+=(int v)
{
  if (v < 0) {
    return this->operator-(-v);
  }

  if (mMem->size() - mIndex <= (unsigned int)v) {
    mIndex = mMem->size();

  } else {
    mIndex += v;
  }
  return *this;
}

template <typename DT>
inline
scml_memory_iterator< DT >
scml_memory_iterator< DT >::operator-=(int v)
{
  if (v < 0) {
    return this->operator+(-v);
  }

  if (mIndex < (unsigned int)v) {
    mIndex = mMem->size();

  } else {
    mIndex -= v;
  }
  return *this;
}

template <typename DT>
inline
scml_memory_iterator< DT >
scml_memory_iterator< DT >::operator-(difference_type v) const
{
  this_type tmp = *this;
  return tmp -= v;
}

template <typename DT>
inline
scml_memory_iterator< DT >
scml_memory_iterator< DT >::operator+(difference_type v) const
{
  this_type tmp = *this;
  return tmp += v;
}

template <typename DT>
inline
int
scml_memory_iterator< DT >::operator-(const this_type& v) const
{
  return mIndex - v.mIndex;
}

template <typename DT>
inline
typename scml_memory_iterator< DT >::difference_type
scml_memory_iterator< DT >::distance(const this_type& it1,
                                     const this_type& it2)
{
  assert(it1.getToplevel() == it2.getToplevel());
  return (it1.mMem->offset() + it1.mIndex) - (it2.mMem->offset() + it2.mIndex);
}

template <typename DT>
inline
bool
scml_memory_iterator< DT >::operator==(const this_type& v) const
{
  return distance(*this, v) == 0;
}

template <typename DT>
inline
bool
scml_memory_iterator< DT >::operator!=(const this_type& v) const
{
  return distance(*this, v) != 0;
}

template <typename DT>
inline
bool
scml_memory_iterator< DT >::operator<(const this_type& v) const
{
  return distance(*this, v) < 0;
}

template <typename DT>
inline
bool
scml_memory_iterator< DT >::operator>(const this_type& v) const
{
  return distance(*this, v) > 0;
}

template <typename DT>
inline
bool
scml_memory_iterator< DT >::operator<=(const this_type& v) const
{
  return distance(*this, v) <= 0;
}

template <typename DT>
inline
bool
scml_memory_iterator< DT >::operator>=(const this_type& v) const
{
  return distance(*this, v) >= 0;
}

template <typename DT>
inline
bool
scml_memory_iterator< DT >::isEnd() const
{
  return mIndex == mMem->size();
}


template <typename DT>
inline
const scml_memory_operations_podt_common< DT >*
scml_memory_iterator< DT >::getToplevel() const
{
  return mMem->mToplevel;
}

#endif
