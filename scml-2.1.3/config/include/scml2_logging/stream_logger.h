/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_STREAMLOGGER_H
#define SCML2_LOGGING_STREAMLOGGER_H

#include <scml2_logging/logger_base.h>

#include <iosfwd>
#include <string>

namespace scml2 { namespace logging {

class stream_base;

class stream_logger : public logger_base
{
public:
  stream_logger(const std::string& name, std::ostream& s);
  void log(const stream_base& s, const char* msg);

private:
  std::ostream& mStream;
};

} }

#endif
