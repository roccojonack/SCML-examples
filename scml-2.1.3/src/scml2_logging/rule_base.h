/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_RULEBASE_H
#define SCML2_LOGGING_RULEBASE_H

#include <string>

namespace scml2 { namespace logging {

class stream_base;

class rule_base
{
public:
  virtual ~rule_base() {}
  virtual bool filter(const stream_base& s, bool previous) const = 0;
  virtual std::string to_string() const = 0;
};

} }

#endif
