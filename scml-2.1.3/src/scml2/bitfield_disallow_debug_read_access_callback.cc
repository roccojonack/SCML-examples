/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/bitfield_disallow_debug_read_access_callback.h>

#include <scml2/utils.h>

namespace scml2 {

template <typename DT>
bool
bitfield_disallow_debug_read_access_callback<DT>::
read(DT& value, const DT&)
{
  value = 0;
  return false;
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class bitfield_disallow_debug_read_access_callback<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
