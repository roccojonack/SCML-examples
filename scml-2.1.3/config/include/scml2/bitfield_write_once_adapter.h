/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_WRITE_ONCE_ADAPTER_H
#define SCML2_BITFIELD_WRITE_ONCE_ADAPTER_H

#include <scml2/bitfield.h>
#include <scml2/write_once_state.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT, typename ADAPTER, bool RETURN_ERROR, bool POST_WRITE>
class bitfield_write_once_adapter
{
public:
  bitfield_write_once_adapter(ADAPTER f, bitfield<DT>& b) : mAdapter(f), mBitfield(b) {
    mWriteOnceState = new write_once_state();
    mWriteOnceState->ref();
  }

  bitfield_write_once_adapter(const bitfield_write_once_adapter& o) : mAdapter(o.mAdapter), mBitfield(o.mBitfield) {
    mWriteOnceState = o.mWriteOnceState;
    mWriteOnceState->ref();
  }

  ~bitfield_write_once_adapter() {
    mWriteOnceState->unref();
  }

  bool operator()(const DT& data, const DT& bitMask, sc_core::sc_time& t) {
    if (mWriteOnceState->is_writable()) {
      mWriteOnceState->set_writable(false);
      return mAdapter(data, bitMask, t);
    } else {
      return !RETURN_ERROR;
    }
  }

  write_once_state* get_state() const {
    return mWriteOnceState;
  }

public:
  ADAPTER mAdapter;
  bitfield<DT>& mBitfield;
  DT mValue;
  write_once_state* mWriteOnceState;
};

template <bool POST_WRITE, typename DT, typename ADAPTER>
inline
bitfield_write_once_adapter<DT, ADAPTER, false, POST_WRITE>
create_bitfield_write_once_ignore_adapter(ADAPTER f, bitfield<DT>& b, write_once_state** state)
{
  bitfield_write_once_adapter<DT, ADAPTER, false, POST_WRITE> result(f, b);
  *state = result.get_state();
  return result;
}

template <bool POST_WRITE, typename DT, typename ADAPTER>
inline
bitfield_write_once_adapter<DT, ADAPTER, true, POST_WRITE>
create_bitfield_write_once_error_adapter(ADAPTER f, bitfield<DT>& b, write_once_state** state)
{
  bitfield_write_once_adapter<DT, ADAPTER, true, POST_WRITE> result(f, b);
  *state = result.get_state();
  return result;
}

}

#endif
