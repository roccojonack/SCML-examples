/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_bitfields_debug_read_callback.h>

#include <scml2/reg.h>
#include <scml2/bitfield.h>
#include <scml2/utils.h>

#include <tlm.h>

namespace scml2 {

template <typename DT>
unsigned int
memory_bitfields_debug_read_callback<DT>::
execute(tlm::tlm_generic_payload& trans)
{
  BitfieldsIter it = this->mBitfields.begin();
  BitfieldsConstIter end = this->mBitfields.end();

  const DT byteEnables =
    get_bit_mask<DT>(trans.get_data_length() * 8) << trans.get_address() * 8;
  DT readData = this->mRegister.get_debug();
  for (; it != end; ++it) {
    if (!(*it)->has_default_debug_read_behavior() &&
        this->bitfieldAccessed(*it, trans)) {
      DT bitfieldData = 0;
      if (!(*it)->get_debug_with_triggering_callbacks(bitfieldData,
                                                      extract_bits<DT>(byteEnables,
                                                                       (*it)->get_size(),
                                                                       (*it)->get_offset()))) {
        return 0;
      }
      readData = insert_bits(readData,
                             bitfieldData,
                             (*it)->get_size(),
                             (*it)->get_offset());
    }
  }

  readData &= byteEnables;
  to_char_array(readData >> (trans.get_address() * 8),
                trans.get_data_ptr(),
                trans.get_data_length(),
                0);

  return sizeOf<DT>();
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class memory_bitfields_debug_read_callback<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
