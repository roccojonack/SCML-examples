/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_bitfields_read_callback.h>

#include <scml2/reg.h>
#include <scml2/bitfield.h>
#include <scml2/utils.h>

#include <tlm.h>

namespace scml2 {

template <typename DT>
bool
memory_bitfields_read_callback<DT>::
has_never_syncing_behavior() const
{
  BitfieldsIter it = this->mBitfields.begin();
  BitfieldsConstIter end = this->mBitfields.end();

  for (; it != end; ++it) {
    if ((*it)->has_never_syncing_read_behavior()) {
      return true;
    }
  }
  return false;
}

template <typename DT>
bool
memory_bitfields_read_callback<DT>::
process_unrolled_access(DT& data,
                        const DT& byteEnables,
                        sc_core::sc_time& t, const tlm2_gp_extensions&)
{
  BitfieldsIter it = this->mBitfields.begin();
  BitfieldsConstIter end = this->mBitfields.end();

  DT readData = this->mRegister.get();
  for (; it != end; ++it) {
    if (!(*it)->has_default_read_behavior() &&
        this->bitfieldAccessed(*it, byteEnables)) {
      DT bitfieldData = 0;
      if (!(*it)->get_with_triggering_callbacks(bitfieldData,
                                                extract_bits<DT>(byteEnables,
                                                                 (*it)->get_size(),
                                                                 (*it)->get_offset()),
                                                t)) {
        return false;
      }
      readData = insert_bits(readData,
                             bitfieldData,
                             (*it)->get_size(),
                             (*it)->get_offset());
    }
  }

  data = readData & byteEnables;

  return true;
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class memory_bitfields_read_callback<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
