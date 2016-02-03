/*****************************************************************************
 *                   Copyright (C) 2008-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
/*
 * Modifications :
 *
 * Purpose of file : Definition of the scml_post_target_adaptor
 *
 */

#ifndef SCML_POST_TARGET_ADAPTOR_H
#define SCML_POST_TARGET_ADAPTOR_H

#include "scmlinc/scml_post_PV_transactor.h"
#include <systemc>

template <typename DT, typename AT>
class scml_post_target_adaptor : public scml_post_PV_transactor<DT, AT>
{
public:
  sc_core::sc_export<scml_post_if<DT, AT> > pIn;

public:
  SC_HAS_PROCESS(scml_post_target_adaptor);
  scml_post_target_adaptor(sc_module_name name) : 
    scml_post_PV_transactor<DT, AT>(name)
  {
    pIn(*this);
  }
};

#endif
