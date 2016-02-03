/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_DEBUG_WRITE_CALLBACK_BASE_H
#define SCML2_BITFIELD_DEBUG_WRITE_CALLBACK_BASE_H

#include <scml2/bitfield_debug_callback_base.h>

namespace scml2 {

template <typename DT>
class bitfield_debug_write_callback_base :
  public bitfield_debug_callback_base
{
public:
  bitfield_debug_write_callback_base(const std::string& name);

  virtual bool write(const DT& value, const DT& bitMask) = 0;
};

template <typename DT>
inline
bitfield_debug_write_callback_base<DT>::
bitfield_debug_write_callback_base(const std::string& name) :
  bitfield_debug_callback_base(name)
{
}

}

#endif
