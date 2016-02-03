/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_SET_ON_READ_ADAPTER_H
#define SCML2_BITFIELD_SET_ON_READ_ADAPTER_H

#include <scml2/bitfield.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT, typename ADAPTER>
class bitfield_set_on_read_adapter
{
public:
  bitfield_set_on_read_adapter(ADAPTER f, bitfield<DT>& b, DT value) : mAdapter(f), mBitfield(b), mValue(value) {
  }

  bool operator()(DT& value, const DT& bitMask, sc_core::sc_time& t) {
    if (mAdapter(value, bitMask, t)) {
      mBitfield.put(mValue, bitMask);
      return true;
    }
    return false;
  }

public:
  ADAPTER mAdapter;
  bitfield<DT>& mBitfield;
  DT mValue;
};

template <typename DT, typename ADAPTER>
inline
bitfield_set_on_read_adapter<DT, ADAPTER>
create_bitfield_set_on_read_adapter(ADAPTER f, bitfield<DT>& b, DT value)
{
  return bitfield_set_on_read_adapter<DT, ADAPTER>(f, b, value);
}

}

#endif
