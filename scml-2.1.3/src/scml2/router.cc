/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/router.h>
#include <scml2/utils.h>

namespace scml2 {

template <typename DT>
router<DT>::
router(const std::string& name,
       unsigned long long size) :
  router_base(name, size, sizeOf<DT>())
{
}

template <typename DT>
router<DT>::
~router()
{
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class router<type >;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
