/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_NAMEPREFIXMATCH_H
#define SCML2_LOGGING_NAMEPREFIXMATCH_H

#include <scml2_logging/stream_base.h>

#include <string>

namespace scml2 { namespace logging { namespace match {

class name_prefix_match
{
public:
  name_prefix_match(const std::string& prefix);
  bool matches(const stream_base& s) const;
  std::string to_string() const;

private:
  const std::string mPrefix;
};

inline
name_prefix_match::
name_prefix_match(const std::string& prefix) :
  mPrefix(prefix)
{
}

inline
bool
name_prefix_match::
matches(const stream_base& s) const
{
  if (mPrefix.size() > s.get_name().size()) {
    return false;
  }
  if (s.get_name().compare(0, mPrefix.size(), mPrefix) == 0) {
    return true;
  }
  return false;
}

inline
std::string
name_prefix_match::
to_string() const
{
  return std::string("'name' prefix == '") + mPrefix + "'";
}

} } }

#endif
