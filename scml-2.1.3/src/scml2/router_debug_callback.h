/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ROUTER_DEBUG_CALLBACK_H
#define SCML2_ROUTER_DEBUG_CALLBACK_H

#include <scml2/router_debug_callback_base.h>
#include <scml2/debug_callback.h>

#include <string>

namespace scml2 {

template <typename ADAPTER>
inline
router_debug_callback_base*
create_router_debug_callback(ADAPTER adapter, const std::string& name)
{
  return new debug_callback<ADAPTER, router_debug_callback_base>(adapter, name);
}

}

#endif
