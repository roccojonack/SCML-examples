/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_LOGGER_LOGGER_H
#define SCML2_LOGGING_LOGGER_LOGGER_H

#include <scml2_logging/rule.h>

#include <iosfwd>
#include <list>
#include <string>

namespace scml2 { namespace logging {

class stream_base;

class logger_base
{
public:
  logger_base(const std::string& name);
  virtual ~logger_base();

  const std::string& get_name() const;

  void set_enable(bool enable);
  template <typename Match> const rule_base* enable(const Match& m);
  template <typename Match> const rule_base* disable(const Match& m);
  void add_rule(const rule_base* rule);
  bool remove_rule(const rule_base* rule);
  void clear_rules();
  void dump_rules(std::ostream& os) const;

  bool is_enabled(const stream_base& s) const;

  virtual void log(const stream_base& q, const char* msg) = 0;

private:
  void update_streams() const;

private:
  const std::string mName;
  bool mEnabled;
  typedef std::list<const rule_base*> Rules;
  typedef Rules::iterator RulesIter;
  typedef Rules::const_iterator RulesConstIter;
  Rules mRules;
};

inline
const std::string&
logger_base::
get_name() const
{
  return mName;
}

template <typename Match>
inline
const rule_base*
logger_base::
enable(const Match& m)
{
  const rule_base* r = new rule<Match>(true, m);
  add_rule(r);
  return r;
}

template <typename Match>
inline
const rule_base*
logger_base::
disable(const Match& m)
{
  const rule_base* r = new rule<Match>(false, m);
  add_rule(r);
  return r;
}

} }

#endif
