/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_NEVERSYNC_READ_CALLBACK_H
#define SCML2_BITFIELD_NEVERSYNC_READ_CALLBACK_H

#include <scml2/bitfield_read_callback_base.h>

#include <tlm.h>
#include <string>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT, typename ADAPTER>
class bitfield_neversync_read_callback :
  public bitfield_read_callback_base<DT>
{
public:
  bitfield_neversync_read_callback(ADAPTER adapter, const std::string& name);

  virtual bool read(DT& value, const DT& bitMask, sc_core::sc_time& t);
  virtual bool has_never_syncing_behavior() const;

protected:
  ADAPTER mAdapter;
};

template <typename DT, typename ADAPTER>
inline
bitfield_neversync_read_callback<DT, ADAPTER>::
bitfield_neversync_read_callback(ADAPTER adapter, const std::string& name) :
  bitfield_read_callback_base<DT>(name),
  mAdapter(adapter)
{
}

template <typename DT, typename ADAPTER>
inline
bool
bitfield_neversync_read_callback<DT, ADAPTER>::
read(DT& value, const DT& bitMask, sc_core::sc_time& t)
{
  return mAdapter(value, bitMask, t);
}

template <typename DT, typename ADAPTER>
inline
bool
bitfield_neversync_read_callback<DT, ADAPTER>::
has_never_syncing_behavior() const
{
  return true;
}

}

#endif
