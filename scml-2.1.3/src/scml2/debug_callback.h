/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_DEBUG_CALLBACK_H
#define SCML2_DEBUG_CALLBACK_H

#include <string>

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

template <typename ADAPTER, typename BASE>
class debug_callback :
  public BASE
{
public:
  debug_callback(ADAPTER adapter, const std::string& name);

  virtual unsigned int execute(tlm::tlm_generic_payload& trans);

protected:
  ADAPTER mAdapter;
};

template <typename ADAPTER, typename BASE>
inline
debug_callback<ADAPTER, BASE>::
debug_callback(ADAPTER adapter, const std::string& name) :
  BASE(name),
  mAdapter(adapter)
{
}

template <typename ADAPTER, typename BASE>
inline
unsigned int
debug_callback<ADAPTER, BASE>::
execute(tlm::tlm_generic_payload& trans)
{
  return mAdapter(trans);
}

}

#endif
