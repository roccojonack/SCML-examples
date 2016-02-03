/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2_logging/stream_logger.h>
#include <scml2_logging/stream_base.h>
#include <scml2_logging/severity.h>

#include <ostream>

namespace scml2 { namespace logging {

stream_logger::
stream_logger(const std::string& name, std::ostream& s) :
  logger_base(name),
  mStream(s)
{
}

void
stream_logger::
log(const stream_base& s, const char* msg)
{
  mStream << s.get_name() << "(" << s.get_severity().get_name() << "): " << msg;
}

} }
