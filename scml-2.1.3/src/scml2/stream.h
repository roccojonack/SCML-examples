/******************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  **
 *       This software and the associated documentation are confidential     **
 *                  and proprietary to Synopsys, Inc.                        **
 *        Your use or disclosure of this software is subject                 **
 *      to the terms and conditions of a written license agreement           **
 *           between you, or your company, and Synopsys, Inc.                **
 *                                                                           **
 *****************************************************************************/
#ifndef SCML2_STREAM_H
#define SCML2_STREAM_H

#include <scml2/utils.h>
#include <scml2/severity.h>

#include <scml2_logging/stream.h>

namespace scml2 {

class stream : public logging::stream
{
public:
  explicit stream(const severity& severity);
  stream(const std::string& name, const severity& severity);
};

inline
stream::
stream(const severity& severity) :
  logging::stream(create_hierarchical_sc_name(""), severity)
{
}

inline
stream::
stream(const std::string& name, const severity& severity) :
  logging::stream(create_hierarchical_sc_name(name), severity)
{
}

}

#endif
