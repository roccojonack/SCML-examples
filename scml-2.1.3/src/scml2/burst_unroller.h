/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BURST_UNROLLER_H
#define SCML2_BURST_UNROLLER_H

namespace tlm {
  class tlm_generic_payload;
}

namespace sc_core {
  class sc_time;
}

namespace scml2 {

class burst_unroller
{
public:
  burst_unroller(unsigned int width);
  virtual ~burst_unroller();

protected:
  void unroll_transaction(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  virtual void process_unrolled_transaction(tlm::tlm_generic_payload& trans, sc_core::sc_time& t) = 0;

private:
  unsigned int mWordSize;
};

}

#endif
