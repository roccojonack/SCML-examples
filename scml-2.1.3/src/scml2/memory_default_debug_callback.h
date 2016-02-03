/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_DEFAULT_DEBUG_CALLBACK_H
#define SCML2_MEMORY_DEFAULT_DEBUG_CALLBACK_H

#include <scml2/memory_debug_callback_base.h>
#include <scml2/memory_fast_access.h>

#include <tlm.h>

namespace scml2 {

template <typename DT>
class memory_default_debug_callback : public memory_debug_callback_base
{
public:
  memory_default_debug_callback(memory_fast_access<DT>& fastAccess);

  virtual unsigned int execute(tlm::tlm_generic_payload& trans);
  virtual bool has_default_behavior() const;

protected:
  memory_fast_access<DT>& mFastAccess;
};

template <typename DT>
inline
memory_default_debug_callback<DT>::
memory_default_debug_callback(memory_fast_access<DT>& fastAccess) :
  memory_debug_callback_base(""),
  mFastAccess(fastAccess)
{
}

template <typename DT>
inline
unsigned int
memory_default_debug_callback<DT>::
execute(tlm::tlm_generic_payload& trans)
{
  mFastAccess.transport_debug(trans);
  return trans.get_data_length();
}

template <typename DT>
inline
bool
memory_default_debug_callback<DT>::
has_default_behavior() const
{
  return true;
}

}

#endif
