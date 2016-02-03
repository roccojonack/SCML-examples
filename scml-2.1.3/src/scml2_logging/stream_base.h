/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_STREAM_BASE_H
#define SCML2_LOGGING_STREAM_BASE_H

#include <scml2_logging/streambuf.h>
#include <scml2_logging/severity.h>

#include <string>

namespace scml2 { namespace logging {

class registry;

class stream_base
{
public:
  stream_base(const std::string& name, const severity& severity);
  virtual ~stream_base();

  std::string get_name() const;
  const severity& get_severity() const;

  bool is_enabled() const;

private:
  friend class registry;
  void set_enabled(bool enabled);
  void initialize_enabled() const;

protected:
  const std::string mName;
  const severity mSeverity;
  mutable bool mEnabledOrRequiresInit;
  mutable bool mRequiresInit;
  streambuf mStreamBuf;

  // disabled
  stream_base();
  stream_base(const stream_base&);
  stream_base& operator= (const stream_base&);
};

inline
std::string
stream_base::
get_name() const
{
  return mName;
}

inline
const severity&
stream_base::
get_severity() const
{
  return mSeverity;
}

inline
bool
stream_base::
is_enabled() const
{
  if (mEnabledOrRequiresInit) {
    initialize_enabled();
  }
  return mEnabledOrRequiresInit;
}

inline
void
stream_base::
set_enabled(bool enabled)
{
  mEnabledOrRequiresInit = enabled;
  mRequiresInit = false;
}

} }

#endif
