/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_UNTIMED_WORD_READ_ADAPTER_H
#define SCML2_UNTIMED_WORD_READ_ADAPTER_H

#include <scml2/word_adapter_base.h>
#include <scml2/streams.h>
#include <scml2/utils.h>

#include <scml2_logging/stream.h>
#include <tlm.h>
#include <cassert>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename M, typename C>
class untimed_word_read_adapter : public word_adapter_base
{
public:
  typedef typename M::data_type data_type;
  typedef bool (C::*CallbackType)(data_type& data);

public:
  untimed_word_read_adapter(C& c, CallbackType cb, const M& mem);

  void operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

private:
  C& mClass;
  CallbackType mCallback;
};

template <typename M, typename C>
inline
untimed_word_read_adapter<M, C>
create_word_read_adapter(C& c,
                         typename untimed_word_read_adapter<M, C>::CallbackType cb,
                         const M& mem)
{
  return untimed_word_read_adapter<M, C>(c, cb, mem);
}

template <typename M, typename C>
inline
untimed_word_read_adapter<M, C>::
untimed_word_read_adapter(C& c, CallbackType cb, const M& mem) :
  word_adapter_base(sizeOf<data_type>()),
  mClass(c),
  mCallback(cb)
{
  if (mem.get_size() > 1) {
    SCML2_LOG(mem.get_streams().error())
      << "untimed_word_read_adapter only supported for memory objects of size 1, "
      << "memory '" << mem.get_name() << "' has size " << mem.get_size()
      << std::endl;
  }
}

template <typename M, typename C>
inline
void
untimed_word_read_adapter<M, C>::
operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time&)
{
  assert(trans.is_read());

  if (checkAlignedWordAccesses(trans)) {
    for (unsigned int i = 0; i < trans.get_data_length(); i += mWordSize) {
      data_type data;
      if (!(mClass.*mCallback)(data)) {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return;
      }
      to_char_array(data, trans.get_data_ptr() + i, mWordSize, 0);
    }
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
  }
}

}

#endif