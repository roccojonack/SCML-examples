/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include "reset_trigger.h"

// dependency inversion pattern: scml2 must not depend on cwrscml2
namespace scml2 {
  void (*register_reset_trigger_cb)(reset_trigger_base*) = 0;
  void (*unregister_reset_trigger_cb)(reset_trigger_base*) = 0;
}

scml2::reset_trigger_base::reset_trigger_base(const std::string& name, const std::string& description)
: mName(name), mDescription(description)
{
  if (register_reset_trigger_cb != 0) {
    register_reset_trigger_cb(this);
  }
}

scml2::reset_trigger_base::~reset_trigger_base()
{
  if (unregister_reset_trigger_cb != 0) {
    unregister_reset_trigger_cb(this);
  }
}
