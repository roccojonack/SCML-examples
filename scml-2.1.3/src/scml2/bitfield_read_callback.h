/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_READ_CALLBACK_H
#define SCML2_BITFIELD_READ_CALLBACK_H

#include <scml2/bitfield_neversync_read_callback.h>
#include <scml2/bitfield_autosync_read_callback.h>
#include <scml2/bitfield_selfsync_read_callback.h>

#include <scml2/types.h>

#include <string>
#include <cassert>

namespace scml2 {

template <typename DT> class bitfield_read_callback_base;

template <typename DT, typename ADAPTER>
inline
bitfield_read_callback_base<DT>*
create_bitfield_read_callback(ADAPTER adapter,
                              const std::string& name,
                              SyncType syncType)
{
  switch (syncType) {
  case NEVER_SYNCING:
    return new bitfield_neversync_read_callback<DT, ADAPTER>(adapter, name);
  case AUTO_SYNCING:
    return new bitfield_autosync_read_callback<DT, ADAPTER>(adapter, name);
  case SELF_SYNCING:
    return new bitfield_selfsync_read_callback<DT, ADAPTER>(adapter, name);
  };
  assert(false);
  return 0;
}

}

#endif
