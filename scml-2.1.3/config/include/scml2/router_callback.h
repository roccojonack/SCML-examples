/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ROUTER_CALLBACK_H
#define SCML2_ROUTER_CALLBACK_H

#include <scml2/router_callback_base.h>
#include <scml2/neversync_callback.h>
#include <scml2/autosync_callback.h>
#include <scml2/selfsync_callback.h>
#include <scml2/types.h>

#include <string>
#include <cassert>

namespace scml2 {

template <typename ADAPTER>
inline
router_callback_base*
create_router_callback(ADAPTER adapter,
                       const std::string& name,
                       SyncType syncType)
{
  switch (syncType) {
  case NEVER_SYNCING:
    return new neversync_callback<ADAPTER, router_callback_base>(adapter, name);
  case AUTO_SYNCING:
    return new autosync_callback<ADAPTER, router_callback_base>(adapter, name);
  case SELF_SYNCING:
    return new selfsync_callback<ADAPTER, router_callback_base>(adapter, name);
  };
  assert(false);
  return 0;
}

}

#endif
