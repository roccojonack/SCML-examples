/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/symbolic_names.h>

#include <algorithm>
#include <iterator>
#include <cassert>
#include <limits>

namespace scml2 {

symbolic_names::
~symbolic_names()
{
}

bool
symbolic_names::
set_symbolic_name(const std::vector<unsigned char>& value,
                  const std::string& name)
{
  if (mNameValueMap.find(name) != mNameValueMap.end() ||
    mValueNameMap.find(value) != mValueNameMap.end()) {
    return false;

  } else {
    mNameValueMap[name] = value;
    mValueNameMap[value] = name;
    return true;
  }
}

unsigned int
symbolic_names::
collect_symbolic_names(SymbolicNames& symbolicNames) const
{
  assert(mNameValueMap.size() == mValueNameMap.size());
  std::copy(mValueNameMap.begin(),
            mValueNameMap.end(),
            std::back_insert_iterator<SymbolicNames>(symbolicNames));
  size_t size = mValueNameMap.size();
  assert( size < std::numeric_limits<unsigned int>::max());
  return (unsigned int)size;
}

}
