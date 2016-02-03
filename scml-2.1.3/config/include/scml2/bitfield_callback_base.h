/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_CALLBACK_BASE_H
#define SCML2_BITFIELD_CALLBACK_BASE_H

#include <scml2/resource.h>
#include <string>

namespace scml2 {

class bitfield_callback_base :
  public resource
{
public:
  bitfield_callback_base(const std::string& name = "<anonymous>");
  virtual ~bitfield_callback_base();

  const std::string& get_name() const;

  virtual bool has_default_behavior() const;
  virtual bool has_never_syncing_behavior() const = 0;

private:
  const std::string mName;
};

inline
bitfield_callback_base::
bitfield_callback_base(const std::string& name) :
  mName(name)
{
}

inline
bitfield_callback_base::
~bitfield_callback_base()
{
}

inline
const std::string&
bitfield_callback_base::
get_name() const
{
  return mName;
}

inline
bool
bitfield_callback_base::
has_default_behavior() const
{
  return false;
}

}

#endif
