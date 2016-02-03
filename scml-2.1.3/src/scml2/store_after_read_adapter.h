/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_STORE_AFTER_READ_ADAPTER_H
#define SCML2_STORE_AFTER_READ_ADAPTER_H

#include <tlm.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename MEM, typename ADAPTER>
class store_after_read_adapter
{
public:
  store_after_read_adapter(ADAPTER f, MEM& m);

  void operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

public:
  ADAPTER mAdapter;
  MEM& mMemObject;
};

template <typename MEM, typename ADAPTER>
inline
store_after_read_adapter<MEM, ADAPTER>
create_store_after_read_adapter(ADAPTER f, MEM& m)
{
  return store_after_read_adapter<MEM, ADAPTER>(f, m);
}

template <typename MEM, typename ADAPTER>
inline
store_after_read_adapter<MEM, ADAPTER>::
store_after_read_adapter(ADAPTER f, MEM& m) :
  mAdapter(f),
  mMemObject(m)
{
}

template <typename MEM, typename ADAPTER>
inline
void
store_after_read_adapter<MEM, ADAPTER>::
operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  mAdapter(trans, t);
  if (trans.is_read() && trans.is_response_ok()) {
    mMemObject.put(trans.get_address(),
                   trans.get_data_ptr(),
                   trans.get_data_length(),
                   trans.get_byte_enable_ptr(),
                   trans.get_byte_enable_length());
  }
}

}

#endif
