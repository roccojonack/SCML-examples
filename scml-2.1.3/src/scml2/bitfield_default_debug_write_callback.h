/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_DEFAULT_DEBUG_WRITE_CALLBACK_H
#define SCML2_BITFIELD_DEFAULT_DEBUG_WRITE_CALLBACK_H

#include <scml2/bitfield_write_callback_base.h>
#include <scml2/bitfield.h>

namespace scml2 {

template <typename DT>
class bitfield_default_debug_write_callback :
  public bitfield_debug_write_callback_base<DT>
{
public:
  bitfield_default_debug_write_callback(bitfield<DT>& bitfield);

  virtual bool write(const DT& value, const DT& bitMask);
  virtual bool has_default_behavior() const;

private:
  bitfield<DT>& mBitfield;
};

template <typename DT>
inline
bitfield_default_debug_write_callback<DT>::
bitfield_default_debug_write_callback(bitfield<DT>& bitfield) :
  bitfield_debug_write_callback_base<DT>(""),
  mBitfield(bitfield)
{
}

template <typename DT>
inline
bool
bitfield_default_debug_write_callback<DT>::
write(const DT& value, const DT& bitMask)
{
  mBitfield.put_debug(value, bitMask);
  return true;
}

template <typename DT>
inline
bool
bitfield_default_debug_write_callback<DT>::
has_default_behavior() const
{
  return true;
}

}

#endif
