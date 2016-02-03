/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_WORD_ADAPTER_BASE_H
#define SCML2_WORD_ADAPTER_BASE_H

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

class word_adapter_base
{
public:
  word_adapter_base(unsigned int wordSize);

  bool checkAlignedWordAccesses(tlm::tlm_generic_payload& trans);

protected:
  unsigned int mWordSize;
};

inline
word_adapter_base::
word_adapter_base(unsigned int wordSize) :
  mWordSize(wordSize)
{
}

}

#endif
