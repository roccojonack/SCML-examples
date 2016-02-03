/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_SCOPED_REFERENCE_H
#define SCML2_SCOPED_REFERENCE_H

namespace scml2 {

template <typename T>
class scoped_reference
{
public:
  scoped_reference(T* t);
  ~scoped_reference();

private:
  T* mT;
};

template <typename T>
inline
scoped_reference<T>::
scoped_reference(T* t) :
  mT(t)
{
  mT->ref();
}

template <typename T>
inline
scoped_reference<T>::
~scoped_reference()
{
  mT->unref();
}

}

#endif
