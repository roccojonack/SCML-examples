/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_QUANTUMKEEPER_IF_H
#define SCML2_QUANTUMKEEPER_IF_H

#include <systemc>

namespace scml2 {

class quantumkeeper_if
{
public:
  virtual ~quantumkeeper_if();

  virtual void inc(const sc_core::sc_time& t) = 0;
  virtual void set(const sc_core::sc_time& t) = 0;
  virtual sc_core::sc_time get_local_time() const = 0;
};

inline
quantumkeeper_if::
~quantumkeeper_if()
{
}

}

#endif
