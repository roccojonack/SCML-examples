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

#include <systemc>
#include <scml2_testing/predicate.h>
#include <scml2_testing/proxy.h>
#include <scml2_testing/pin_value_proxy.h>

namespace scml2 { namespace testing {

template <typename DT>
class output_pin_proxy : public proxy< sc_core::sc_in<DT> >, public output_pin_proxy_base<DT> {
  public:
    predicate<complete, pin_value_proxy<DT>, DT> equals(DT val) {
      return predicate<complete, pin_value_proxy<DT>, null_type>(pin_value_proxy<DT>(this)).equals(val);
    }

    virtual DT get_value() const {
      return *this->target;
    }

    operator DT () const {
      return get_value(); 
    }
};


}}
