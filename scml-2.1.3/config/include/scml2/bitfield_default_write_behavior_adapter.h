/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_DEFAULT_WRITE_BEHAVIOR_ADAPTER_H
#define SCML2_BITFIELD_DEFAULT_WRITE_BEHAVIOR_ADAPTER_H

#include <scml2/bitfield.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT, typename ADAPTER>
class bitfield_default_write_behavior_adapter
{
public:
  bitfield_default_write_behavior_adapter(ADAPTER f, bitfield<DT>& b) : mAdapter(f), mBitfield(b) {
  }

  bool operator()(const DT& value, const DT& bitMask, sc_core::sc_time& t) {
    mBitfield.put(value, bitMask);
    return mAdapter(value, bitMask, t);
  }

public:
  ADAPTER mAdapter;
  bitfield<DT>& mBitfield;
};

template <typename DT, typename ADAPTER>
inline
bitfield_default_write_behavior_adapter<DT, ADAPTER>
create_bitfield_default_write_behavior_adapter(ADAPTER f, bitfield<DT>& b)
{
  return bitfield_default_write_behavior_adapter<DT, ADAPTER>(f, b);
}

}

#endif
