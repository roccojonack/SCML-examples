/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/word_access_unroller_base.h>
#include <scml2/utils.h>

#include <cassert>

namespace scml2 {

template <typename DT>
word_access_unroller_base<DT>::
~word_access_unroller_base()
{
}

template <typename DT>
bool
word_access_unroller_base<DT>::
do_access(unsigned char* data,
          unsigned int size,
          unsigned int offset,
          bool readNotWrite,
          const DT& byteEnables,
          sc_core::sc_time& t,
          const tlm2_gp_extensions& extensions)
{
  if (readNotWrite) {
    return process_unrolled_access(array_from_dt<DT>(data, size, offset, false),
                                   byteEnables,
                                   t,
                                   extensions);
  } else {
    // FIXME: process_unrolled_access takes non-const
    array_to_dt<DT> dataWrapper(data, size, offset);
    const DT& dataConstRef = dataWrapper;
    return process_unrolled_access(const_cast<DT&>(dataConstRef),
                                   byteEnables,
                                   t,
                                   extensions);
  }
}

template <typename DT>
void
word_access_unroller_base<DT>::
unroll_to_word_access(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  static const DT allBytesEnables = ~DT(0);

  const unsigned int wordSize = sizeOf<DT>();
  const unsigned int dataLength = trans.get_data_length();
  const unsigned char* byteEnablePtr = trans.get_byte_enable_ptr();
  const unsigned int byteEnableLength = trans.get_byte_enable_length();
  const unsigned int streamingWidth = trans.get_streaming_width();

  assert((streamingWidth >= dataLength && (trans.get_address() + dataLength) <= wordSize) ||
         (streamingWidth < dataLength && (trans.get_address() + streamingWidth) <= wordSize));

  const unsigned int address = (unsigned int)trans.get_address();
  
  tlm2_gp_extensions extensions(trans);
  if (streamingWidth >= dataLength &&
      dataLength == wordSize &&
      (!byteEnablePtr || byteEnableLength >= dataLength)) {
    // Aligned word access: No unroll needed
    if (!do_access(trans.get_data_ptr(),
                   wordSize,
                   0,
                   trans.is_read(),
                   byteEnablePtr ? array_to_dt<DT>(byteEnablePtr) : allBytesEnables,
                   t,
                   extensions)) {
      trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);

    } else {
      trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }

  } else if (dataLength % wordSize == 0 &&
             (!byteEnablePtr ||
              byteEnableLength >= dataLength ||
              byteEnableLength % wordSize == 0) &&
             (streamingWidth == wordSize ||
              streamingWidth >= dataLength)) {
    // Aligned access: streaming_width and byte enable length multiple of wordsize
    //                 --> Unroll needed, but no copy required
    for (unsigned int i = 0; i < dataLength; i += wordSize) {
      const unsigned char* currentByteEnablePtr = byteEnablePtr;
      if (currentByteEnablePtr) {
        currentByteEnablePtr += (i % byteEnableLength);
      }

      if (!do_access(trans.get_data_ptr() + i,
                     wordSize,
                     0,
                     trans.is_read(),
                     byteEnablePtr ? array_to_dt<DT>(currentByteEnablePtr) : allBytesEnables,
                     t,
                     extensions)) {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return;
      }
    }

    trans.set_response_status(tlm::TLM_OK_RESPONSE);

  } else {
    // copy data and be arrays
    for (unsigned int currentIndex = 0; currentIndex < dataLength; ) {
      const unsigned int currentDataLength = std::min(streamingWidth, dataLength - currentIndex);

      // copy byte enables
      DT currentByteEnables;
      if (byteEnablePtr) {
        currentByteEnables = 0;
        for (unsigned int i = 0; i < currentDataLength; ++i) {
          if (byteEnablePtr[(currentIndex + i) % byteEnableLength] == TLM_BYTE_ENABLED) {
            currentByteEnables |= DT(TLM_BYTE_ENABLED) << ((address + i) * 8);
          }
        }

      } else {
        currentByteEnables = get_bit_mask<DT>(8 * currentDataLength) << (8 * trans.get_address());
      }

      if (!do_access(trans.get_data_ptr() + currentIndex,
                     currentDataLength,
                     address,
                     trans.is_read(),
                     currentByteEnables,
                     t,
                     extensions)) {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return;
      }

      currentIndex += currentDataLength;
    }

    trans.set_response_status(tlm::TLM_OK_RESPONSE);
  }
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class word_access_unroller_base<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
