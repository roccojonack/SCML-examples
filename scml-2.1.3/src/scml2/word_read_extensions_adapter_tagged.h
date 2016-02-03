/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_WORD_READ_EXTENSIONS_ADAPTER_TAGGED_H
#define SCML2_WORD_READ_EXTENSIONS_ADAPTER_TAGGED_H

#include <scml2/word_adapter_base.h>
#include <scml2/streams.h>
#include <scml2/utils.h>
#include <scml2/tlm2_gp_extensions.h>

#include <scml2_logging/stream.h>
#include <tlm.h>
#include <cassert>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename M, typename C>
class word_read_extensions_adapter_tagged : public word_adapter_base
{
public:
  typedef typename M::data_type data_type;
  typedef bool (C::*CallbackType)(data_type& data,
                                  sc_core::sc_time&, 
                                  const tlm2_gp_extensions&,
                                  int id);

public:
  word_read_extensions_adapter_tagged(C& c, CallbackType cb, int id, const M& mem);

  void operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

private:
  C& mClass;
  CallbackType mCallback;
  int mId;
};

template <typename M, typename C>
inline
word_read_extensions_adapter_tagged<M, C>
create_word_read_adapter(C& c,
                         typename word_read_extensions_adapter_tagged<M, C>::CallbackType cb,
                         int id,
                         const M& mem)
{
  return word_read_extensions_adapter_tagged<M, C>(c, cb, id, mem);
}

template <typename M, typename C>
inline
word_read_extensions_adapter_tagged<M, C>::
word_read_extensions_adapter_tagged(C& c, CallbackType cb, int id, const M& mem) :
  word_adapter_base(sizeOf<data_type>()),
  mClass(c),
  mCallback(cb),
  mId(id)
{
  if (mem.get_size() > 1) {
    SCML2_LOG(mem.get_streams().error())
      << "word_read_extensions_adapter_tagged only supported for memory objects of size 1, "
      << "memory '" << mem.get_name() << "' has size " << mem.get_size()
      << std::endl;
  }
}

template <typename M, typename C>
inline
void
word_read_extensions_adapter_tagged<M, C>::
operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  assert(trans.is_read());

  if (checkAlignedWordAccesses(trans)) {
    tlm2_gp_extensions extensions(trans);
    for (unsigned int i = 0; i < trans.get_data_length(); i += mWordSize) {
      data_type data;
      if (!(mClass.*mCallback)(data, t, extensions, mId)) {
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
