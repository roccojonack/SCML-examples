/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2_logging/stream_base.h>
#include <scml2_logging/registry.h>

namespace scml2 { namespace logging {

stream_base::
stream_base(const std::string& name, const severity& severity) :
  mName(name),
  mSeverity(severity),
  mEnabledOrRequiresInit(true),
  mRequiresInit(true),
  mStreamBuf(*this)
{
  registry::get_instance().register_stream(this);
}

stream_base::
~stream_base()
{
  registry::get_instance().unregister_stream(this);
}

void
stream_base::
initialize_enabled() const
{
  if (mRequiresInit) {
    mEnabledOrRequiresInit = registry::get_instance().must_be_enabled(*this);
    mRequiresInit = false;
  }
}

} }
