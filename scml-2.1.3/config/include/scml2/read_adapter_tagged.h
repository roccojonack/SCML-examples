/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_READ_ADAPTER_TAGGED_H
#define SCML2_READ_ADAPTER_TAGGED_H

#include <scml2/streams.h>
#include <scml2_logging/stream.h>
#include <scml2/tlm2_gp_extensions.h>
#include <cassert>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename M, typename C>
class read_adapter_tagged
{
public:
  typedef typename M::data_type data_type;
  typedef bool (C::*CallbackType)(data_type& data,
                                  const data_type& byteEnables,
                                  sc_core::sc_time&,
                                  int id);

public:
  read_adapter_tagged(C& c, CallbackType cb, int id, const M& mem);

  bool operator()(data_type& data,
                  const data_type& byteEnables,
                  sc_core::sc_time& t, 
                  const tlm2_gp_extensions&);

private:
  C& mClass;
  CallbackType mCallback;
  int mId;
};

template <typename M, typename C>
inline
read_adapter_tagged<M, C>
create_read_adapter(C& c,
                    typename read_adapter_tagged<M, C>::CallbackType cb,
                    int id,
                    const M& mem)
{
  return read_adapter_tagged<M, C>(c, cb, id, mem);
}

template <typename M, typename C>
inline
read_adapter_tagged<M, C>::
read_adapter_tagged(C& c, CallbackType cb, int id, const M& mem) :
  mClass(c),
  mCallback(cb),
  mId(id)
{
  if (mem.get_size() > 1) {
    SCML2_LOG(mem.get_streams().error())
      << "read_adapter_tagged only supported for memory objects of size 1, "
      << "memory '" << mem.get_name() << "' has size " << mem.get_size()
      << std::endl;
  }
}

template <typename M, typename C>
inline
bool
read_adapter_tagged<M, C>::
operator()(data_type& data,
           const data_type& byteEnables,
           sc_core::sc_time& t, 
           const tlm2_gp_extensions&)
{
  assert(mCallback);
  return (mClass.*mCallback)(data, byteEnables, t, mId);
}

}

#endif
