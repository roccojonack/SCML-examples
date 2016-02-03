/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_MASK_WRITE_ADAPTER_TAGGED_H
#define SCML2_BITFIELD_MASK_WRITE_ADAPTER_TAGGED_H

#include <tlm.h>
#include <cassert>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT, typename C>
class bitfield_mask_write_adapter_tagged
{
public:
  typedef bool (C::*CallbackType)(const DT& value,
                                  const DT& bitMask,
                                  sc_core::sc_time& t,
                                  int id);

public:
  bitfield_mask_write_adapter_tagged(C& c, CallbackType cb, int id);

  bool operator()(const DT& value, const DT& bitMask, sc_core::sc_time& t);

private:
  C& mC;
  CallbackType mCallback;
  int mId;
};

template <typename DT, typename C>
inline
bitfield_mask_write_adapter_tagged<DT, C>
create_bitfield_write_adapter(C& c,
                              typename bitfield_mask_write_adapter_tagged<DT, C>::CallbackType cb,
                              int id)
{
  return bitfield_mask_write_adapter_tagged<DT, C>(c, cb, id);
}

template <typename DT, typename C>
inline
bitfield_mask_write_adapter_tagged<DT, C>::
bitfield_mask_write_adapter_tagged(C& c, CallbackType cb, int id) :
  mC(c),
  mCallback(cb),
  mId(id)
{
}

template <typename DT, typename C>
inline
bool
bitfield_mask_write_adapter_tagged<DT, C>::
operator()(const DT& value, const DT& bitMask, sc_core::sc_time& t)
{
  assert(mCallback);
  return (mC.*mCallback)(value, bitMask, t, mId);
}

}

#endif
