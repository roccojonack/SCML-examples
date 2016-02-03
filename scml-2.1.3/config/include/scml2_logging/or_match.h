/****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_ORMATCH_H
#define SCML2_LOGGING_ORMATCH_H

#include <string>

namespace scml2 { namespace logging {
  
class stream_base;

namespace match {

template <typename Match1, typename Match2>
class or_match
{
public:
  or_match(const Match1& m1, const Match2& m2);
  bool matches(const stream_base& s) const;
  std::string to_string() const;

private:
  const Match1 mMatch1;
  const Match2 mMatch2;
};

template <typename Match1, typename Match2>
inline
or_match<Match1, Match2>
operator||(const Match1& m1, const Match2& m2)
{
  return or_match<Match1, Match2>(m1, m2);
}

template <typename Match1, typename Match2>
inline
or_match<Match1, Match2>::
or_match(const Match1& m1, const Match2& m2) :
  mMatch1(m1),
  mMatch2(m2)
{
}

template <typename Match1, typename Match2>
inline
bool
or_match<Match1, Match2>::
matches(const stream_base& s) const
{
  return mMatch1.matches(s) || mMatch2.matches(s);
}

template <typename Match1, typename Match2>
inline
std::string
or_match<Match1, Match2>::
to_string() const
{
  return "( " + mMatch1.to_string() + " || " + mMatch2.to_string() + " )";
}

} } }

#endif
