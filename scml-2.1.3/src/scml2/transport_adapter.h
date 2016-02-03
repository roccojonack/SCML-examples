/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_TRANSPORT_ADAPTER_H
#define SCML2_TRANSPORT_ADAPTER_H

#include <cassert>

namespace tlm {
  class tlm_generic_payload;
}

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename C>
class transport_adapter
{
public:
  typedef void (C::*CallbackType)(tlm::tlm_generic_payload&, sc_core::sc_time&);

public:
  transport_adapter(C& c, CallbackType cb);

  void operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

private:
  C& mClass;
  CallbackType mCallback;
};

template <typename C>
inline
transport_adapter<C>
create_transport_adapter(C& c,
                         typename transport_adapter<C>::CallbackType cb)
{
  return transport_adapter<C>(c, cb);
}

template <typename C>
inline
transport_adapter<C>::
transport_adapter(C& c, CallbackType cb) :
  mClass(c),
  mCallback(cb)
{
}

template <typename C>
inline
void
transport_adapter<C>::
operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  assert(mCallback);
  (mClass.*mCallback)(trans, t);
}

}

#endif
