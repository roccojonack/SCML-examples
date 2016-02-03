/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_NAMEMATCH_H
#define SCML2_LOGGING_NAMEMATCH_H

#include <scml2_logging/stream_base.h>

#include <string>

namespace scml2 { namespace logging {
  
class logging;

namespace match {

class name_match
{
public:
  name_match(const std::string& name);
  bool matches(const stream_base& s) const;
  std::string to_string() const;

private:
  const std::string mName;
};

inline
name_match::
name_match(const std::string& name) :
  mName(name)
{
}

inline
bool
name_match::
matches(const stream_base& s) const
{
  if (s.get_name() == mName) {
    return true;
  }
  return false;
}

inline
std::string
name_match::
to_string() const
{
  return std::string("'name' == '") + mName + "'";
}

} } }

#endif
