/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_READ_CALLBACK_BASE_H
#define SCML2_BITFIELD_READ_CALLBACK_BASE_H

#include <scml2/bitfield_callback_base.h>
#include <tlm.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT>
class bitfield_read_callback_base :
  public bitfield_callback_base
{
public:
  bitfield_read_callback_base(const std::string& name);

  virtual bool read(DT& value, const DT& bitMask, sc_core::sc_time& t) = 0;
};

template <typename DT>
inline
bitfield_read_callback_base<DT>::
bitfield_read_callback_base(const std::string& name) :
  bitfield_callback_base(name)
{
}

}

#endif
