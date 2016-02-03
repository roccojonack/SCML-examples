/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_DEBUG_BURST_UNROLLER_H
#define SCML2_DEBUG_BURST_UNROLLER_H

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

class debug_burst_unroller
{
public:
  debug_burst_unroller(unsigned int width);
  virtual ~debug_burst_unroller();

protected:
  unsigned int unroll_debug_transaction(tlm::tlm_generic_payload& trans);
  virtual unsigned int process_unrolled_debug_transaction(tlm::tlm_generic_payload& trans) = 0;

private:
  unsigned int mWordSize;
};

}

#endif
