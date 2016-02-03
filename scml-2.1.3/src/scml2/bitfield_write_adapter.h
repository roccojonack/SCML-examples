/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_WRITE_ADAPTER_H
#define SCML2_BITFIELD_WRITE_ADAPTER_H

#include <tlm.h>
#include <cassert>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT, typename C>
class bitfield_write_adapter
{
public:
  typedef bool (C::*CallbackType)(const DT& value, sc_core::sc_time& t);

public:
  bitfield_write_adapter(C& c, CallbackType cb);

  bool operator()(const DT& value, const DT& bitMask, sc_core::sc_time& t);

private:
  C& mC;
  CallbackType mCallback;
};

template <typename DT, typename C>
inline
bitfield_write_adapter<DT, C>
create_bitfield_write_adapter(C& c,
                              typename bitfield_write_adapter<DT, C>::CallbackType cb)
{
  return bitfield_write_adapter<DT, C>(c, cb);
}

template <typename DT, typename C>
inline
bitfield_write_adapter<DT, C>::
bitfield_write_adapter(C& c, CallbackType cb) :
  mC(c),
  mCallback(cb)
{
}

template <typename DT, typename C>
inline
bool
bitfield_write_adapter<DT, C>::
operator()(const DT& value, const DT&, sc_core::sc_time& t)
{
  assert(mCallback);
  return (mC.*mCallback)(value, t);
}

}

#endif
