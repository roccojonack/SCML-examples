/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_DIAGNOSTICS_H
#define SCML2_LOGGING_DIAGNOSTICS_H

#include <iosfwd>
#include <string>
#include <set>
#include <vector>

namespace scml2 { namespace logging {

class stream_base;
class logger_base;

// FIXME: lock mutex?
// FIXME: add callback on changing rules
class registry
{
public:
  static registry& get_instance();

  ~registry();

  void log(const stream_base& s, const char* msg);

  bool register_logger(logger_base* l);
  bool unregister_logger(logger_base* l);
  logger_base* find_logger_by_name(const std::string& name) const;
  unsigned int collect_loggers(std::vector<logger_base*>& l) const;

  void update_streams();

  unsigned int collect_streams(std::vector<stream_base*>& s) const;

  void set_exit_after_log();

  void dump_logger_rules(std::ostream& os) const;

private:
  friend class stream_base;

  registry();

  bool register_stream(stream_base* s);
  bool unregister_stream(stream_base* s);

  bool must_be_enabled(const stream_base& s) const;

private:
  typedef std::set<stream_base*> Streams;
  typedef Streams::iterator StreamsIter;
  typedef Streams::const_iterator StreamsConstIter;
  Streams mStreams;
  typedef std::set<logger_base*> Loggers;
  typedef Loggers::iterator LoggersIter;
  typedef Loggers::const_iterator LoggersConstIter;
  Loggers mLoggers;
  bool mExitAfterLog;
};

// Initializes default loggers
static class Initializer
{
public:
  Initializer();
  ~Initializer();
private:
  static unsigned int counter;
  static logger_base* cerrLogger;
  static logger_base* exitLogger;
} initializer;

} }

#endif
