/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/word_adapter_base.h>

#include <tlm.h>

namespace scml2 {

bool
word_adapter_base::
checkAlignedWordAccesses(tlm::tlm_generic_payload& trans)
{
  if (trans.get_address() % mWordSize) {
    trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
    return false;
  }

  if (trans.get_data_length() % mWordSize ||
      (trans.get_streaming_width() < trans.get_data_length() &&
       trans.get_streaming_width() != mWordSize)) {
    trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
    return false;
  }

  if (trans.get_byte_enable_ptr()) {
    for (unsigned int i = 0; i < trans.get_byte_enable_length(); ++i) {
      if (trans.get_byte_enable_ptr()[i] == TLM_BYTE_DISABLED) {
        trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
        return false;
      }
    }
  }

  return true;
}

}
