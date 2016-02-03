/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_DEBUG_READ_CALLBACK_H
#define SCML2_BITFIELD_DEBUG_READ_CALLBACK_H

#include <scml2/bitfield_debug_read_callback_base.h>

#include <string>

namespace scml2 {

template <typename DT, typename ADAPTER>
class bitfield_debug_read_callback :
  public bitfield_debug_read_callback_base<DT>
{
public:
  bitfield_debug_read_callback(ADAPTER adapter, const std::string& name);

  virtual bool read(DT& value, const DT& bitMask);

protected:
  ADAPTER mAdapter;
};

template <typename DT, typename ADAPTER>
inline
bitfield_debug_read_callback_base<DT>*
create_bitfield_debug_read_callback(ADAPTER adapter, const std::string& name)
{
  return new bitfield_debug_read_callback<DT, ADAPTER>(adapter, name);
}

template <typename DT, typename ADAPTER>
inline
bitfield_debug_read_callback<DT, ADAPTER>::
bitfield_debug_read_callback(ADAPTER adapter, const std::string& name) :
  bitfield_debug_read_callback_base<DT>(name),
  mAdapter(adapter)
{
}

template <typename DT, typename ADAPTER>
inline
bool
bitfield_debug_read_callback<DT, ADAPTER>::
read(DT& value, const DT& bitMask)
{
  return mAdapter(value, bitMask);
}

}

#endif
