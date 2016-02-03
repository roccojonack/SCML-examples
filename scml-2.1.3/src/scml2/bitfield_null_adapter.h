/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_NULL_ADAPTER_H
#define SCML2_BITFIELD_NULL_ADAPTER_H

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template<typename DT>
class bitfield_null_adapter
{
public:
  bitfield_null_adapter() {
  }

  bool operator()(const DT&, const DT&, sc_core::sc_time&) {
    return true;
  }
};

}

#endif
