/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_SELECT_CALLBACK_BASE_H
#define SCML2_MEMORY_SELECT_CALLBACK_BASE_H

#include <scml2/resource.h>

#include <string>

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

class mappable_if;

class memory_select_callback_base : public resource
{
public:
  memory_select_callback_base(const std::string& name = "<anonymous>");
  virtual ~memory_select_callback_base();

  const std::string& get_name() const;

  virtual mappable_if* execute(tlm::tlm_generic_payload& trans) = 0;

private:
  const std::string mName;
};

inline
memory_select_callback_base::
memory_select_callback_base(const std::string& name) :
  mName(name)
{
}

inline
memory_select_callback_base::
~memory_select_callback_base()
{
}

inline
const std::string&
memory_select_callback_base::
get_name() const
{
  return mName;
}

}

#endif
