/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_RULE_H
#define SCML2_LOGGING_RULE_H

#include <scml2_logging/rule_base.h>

#include <string>

namespace scml2 { namespace logging {

class stream_base;

template <typename Match>
class rule : public rule_base
{
public:
  rule(bool enableNotDisable, const Match& match);
  bool filter(const stream_base& s, bool previous) const;
  std::string to_string() const;

private:
  bool mEnableNotDisable;
  const Match mMatch;
};

template <typename Match>
inline
rule<Match>::
rule(bool enableNotDisable, const Match& match) :
  mEnableNotDisable(enableNotDisable),
  mMatch(match)
{
}

template <typename Match>
inline
bool
rule<Match>::
filter(const stream_base& s, bool previous) const
{
  if (mMatch.matches(s)) {
    return mEnableNotDisable;

  } else {
    return previous;
  }
}

template <typename Match>
inline
std::string
rule<Match>::
to_string() const
{
  if (mEnableNotDisable) {
    return std::string("enable ") + mMatch.to_string();

  } else {
    return std::string("disable ") + mMatch.to_string();
  }
}

} }

#endif
