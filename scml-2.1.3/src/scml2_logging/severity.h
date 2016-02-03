/****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_SEVERITY_H
#define SCML2_LOGGING_SEVERITY_H

#include <string>

namespace scml2 { namespace logging {

class severity
{
public:
  static severity internal_error();
  static severity error();
  static severity warning();
  static severity note();
  static severity debug();

public:
  severity(const std::string& name, unsigned int severity);
  severity(const severity&);

  const std::string& get_name() const;
  unsigned int get_level() const;

  friend bool operator<(const severity& l, const severity& r);

private:
  const std::string mName;
  const unsigned int mLevel;

  // disabled
  severity();
  severity& operator= (const severity&);
};

inline
bool
operator<(const severity& l, const severity& r)
{
  return l.mLevel < r.mLevel;
}

inline
severity
severity::internal_error()
{
  return severity("internal_error", 5);
}

inline
severity
severity::error()
{
  return severity("error", 10);
}

inline
severity
severity::warning()
{
  return severity("warning", 100);
}

inline
severity
severity::note()
{
  return severity("note", 1000);
}

inline
severity
severity::debug()
{
  return severity("debug", 10000);
}

inline
severity::
severity(const std::string& name, unsigned int severity) :
  mName(name),
  mLevel(severity)
{
}

inline
severity::
severity(const severity& rhs) :
  mName(rhs.mName),
  mLevel(rhs.mLevel)
{
}

inline
const std::string&
severity::
get_name() const
{
  return mName;
}

inline
unsigned int
severity::
get_level() const
{
  return mLevel;
}

} }

#endif
