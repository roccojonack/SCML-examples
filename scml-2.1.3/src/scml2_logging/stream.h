/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_STREAM_H
#define SCML2_LOGGING_STREAM_H

#include <scml2_logging/stream_base.h>

#include <ostream>
#include <string>

#define SCML2_LOG(s) \
if (!(s).is_enabled()) { \
} else \
 (s)

#define SCML2_LOG_ASSERT(a, s) \
if (!(s).is_enabled() || (a)) { \
} else \
 (s)

namespace scml2 { namespace logging {

class severity;

class stream :
  public stream_base,
  public std::ostream
{
public:
  stream(const std::string& name, const severity& severity);

private:
  // disabled
  stream();
  stream(const stream&);
  stream& operator= (const stream&);
};

inline
stream::
stream(const std::string& name, const severity& severity) :
  stream_base(name, severity),
  std::ostream(&mStreamBuf)
{
}

} }

#endif
