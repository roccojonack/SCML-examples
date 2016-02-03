/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_BITFIELDS_DEBUG_READ_CALLBACK_H
#define SCML2_MEMORY_BITFIELDS_DEBUG_READ_CALLBACK_H

#include <scml2/memory_bitfields_debug_callback_base.h>

#include <vector>

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

template <typename DT> class reg;
template <typename DT> class bitfield;

template <typename DT>
class memory_bitfields_debug_read_callback :
  public memory_bitfields_debug_callback_base<DT>
{
public:
  typedef typename memory_bitfields_debug_callback_base<DT>::Bitfields Bitfields;
  typedef typename memory_bitfields_debug_callback_base<DT>::BitfieldsIter BitfieldsIter;
  typedef typename memory_bitfields_debug_callback_base<DT>::BitfieldsConstIter BitfieldsConstIter;

public:
  memory_bitfields_debug_read_callback(reg<DT>& r, Bitfields& bitfields);

  virtual unsigned int execute(tlm::tlm_generic_payload& trans);
};

template <typename DT>
inline
memory_bitfields_debug_read_callback<DT>::
memory_bitfields_debug_read_callback(reg<DT>& r, Bitfields& bitfields) :
  memory_bitfields_debug_callback_base<DT>(r, bitfields)
{
}

}

#endif
