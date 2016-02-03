/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_ON_WRITE_ADAPTER_H
#define SCML2_BITFIELD_ON_WRITE_ADAPTER_H

#include <scml2/bitfield.h>
#include <scml2/memory_behavior_functions.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT, typename ADAPTER, template<typename> class FUNCTOR, bool POST_WRITE>
class bitfield_on_write_adapter
{
public:
  bitfield_on_write_adapter(ADAPTER f, bitfield<DT>& b) : mAdapter(f), mBitfield(b) {
  }

  bool operator()(const DT& data, const DT& bitMask, sc_core::sc_time& t) {
    if (!POST_WRITE) {
      if (!mAdapter(data, bitMask, t)) {
        return false;
      }
    }

    FUNCTOR<DT>()(mBitfield, data, bitMask);

    if (POST_WRITE) {
      return mAdapter(data, bitMask, t);
    }

    return true;
  }

public:
  ADAPTER mAdapter;
  bitfield<DT>& mBitfield;
  DT mValue;
};

#define SCML2_DEFINE_BITFIELD_ON_WRITE_ADAPTER(function) \
  template<typename DT> \
  struct bitfield_##function##_functor { \
    void operator()(bitfield<DT>& object, const DT& data, const DT& mask) const { \
      function(object, data, mask); \
    } \
  }; \
  \
  template <bool POST_WRITE, typename DT, typename ADAPTER> \
  inline \
  bitfield_on_write_adapter<DT, ADAPTER, bitfield_##function##_functor, POST_WRITE> \
  create_bitfield_##function##_adapter(ADAPTER f, bitfield<DT>& b) \
  {\
    return bitfield_on_write_adapter<DT, ADAPTER, bitfield_##function##_functor, POST_WRITE>(f, b); \
  }

SCML2_DEFINE_BITFIELD_ON_WRITE_ADAPTER(clear_on_write_0)
SCML2_DEFINE_BITFIELD_ON_WRITE_ADAPTER(clear_on_write_1)
SCML2_DEFINE_BITFIELD_ON_WRITE_ADAPTER(set_on_write_0)
SCML2_DEFINE_BITFIELD_ON_WRITE_ADAPTER(set_on_write_1)

}

#endif
