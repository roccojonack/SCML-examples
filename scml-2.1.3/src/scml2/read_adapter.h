/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_READ_ADAPTER_H
#define SCML2_READ_ADAPTER_H

#include <scml2/streams.h>
#include <scml2_logging/stream.h>
#include <scml2/tlm2_gp_extensions.h>
#include <cassert>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename M, typename C>
class read_adapter
{
public:
  typedef typename M::data_type data_type;
  typedef bool (C::*CallbackType)(data_type& data,
                                  const data_type& byteEnables,
                                  sc_core::sc_time&);

public:
  read_adapter(C& c, CallbackType cb, const M& mem);

  bool operator()(data_type& data,
                  const data_type& byteEnables,
                  sc_core::sc_time& t,
                  const tlm2_gp_extensions&);

private:
  C& mClass;
  CallbackType mCallback;
};

template <typename M, typename C>
inline
read_adapter<M, C>
create_read_adapter(C& c,
                    typename read_adapter<M, C>::CallbackType cb,
                    const M& mem)
{
  return read_adapter<M, C>(c, cb, mem);
}

template <typename M, typename C>
inline
read_adapter<M, C>::
read_adapter(C& c, CallbackType cb, const M& mem) :
  mClass(c),
  mCallback(cb)
{
  if (mem.get_size() > 1) {
    SCML2_LOG(mem.get_streams().error())
      << "read_adapter only supported for memory objects of size 1, "
      << "memory '" << mem.get_name() << "' has size " << mem.get_size()
      << std::endl;
  }
}

template <typename M, typename C>
inline
bool
read_adapter<M, C>::
operator()(data_type& data,
           const data_type& byteEnables,
           sc_core::sc_time& t, 
           const tlm2_gp_extensions&)
{
  assert(mCallback);
  return (mClass.*mCallback)(data, byteEnables, t);
}

}

#endif
