/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/burst_unroller.h>
#include <scml2/utils.h>

#include <tlm.h>
#include <algorithm>
#include <cassert>

namespace scml2 {

burst_unroller::
burst_unroller(unsigned int width) :
  mWordSize(width)
{
}

burst_unroller::
~burst_unroller()
{
}

void
burst_unroller::
unroll_transaction(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  tlm::tlm_generic_payload unrolledTrans;
  copy_extension_pointers(trans, unrolledTrans);

  assert(trans.get_streaming_width());
  assert(!trans.get_byte_enable_ptr() || trans.get_byte_enable_length());

  const unsigned long long address = trans.get_address();
  unsigned char* dataPtr = trans.get_data_ptr();
  const unsigned int dataLength = trans.get_data_length();
  unsigned char* byteEnablePtr = trans.get_byte_enable_ptr();
  const unsigned int byteEnableLength = trans.get_byte_enable_length();
  const unsigned int streamingWidth =
    std::min(dataLength, trans.get_streaming_width());

  const unsigned int offset = address % mWordSize;

  unrolledTrans.set_command(trans.get_command());
  unrolledTrans.set_streaming_width(mWordSize);

  if ((!byteEnablePtr ||
       byteEnableLength >= dataLength ||
       // aligned access, byteEnableLength multiple of wordsize
       (!(byteEnableLength % mWordSize) && !offset)) &&
      (streamingWidth >= dataLength ||
       // aligned access, streamingWidth multiple of wordsize
       (!(streamingWidth % mWordSize) && !offset))) {
    unsigned long long currentAddress = address;
    for (unsigned int currentIndex = 0; currentIndex < dataLength; ) {
      unsigned int currentDataLength;
      if (currentIndex == 0) {
        currentDataLength =
          std::min(mWordSize - offset, dataLength);

      } else {
        currentDataLength =
          std::min(mWordSize, dataLength - currentIndex);
      }

      unrolledTrans.set_address(currentAddress);
      unrolledTrans.set_data_ptr(dataPtr + currentIndex);
      unrolledTrans.set_data_length(currentDataLength);
      if (byteEnablePtr) {
        unrolledTrans.set_byte_enable_ptr(byteEnablePtr + (currentIndex % byteEnableLength));
        unrolledTrans.set_byte_enable_length(currentDataLength);
      }
      unrolledTrans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

      process_unrolled_transaction(unrolledTrans, t);

      if (unrolledTrans.get_response_status() != tlm::TLM_OK_RESPONSE) {
        trans.set_response_status(unrolledTrans.get_response_status());
        clear_extension_pointers(unrolledTrans);
        return;
      }

      currentIndex += currentDataLength;
      if (currentIndex % streamingWidth == 0) {
        currentAddress = address;

      } else {
        currentAddress += currentDataLength;
      }
    }

  } else {
    std::vector<unsigned char> data(mWordSize);
    std::vector<unsigned char> byteEnables(mWordSize);

    unrolledTrans.set_data_ptr(&data[0]);
    unrolledTrans.set_data_length(mWordSize);
    unrolledTrans.set_byte_enable_ptr(&byteEnables[0]);
    unrolledTrans.set_byte_enable_length(mWordSize);

    const unsigned long long baseAddress = address - offset;
    unsigned long long currentAddress = baseAddress;
    unsigned int bytesLeftInStreamingBeat =
      std::min(streamingWidth, dataLength);
    for (unsigned int currentIndex = 0; currentIndex < dataLength; ) {
      unsigned int currentDataLength;
      unsigned int currentOffset;
      if (currentIndex % streamingWidth == 0) {
        currentOffset = offset;
        currentDataLength =
          std::min(mWordSize - offset, bytesLeftInStreamingBeat);

      } else {
        currentOffset = 0;
        currentDataLength = std::min(mWordSize, bytesLeftInStreamingBeat);
      }
      assert(currentDataLength);

      // copy data array
      memset(&data[0], 0, mWordSize);
      memcpy(&data[0] + currentOffset,
             dataPtr + currentIndex,
             currentDataLength);

      // copy byte enables
      memset(&byteEnables[0], TLM_BYTE_DISABLED, mWordSize);
      if (byteEnablePtr) {
        if (byteEnableLength >= dataLength) {
          memcpy(&byteEnables[0] + currentOffset,
                 byteEnablePtr + currentIndex,
                 currentDataLength);

        } else {
          for (unsigned int i = 0; i < currentDataLength; ++i) {
            byteEnables[currentOffset + i] =
              byteEnablePtr[(currentIndex + i) % byteEnableLength];
          }
        }

      } else {
        memset(&byteEnables[0] + currentOffset, TLM_BYTE_ENABLED, currentDataLength);
      }

      unrolledTrans.set_address(currentAddress);
      unrolledTrans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

      process_unrolled_transaction(unrolledTrans, t);

      if (unrolledTrans.get_response_status() != tlm::TLM_OK_RESPONSE) {
        trans.set_response_status(unrolledTrans.get_response_status());
        clear_extension_pointers(unrolledTrans);
        return;
      }

      if (trans.is_read()) {
        // copy back read data
        memcpy(dataPtr + currentIndex,
               &data[0] + currentOffset,
               currentDataLength);
      }

      currentIndex += currentDataLength;
      bytesLeftInStreamingBeat -= currentDataLength;
      if (currentIndex % streamingWidth == 0) {
        bytesLeftInStreamingBeat =
          std::min(streamingWidth, dataLength - currentIndex);
        currentAddress = baseAddress;

      } else {
        currentAddress += mWordSize;
      }
    }
  }

  trans.set_response_status(tlm::TLM_OK_RESPONSE);
  clear_extension_pointers(unrolledTrans);
}

}
