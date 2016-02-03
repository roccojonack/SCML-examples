/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2_logging/registry.h>
#include <scml2_logging/stream_logger.h>
#include <scml2_logging/exit_logger.h>
#include <scml2_logging/stream_base.h>
#include <scml2_logging/logger_base.h>
#include <scml2_logging/severity_threshold_match.h>
#include <scml2_logging/severity.h>

#include <iostream>
#include <cstdlib>
#include <cassert>

namespace scml2 { namespace logging {

registry&
registry::
get_instance()
{
  static registry instance;
  return instance;
}

registry::
registry() :
  mExitAfterLog(false)
{
}

registry::
~registry()
{
}

void
registry::
log(const stream_base& s, const char* msg)
{
  if (s.is_enabled()) {
    LoggersConstIter it = mLoggers.begin();
    LoggersConstIter end = mLoggers.end();
    for (; it != end; ++it) {
      if ((*it)->is_enabled(s)) {
        (*it)->log(s, msg);
      }
    }
    if (mExitAfterLog) {
      exit(1); // Dietmar: shouldn't we better use abort() as it makes it easier to debug the root cause of the error?
    }
  }
}

bool
registry::
register_logger(logger_base* l)
{
  assert(l);
  if (mLoggers.insert(l).second) {
    update_streams();
    return true;
  }
  return false;
}

bool
registry::
unregister_logger(logger_base* l)
{
  if (mLoggers.erase(l) != 0) {
    update_streams();
    return true;
  }
  return false;
}

logger_base*
registry::
find_logger_by_name(const std::string& name) const
{
  LoggersConstIter it = mLoggers.begin();
  LoggersConstIter end = mLoggers.end();
  for (; it != end; ++it) {
    if ((*it)->get_name() == name) {
      return *it;
    }
  }
  return 0;
}

unsigned int
registry::
collect_loggers(std::vector<logger_base*>& l) const
{
  LoggersConstIter it = mLoggers.begin();
  LoggersConstIter end = mLoggers.end();
  for (; it != end; ++it) {
    l.push_back(*it);
  }
  return mLoggers.size();
}

void
registry::
update_streams()
{
  StreamsConstIter it = mStreams.begin();
  StreamsConstIter end = mStreams.end();
  for (; it != end; ++it) {
    (*it)->set_enabled(must_be_enabled(*(*it)));
  }
}

unsigned int
registry::
collect_streams(std::vector<stream_base*>& v) const
{
  StreamsConstIter it = mStreams.begin();
  StreamsConstIter end = mStreams.end();
  for (; it != end; ++it) {
    v.push_back(*it);
  }
  return mStreams.size();
}

void
registry::
set_exit_after_log()
{
  mExitAfterLog = true;
}

void
registry::
dump_logger_rules(std::ostream& os) const
{
  LoggersConstIter it = mLoggers.begin();
  LoggersConstIter end = mLoggers.end();
  for (; it != end; ++it) {
    (*it)->dump_rules(os);
  }
}

bool
registry::
register_stream(stream_base* s)
{
  assert(s);
  return mStreams.insert(s).second;
}

bool
registry::
unregister_stream(stream_base* s)
{
  return (mStreams.erase(s) != 0);
}

bool
registry::
must_be_enabled(const stream_base& s) const
{
  LoggersConstIter it = mLoggers.begin();
  LoggersConstIter end = mLoggers.end();
  for (; it != end; ++it) {
    if ((*it)->is_enabled(s)) {
      return true;
    }
  }
  return false;
}

unsigned int Initializer::counter = 0;
logger_base* Initializer::cerrLogger = 0;
logger_base* Initializer::exitLogger = 0;

Initializer::
Initializer()
{
  if (counter++ == 0) {
    registry& d = registry::get_instance();
    
    // Enable output to std::cerr for warnings and higher
    cerrLogger =
      new stream_logger("default_cerr_logger", std::cerr);
    d.register_logger(cerrLogger);
    cerrLogger->enable(
      match::severity_threshold_match(severity::warning().get_level()));
    
    // Exit on error and higher
    exitLogger = new exit_logger();
    d.register_logger(exitLogger);
    exitLogger->enable(
      match::severity_threshold_match(severity::error().get_level()));
  }
}

Initializer::
~Initializer()
{
  if (--counter == 0) {
    registry& d = registry::get_instance();

    d.unregister_logger(cerrLogger);
    delete cerrLogger;
    cerrLogger = 0;

    d.unregister_logger(exitLogger);
    delete exitLogger;
    exitLogger = 0;
  }
}

} }
