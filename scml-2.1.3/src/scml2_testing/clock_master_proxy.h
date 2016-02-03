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
#include <cwrscml2/clock_if.h>
#include <scml2_testing/proxy.h>

namespace scml2 { namespace testing {

class clock_master_proxy : public proxy< sc_core::sc_port<scml2::clock_if> > {
};


}}
