/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2_logging/exit_logger.h>
#include <scml2_logging/registry.h>

namespace scml2 { namespace logging {

exit_logger::
exit_logger() :
  logger_base("exit_logger")
{
}

void
exit_logger::
log(const stream_base&, const char*)
{
  registry::get_instance().set_exit_after_log();
}

} }
