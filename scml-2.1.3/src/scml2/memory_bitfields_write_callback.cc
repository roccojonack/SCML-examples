/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_bitfields_write_callback.h>

#include <scml2/reg.h>
#include <scml2/bitfield.h>
#include <scml2/utils.h>

#include <tlm.h>

namespace scml2 {

template <typename DT>
bool
memory_bitfields_write_callback<DT>::
has_never_syncing_behavior() const
{
  BitfieldsIter it = this->mBitfields.begin();
  BitfieldsConstIter end = this->mBitfields.end();

  for (; it != end; ++it) {
    if ((*it)->has_never_syncing_write_behavior()) {
      return true;
    }
  }
  return false;
}

template <typename DT>
bool
memory_bitfields_write_callback<DT>::
process_unrolled_access(DT& data,
                        const DT& byteEnables,
                        sc_core::sc_time& t, const tlm2_gp_extensions&)
{
  BitfieldsIter it = this->mBitfields.begin();
  BitfieldsConstIter end = this->mBitfields.end();

  const DT writeData = (this->mRegister.get_debug() & ~byteEnables) | (data & byteEnables);
  DT writeMask = 0;
  for (; it != end; ++it) {
    if (!(*it)->has_default_write_behavior() &&
        this->bitfieldAccessed(*it, byteEnables)) {
      // data passed to callback (writeData) should also contain data for disabled bits
      // for backwards compatibility of callbacks without bitMask
      if (!(*it)->put_with_triggering_callbacks(extract_bits<DT>(writeData,
                                                                 (*it)->get_size(),
                                                                 (*it)->get_offset()),
                                                extract_bits<DT>(byteEnables,
                                                                 (*it)->get_size(),
                                                                 (*it)->get_offset()),
                                                t)) {
        return false;
      }
      writeMask = insert_bits<DT>(writeMask,
                                  get_bit_mask<DT>((*it)->get_size()),
                                  (*it)->get_size(),
                                  (*it)->get_offset());
    }
  }

  const DT updatedData = this->mRegister.get_debug();
  this->mRegister.put((writeData & ~writeMask) | (updatedData & writeMask));

  return true;
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class memory_bitfields_write_callback<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
