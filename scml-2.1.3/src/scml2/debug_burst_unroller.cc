/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/debug_burst_unroller.h>
#include <scml2/utils.h>

#include <tlm.h>
#include <algorithm>

namespace scml2 {

debug_burst_unroller::
debug_burst_unroller(unsigned int width) :
  mWordSize(width)
{
}

debug_burst_unroller::
~debug_burst_unroller()
{
}

unsigned int
debug_burst_unroller::
unroll_debug_transaction(tlm::tlm_generic_payload& trans)
{
  tlm::tlm_generic_payload unrolledTrans;
  copy_extension_pointers(trans, unrolledTrans);

  const unsigned long long address = trans.get_address();
  unsigned char* dataPtr = trans.get_data_ptr();
  const unsigned int dataLength = trans.get_data_length();

  const unsigned int offset = address % mWordSize;

  unrolledTrans.set_command(trans.get_command());

  unsigned int result = 0;
  for (unsigned int currentIndex = 0; currentIndex < dataLength; ) {
    unsigned int currentDataLength;
    if (currentIndex == 0) {
      currentDataLength = mWordSize - offset;

    } else {
      currentDataLength = mWordSize;
    }
    currentDataLength = std::min(currentDataLength, dataLength - currentIndex);

    unrolledTrans.set_address(address + currentIndex);
    unrolledTrans.set_data_ptr(dataPtr + currentIndex);
    unrolledTrans.set_data_length(currentDataLength);

    unsigned int tmp = process_unrolled_debug_transaction(unrolledTrans);
    result += tmp;
    if (tmp < currentDataLength) {
      clear_extension_pointers(unrolledTrans);
      return result;
    }

    currentIndex += currentDataLength;
  }

  clear_extension_pointers(unrolledTrans);
  return result;
}

}
