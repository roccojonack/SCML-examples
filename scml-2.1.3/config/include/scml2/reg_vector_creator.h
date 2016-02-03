/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_REG_VECTOR_CREATOR_H
#define SCML2_REG_VECTOR_CREATOR_H

#include <scml2/reg.h>

namespace scml2 {

template <typename DT>
class memory;

template <typename DT, typename T = scml2::reg<DT> >
class reg_vector_creator
{
public:
  reg_vector_creator(scml2::memory<DT>& parent, size_t offset = 0, size_t size = 1) : mParent(parent), mOffset(offset), mSize(size) {
  }

  T* operator()(const char* prefix, size_t i) {
    return new T(prefix, mParent, mOffset + i*mSize);
  }

private:
  scml2::memory<DT>& mParent;
  size_t mOffset;
  size_t mSize;
};

template <typename DT, typename T, typename U>
class reg_vector_creator_with_extra_parameter
{
public:
  reg_vector_creator_with_extra_parameter(scml2::memory<DT>& parent, size_t offset, size_t size, U& parameter) : mParent(parent), mOffset(offset), mSize(size), mParameter(parameter) {
  }

  T* operator()(const char* prefix, size_t i) {
    return new T(prefix, mParent, mOffset + i*mSize, mParameter);
  }

private:
  scml2::memory<DT>& mParent;
  size_t mOffset;
  size_t mSize;
  U& mParameter;
};

template <typename DT>
inline reg_vector_creator<DT>
create_reg_vector_creator(scml2::memory<DT>& parent, size_t offset = 0, size_t size = 1) {
  return reg_vector_creator<DT>(parent, offset, size);
}

template <typename DT, typename T>
inline reg_vector_creator<DT, T>
create_reg_vector_creator(scml2::memory<DT>& parent, size_t offset = 0, size_t size = 1) {
  return reg_vector_creator<DT, T>(parent, offset, size);
}

template <typename DT, typename T, typename U>
inline reg_vector_creator_with_extra_parameter<DT, T, U>
create_reg_vector_creator(scml2::memory<DT>& parent, size_t offset, size_t size, U& u) {
  return reg_vector_creator_with_extra_parameter<DT, T, U>(parent, offset, size, u);
}

}

#endif
