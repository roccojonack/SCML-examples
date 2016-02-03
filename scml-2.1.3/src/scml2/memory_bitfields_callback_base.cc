/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_bitfields_callback_base.h>

#include <scml2/bitfield.h>
#include <scml2/utils.h>

#include <tlm.h>
#include <cassert>

namespace scml2 {

template <typename DT>
bool
memory_bitfields_callback_base<DT>::
bitfieldAccessed(bitfield<DT>* b,
                 const DT& byteEnables) const
{
  assert(b);
  const DT mask = get_bit_mask<DT>(b->get_size());
  return ((byteEnables >> b->get_offset()) & mask) != 0;
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class memory_bitfields_callback_base<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
