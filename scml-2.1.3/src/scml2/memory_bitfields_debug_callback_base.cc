/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_bitfields_debug_callback_base.h>

#include <scml2/bitfield.h>

#include <tlm.h>

namespace scml2 {

template <typename DT>
bool
memory_bitfields_debug_callback_base<DT>::
bitfieldAccessed(bitfield<DT>* b, const tlm::tlm_generic_payload& trans) const
{
  const unsigned long long lowBitAccessed = trans.get_address() * 8;
  const unsigned long long highBitAccessed =
    (trans.get_address() + trans.get_data_length()) * 8 - 1;
  const unsigned int lowBitBitfield = b->get_offset();
  const unsigned int highBitBitfield = b->get_offset() + b->get_size();

  return lowBitBitfield <= highBitAccessed && highBitBitfield >= lowBitAccessed;
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class memory_bitfields_debug_callback_base<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
