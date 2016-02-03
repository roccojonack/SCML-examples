/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <cassert>

#ifndef SCML2_DEBUG_TRANSPORT_ADAPTER_H
#define SCML2_DEBUG_TRANSPORT_ADAPTER_H

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

template <typename C>
class debug_transport_adapter
{
public:
  typedef unsigned int (C::*CallbackType)(tlm::tlm_generic_payload&);

public:
  debug_transport_adapter(C& c, CallbackType cb);

  unsigned int operator()(tlm::tlm_generic_payload& trans);

private:
  C& mClass;
  CallbackType mCallback;
};

template <typename C>
inline
debug_transport_adapter<C>
create_debug_transport_adapter(C& c,
                               typename debug_transport_adapter<C>::CallbackType cb)
{
  return debug_transport_adapter<C>(c, cb);
}

template <typename C>
inline
debug_transport_adapter<C>::
debug_transport_adapter(C& c, CallbackType cb) :
  mClass(c),
  mCallback(cb)
{
}

template <typename C>
inline
unsigned int
debug_transport_adapter<C>::
operator()(tlm::tlm_generic_payload& trans)
{
  assert(mCallback);
  return (mClass.*mCallback)(trans);
}

}

#endif
