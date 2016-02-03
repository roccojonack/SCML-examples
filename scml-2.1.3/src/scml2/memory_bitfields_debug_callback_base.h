/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_BITFIELDS_DEBUG_CALLBACK_BASE_H
#define SCML2_MEMORY_BITFIELDS_DEBUG_CALLBACK_BASE_H

#include <scml2/memory_debug_callback_base.h>

#include <vector>

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

template <typename DT> class reg;
template <typename DT> class bitfield;

template <typename DT>
class memory_bitfields_debug_callback_base :
  public memory_debug_callback_base
{
protected:
  typedef std::vector<bitfield<DT>*> Bitfields;
  typedef typename Bitfields::iterator BitfieldsIter;
  typedef typename Bitfields::const_iterator BitfieldsConstIter;

public:
  memory_bitfields_debug_callback_base(reg<DT>& r,
                                       Bitfields& bitfields);

protected:
  bool bitfieldAccessed(bitfield<DT>* b, const tlm::tlm_generic_payload& trans) const;

protected:
  reg<DT>& mRegister;
  Bitfields& mBitfields;
};

template <typename DT>
inline
memory_bitfields_debug_callback_base<DT>::
memory_bitfields_debug_callback_base(reg<DT>& r,
                                     Bitfields& bitfields) :
  mRegister(r),
  mBitfields(bitfields)
{
}

}

#endif
