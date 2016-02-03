/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_BITFIELDS_CALLBACK_BASE_H
#define SCML2_MEMORY_BITFIELDS_CALLBACK_BASE_H

#include <scml2/memory_callback_base.h>
#include <scml2/word_access_unroller_base.h>

#include <vector>

namespace sc_core {
  class sc_time;
}

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

template <typename DT> class reg;
template <typename DT> class bitfield;

template <typename DT>
class memory_bitfields_callback_base :
  public memory_callback_base,
  public word_access_unroller_base<DT>
{
protected:
  typedef std::vector<bitfield<DT>*> Bitfields;
  typedef typename Bitfields::iterator BitfieldsIter;
  typedef typename Bitfields::const_iterator BitfieldsConstIter;

public:
  memory_bitfields_callback_base(reg<DT>& r,
                                 Bitfields& bitfields);

  virtual void execute(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

protected:
  bool bitfieldAccessed(bitfield<DT>* b, const DT& mask) const;

protected:
  reg<DT>& mRegister;
  Bitfields& mBitfields;
};

template <typename DT>
inline
memory_bitfields_callback_base<DT>::
memory_bitfields_callback_base(reg<DT>& r,
                               Bitfields& bitfields) :
  memory_callback_base(""),
  word_access_unroller_base<DT>(),
  mRegister(r),
  mBitfields(bitfields)
{
}

template <typename DT>
inline
void
memory_bitfields_callback_base<DT>::
execute(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  this->unroll_to_word_access(trans, t);
}

}

#endif
