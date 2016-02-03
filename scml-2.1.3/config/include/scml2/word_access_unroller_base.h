/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_WORD_ACCESS_UNROLLER_BASE_H
#define SCML2_WORD_ACCESS_UNROLLER_BASE_H

#include <tlm.h>
#include <scml2/tlm2_gp_extensions.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT>
class word_access_unroller_base
{
public:
  virtual ~word_access_unroller_base();

  virtual bool process_unrolled_access(DT& data,
                                       const DT& byteEnables,
                                       sc_core::sc_time& t,
                                       const tlm2_gp_extensions&) = 0;
  void unroll_to_word_access(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

private:
  bool do_access(unsigned char* data,
                 unsigned int size,
                 unsigned int offset,
                 bool readNotWrite,
                 const DT& byteEnables,
                 sc_core::sc_time& t,
                 const tlm2_gp_extensions&);
};

}

#endif
