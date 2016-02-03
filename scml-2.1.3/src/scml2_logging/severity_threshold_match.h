/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_SEVERITY_THRESHOLD_MATCH_H
#define SCML2_LOGGING_SEVERITY_THRESHOLD_MATCH_H

#include <scml2_logging/stream_base.h>

#include <sstream>
#include <string>

namespace scml2 { namespace logging { namespace match {

class severity_threshold_match
{
public:
  severity_threshold_match(unsigned int threshold);
  bool matches(const stream_base& s) const;
  std::string to_string() const;

private:
  unsigned int mThreshold;
};

inline
severity_threshold_match::
severity_threshold_match(unsigned int threshold) :
  mThreshold(threshold)
{
}

inline
bool
severity_threshold_match::
matches(const stream_base& s) const
{
  if (s.get_severity().get_level() <= mThreshold) {
    return true;
  }
  return false;
}

inline
std::string
severity_threshold_match::
to_string() const
{
  std::ostringstream ss;
  ss << "'severity' <= " << mThreshold;
  return ss.str();
}

} } }

#endif
