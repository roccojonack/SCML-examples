/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_DISALLOW_DEBUG_READ_ACCESS_CALLBACK_H
#define SCML2_BITFIELD_DISALLOW_DEBUG_READ_ACCESS_CALLBACK_H

#include <scml2/bitfield_debug_read_callback_base.h>

namespace scml2 {

template <typename DT>
class bitfield_disallow_debug_read_access_callback :
  public bitfield_debug_read_callback_base<DT>
{
public:
  bitfield_disallow_debug_read_access_callback();

  virtual bool read(DT& value, const DT& bitMask);
};

template <typename DT>
inline
bitfield_disallow_debug_read_access_callback<DT>::
bitfield_disallow_debug_read_access_callback() :
  bitfield_debug_read_callback_base<DT>("<disallow debug read callback>")
{
}

}

#endif
