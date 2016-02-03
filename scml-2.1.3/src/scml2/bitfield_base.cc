/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/bitfield_base.h>
#include <scml2/streams.h>
#include <scml2/utils.h>

#include <scml2_logging/severity.h>

namespace scml2 {

bitfield_base::
bitfield_base(const std::string& name,
              unsigned int offset,
              unsigned int size,
              streams& streams) :
  sc_core::sc_object(name.c_str()),
  mStreams(streams),
  mOffset(offset),
  mSize(size)
{
}

bitfield_base::
~bitfield_base()
{
}

void
bitfield_base::
set_description(const std::string& d)
{
  mDescription = d;
}

const std::string&
bitfield_base::
get_description() const
{
  return mDescription;
}

bool
bitfield_base::
set_symbolic_name(const std::vector<unsigned char>& value, const std::string& name)
{
  return mSymbolicNames.set_symbolic_name(value, name);
}

unsigned int
bitfield_base::
collect_symbolic_names(SymbolicNames& symbolicNames) const
{
  return mSymbolicNames.collect_symbolic_names(symbolicNames);
}

}
