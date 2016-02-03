/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_AUTOSYNC_WRITE_CALLBACK_H
#define SCML2_BITFIELD_AUTOSYNC_WRITE_CALLBACK_H

#include <scml2/bitfield_write_callback_base.h>

#include <tlm.h>
#include <string>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT, typename ADAPTER>
class bitfield_autosync_write_callback :
  public bitfield_write_callback_base<DT>
{
public:
  bitfield_autosync_write_callback(ADAPTER adapter, const std::string& name);

  virtual bool write(const DT& value, const DT& bitMask, sc_core::sc_time& t);
  virtual bool has_never_syncing_behavior() const;

protected:
  ADAPTER mAdapter;
};

template <typename DT, typename ADAPTER>
inline
bitfield_autosync_write_callback<DT, ADAPTER>::
bitfield_autosync_write_callback(ADAPTER adapter, const std::string& name) :
  bitfield_write_callback_base<DT>(name),
  mAdapter(adapter)
{
}

template <typename DT, typename ADAPTER>
inline
bool
bitfield_autosync_write_callback<DT, ADAPTER>::
write(const DT& value, const DT& bitMask, sc_core::sc_time& t)
{
  if (t != sc_core::SC_ZERO_TIME) {
    sc_core::wait(t);
    t = sc_core::SC_ZERO_TIME;
  }
  bool tmp = mAdapter(value, bitMask, t);
  sc_core::wait(sc_core::SC_ZERO_TIME);
  return tmp;
}

template <typename DT, typename ADAPTER>
inline
bool
bitfield_autosync_write_callback<DT, ADAPTER>::
has_never_syncing_behavior() const
{
  return false;
}

}

#endif
