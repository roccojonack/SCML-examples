/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_bitfields_debug_write_callback.h>

#include <scml2/reg.h>
#include <scml2/bitfield.h>
#include <scml2/utils.h>

#include <tlm.h>

namespace scml2 {

template <typename DT>
unsigned int
memory_bitfields_debug_write_callback<DT>::
execute(tlm::tlm_generic_payload& trans)
{
  BitfieldsIter it = this->mBitfields.begin();
  BitfieldsConstIter end = this->mBitfields.end();

  DT data;
  from_char_array(trans.get_data_ptr(),
                  data,
                  trans.get_data_length(),
                  0);
  const DT byteEnables =
    get_bit_mask<DT>(trans.get_data_length() * 8) << trans.get_address() * 8;
  const DT writeData = (this->mRegister.get_debug() & ~byteEnables) | (data & byteEnables);
  DT writeMask = 0;
  for (; it != end; ++it) {
    if (!(*it)->has_default_debug_write_behavior() &&
        this->bitfieldAccessed(*it, trans)) {
      // data passed to callback (writeData) should also contain data for disabled bits
      // for backwards compatibility of callbacks without bitMask
      if (!(*it)->put_debug_with_triggering_callbacks(extract_bits<DT>(writeData,
                                                                       (*it)->get_size(),
                                                                       (*it)->get_offset()),
                                                      extract_bits<DT>(byteEnables,
                                                                       (*it)->get_size(),
                                                                       (*it)->get_offset()))) {
        return 0;
      }
      writeMask = insert_bits<DT>(writeMask,
                                  get_bit_mask<DT>((*it)->get_size()),
                                  (*it)->get_size(),
                                  (*it)->get_offset());
    }
  }

  const DT updatedData = this->mRegister.get_debug();
  this->mRegister.put_debug((writeData & ~writeMask) | (updatedData & writeMask));

  return sizeOf<DT>();
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class memory_bitfields_debug_write_callback<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
