/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_BITFIELDS_READ_CALLBACK_H
#define SCML2_MEMORY_BITFIELDS_READ_CALLBACK_H

#include <scml2/memory_bitfields_callback_base.h>

#include <tlm.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT> class reg;
template <typename DT> class bitfield;

template <typename DT>
class memory_bitfields_read_callback :
  public memory_bitfields_callback_base<DT>
{
public:
  typedef typename memory_bitfields_callback_base<DT>::Bitfields Bitfields;
  typedef typename memory_bitfields_callback_base<DT>::BitfieldsIter BitfieldsIter;
  typedef typename memory_bitfields_callback_base<DT>::BitfieldsConstIter BitfieldsConstIter;

public:
  memory_bitfields_read_callback(reg<DT>& r, Bitfields& bitfields);

  virtual bool process_unrolled_access(DT& data,
                                       const DT& byteEnables,
                                       sc_core::sc_time& t,
                                       const tlm2_gp_extensions&);
  virtual bool has_never_syncing_behavior() const;
};

template <typename DT>
inline
memory_bitfields_read_callback<DT>::
memory_bitfields_read_callback(reg<DT>& r, Bitfields& bitfields) :
  memory_bitfields_callback_base<DT>(r, bitfields)
{
}

}

#endif
