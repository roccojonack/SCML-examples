/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_SELFSYNC_CALLBACK_H
#define SCML2_SELFSYNC_CALLBACK_H

#include <string>

namespace tlm {
  class tlm_generic_payload;
}

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename ADAPTER, typename BASE>
class selfsync_callback :
  public BASE
{
public:
  selfsync_callback(ADAPTER adapter, const std::string& name);

  virtual void execute(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  virtual bool has_never_syncing_behavior() const;

protected:
  ADAPTER mAdapter;
};

template <typename ADAPTER, typename BASE>
inline
selfsync_callback<ADAPTER, BASE>::
selfsync_callback(ADAPTER adapter, const std::string& name) :
  BASE(name),
  mAdapter(adapter)
{
}

template <typename ADAPTER, typename BASE>
inline
void
selfsync_callback<ADAPTER, BASE>::
execute(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  mAdapter(trans, t);
}

template <typename ADAPTER, typename BASE>
inline
bool
selfsync_callback<ADAPTER, BASE>::
has_never_syncing_behavior() const
{
  return false;
}

}

#endif
