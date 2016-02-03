/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_DEFAULT_CALLBACK_H
#define SCML2_MEMORY_DEFAULT_CALLBACK_H

#include <scml2/memory_callback_base.h>

#include <scml2/memory_fast_access.h>
#include <scml2/memory.h>

#include <tlm.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT>
class memory_default_callback : public memory_callback_base
{
public:
  memory_default_callback(memory_fast_access<DT>& fastAccess,
                          memory<DT>& mem);

  virtual void execute(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  virtual bool has_default_behavior() const;
  virtual bool has_never_syncing_behavior() const;

protected:
  memory_fast_access<DT>& mFastAccess;
  memory<DT>& mMemory;
};

template <typename DT>
inline
memory_default_callback<DT>::
memory_default_callback(memory_fast_access<DT>& fastAccess,
                        memory<DT>& mem) :
  memory_callback_base(""),
  mFastAccess(fastAccess),
  mMemory(mem)
{
}

template <typename DT>
inline
void
memory_default_callback<DT>::
execute(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  mFastAccess.transport(trans);
  if (trans.is_read()) {
    t += mMemory.get_default_read_latency();

  } else {
    t += mMemory.get_default_write_latency();
  }
}

template <typename DT>
inline
bool
memory_default_callback<DT>::
has_default_behavior() const
{
  return true;
}

template <typename DT>
inline
bool
memory_default_callback<DT>::
has_never_syncing_behavior() const
{
  return true;
}

}

#endif
