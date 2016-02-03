/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#pragma once

#include <scml2.h>
#include <scml2_testing/proxy.h>

namespace scml2 { namespace testing {

template <typename DT>
class input_pin_proxy : public proxy< sc_core::sc_out<DT> > {
  public:
    input_pin_proxy& operator=(const DT& value) {
      *(this->target) = value;
      return *this;
    }
};

}}
