/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_DEBUG_WRITE_ADAPTER_TAGGED_H
#define SCML2_BITFIELD_DEBUG_WRITE_ADAPTER_TAGGED_H

#include <cassert>

namespace scml2 {

template <typename DT, typename C>
class bitfield_debug_write_adapter_tagged
{
public:
  typedef bool (C::*CallbackType)(const DT& value, int id);

public:
  bitfield_debug_write_adapter_tagged(C& c, CallbackType cb, int id);

  bool operator()(const DT& value, const DT& bitMask);

private:
  C& mC;
  CallbackType mCallback;
  int mId;
};

template <typename DT, typename C>
inline
bitfield_debug_write_adapter_tagged<DT, C>
create_bitfield_debug_write_adapter(C& c,
                                    typename bitfield_debug_write_adapter_tagged<DT, C>::CallbackType cb,
                                    int id)
{
  return bitfield_debug_write_adapter_tagged<DT, C>(c, cb, id);
}

template <typename DT, typename C>
inline
bitfield_debug_write_adapter_tagged<DT, C>::
bitfield_debug_write_adapter_tagged(C& c, CallbackType cb, int id) :
  mC(c),
  mCallback(cb),
  mId(id)
{
}

template <typename DT, typename C>
inline
bool
bitfield_debug_write_adapter_tagged<DT, C>::
operator()(const DT& value, const DT&)
{
  assert(mCallback);
  return (mC.*mCallback)(value, mId);
}

}

#endif
