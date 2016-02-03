/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_LEVELMATCH_H
#define SCML2_LOGGING_LEVELMATCH_H

#include <scml2_logging/stream_base.h>

#include <string>

namespace scml2 { namespace logging { namespace match {

class severity_name_match
{
public:
  severity_name_match(const std::string& severityName);
  bool matches(const stream_base& s) const;
  std::string to_string() const;

private:
  const std::string mSeverityName;
};

inline
severity_name_match::
severity_name_match(const std::string& severityName) :
  mSeverityName(severityName)
{
}

inline
bool
severity_name_match::
matches(const stream_base& s) const
{
  if (s.get_severity().get_name() == mSeverityName) {
    return true;
  }
  return false;
}

inline
std::string
severity_name_match::
to_string() const
{
  return std::string("'severity' == '") + mSeverityName + "'";
}

} } }

#endif
