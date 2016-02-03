/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_CALLBACK_FUNCTIONS_H
#define SCML2_BITFIELD_CALLBACK_FUNCTIONS_H

#include <scml2/bitfield_read_callback.h>
#include <scml2/bitfield_write_callback.h>
#include <scml2/bitfield_read_adapter.h>
#include <scml2/bitfield_write_adapter.h>
#include <scml2/bitfield_read_adapter_tagged.h>
#include <scml2/bitfield_write_adapter_tagged.h>
#include <scml2/bitfield_write_once_adapter.h>
#include <scml2/bitfield_untimed_read_adapter.h>
#include <scml2/bitfield_untimed_write_adapter.h>
#include <scml2/bitfield_untimed_read_adapter_tagged.h>
#include <scml2/bitfield_untimed_write_adapter_tagged.h>
#include <scml2/bitfield_mask_read_adapter.h>
#include <scml2/bitfield_mask_write_adapter.h>
#include <scml2/bitfield_mask_read_adapter_tagged.h>
#include <scml2/bitfield_mask_write_adapter_tagged.h>
#include <scml2/bitfield_untimed_mask_read_adapter.h>
#include <scml2/bitfield_untimed_mask_write_adapter.h>
#include <scml2/bitfield_untimed_mask_read_adapter_tagged.h>
#include <scml2/bitfield_untimed_mask_write_adapter_tagged.h>
#include <scml2/bitfield_disallow_read_access_callback.h>
#include <scml2/bitfield_disallow_write_access_callback.h>
#include <scml2/bitfield_on_write_adapter.h>
#include <scml2/bitfield_post_write_adapter.h>
#include <scml2/bitfield_post_write_adapter_tagged.h>
#include <scml2/bitfield_store_after_read_adapter.h>
#include <scml2/bitfield_default_read_behavior_adapter.h>
#include <scml2/bitfield_default_write_behavior_adapter.h>
#include <scml2/bitfield_null_adapter.h>
#include <scml2/bitfield_set_on_read_adapter.h>
#include <scml2/bitfield.h>
#include <scml2/streams.h>
#include <scml2/types.h>

#include <scml2_logging/stream.h>
#include <string>
#include <cassert>

#include <scml2/bitfield_callback_functions_include.h>

namespace scml2 {

template <typename DT>
inline
void
set_ignore_read_access(bitfield<DT>& bitfield)
{
  bitfield.set_read_callback(new scml2::bitfield_disallow_read_access_callback<DT>(false));
}

template <typename DT>
inline
void
set_ignore_write_access(bitfield<DT>& bitfield)
{
  bitfield.set_write_callback(new scml2::bitfield_disallow_write_access_callback<DT>(false));
}

template <typename DT>
inline
void
set_ignore_access(bitfield<DT>& bitfield)
{
  set_ignore_read_access(bitfield);
  set_ignore_write_access(bitfield);
}

template <typename DT>
inline
void
set_disallow_read_access(bitfield<DT>& bitfield)
{
  bitfield.set_read_callback(new scml2::bitfield_disallow_read_access_callback<DT>(true));
}

template <typename DT>
inline
void
set_disallow_write_access(bitfield<DT>& bitfield)
{
  bitfield.set_write_callback(new scml2::bitfield_disallow_write_access_callback<DT>(true));
}

template <typename DT>
inline
void
set_disallow_access(bitfield<DT>& bitfield)
{
  set_disallow_read_access(bitfield);
  set_disallow_write_access(bitfield);
}

template <typename DT>
inline
void
set_read_only(bitfield<DT>& bitfield)
{
  set_disallow_write_access(bitfield);
}

template <typename DT>
inline
void
set_write_only(bitfield<DT>& bitfield)
{
  set_disallow_read_access(bitfield);
}

}

#endif
