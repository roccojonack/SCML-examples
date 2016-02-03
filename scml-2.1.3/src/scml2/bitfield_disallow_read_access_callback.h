/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_DISALLOW_READ_ACCESS_CALLBACK_H
#define SCML2_BITFIELD_DISALLOW_READ_ACCESS_CALLBACK_H

#include <scml2/bitfield_read_callback_base.h>

#include <tlm.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT>
class bitfield_disallow_read_access_callback :
  public bitfield_read_callback_base<DT>
{
public:
  bitfield_disallow_read_access_callback(bool returnError);

  virtual bool read(DT& value, const DT& bitMask, sc_core::sc_time& t);
  virtual bool has_never_syncing_behavior() const;

private:
  bool mReturnError;
};

template <typename DT>
inline
bitfield_disallow_read_access_callback<DT>::
bitfield_disallow_read_access_callback(bool returnError) :
  bitfield_read_callback_base<DT>(
    returnError ? "<disallow read callback>" :
                  "<ignore read callback>"),
  mReturnError(returnError)
{
}

}

#endif
