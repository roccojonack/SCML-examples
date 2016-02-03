/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_NULL_DEBUG_CALLBACK_H
#define SCML2_MEMORY_NULL_DEBUG_CALLBACK_H

#include <scml2/memory_debug_callback_base.h>
#include <scml2/streams.h>

#include <scml2_logging/stream.h>

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

class memory_null_debug_callback : public memory_debug_callback_base
{
public:
  memory_null_debug_callback(memory_base& memory);
  virtual unsigned int execute(tlm::tlm_generic_payload& trans);
  virtual bool has_default_behavior() const;

private:
  memory_base& mMemory;
};

inline
memory_null_debug_callback::
memory_null_debug_callback(memory_base& memory) :
  mMemory(memory)
{
}

inline
unsigned int
memory_null_debug_callback::
execute(tlm::tlm_generic_payload&)
{
  SCML2_LOG(mMemory.get_streams().internal_error())
    << "debug callback not initialized on '" << get_name() << "'" << std::endl;
  return 0;
}

inline
bool
memory_null_debug_callback::
has_default_behavior() const
{
  return true;
}

}

#endif
