/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_DMI_HANDLER_H
#define SCML2_DMI_HANDLER_H

#include <scml2/abstraction_level_switch_observer.h>
#include <scml2/utils.h>

#include <scml2_logging/stream.h>
#include <tlm.h>
#include <systemc>

#include <list>
#include <cassert>

namespace scml2 {

class dmi_handler :
  public tlm::tlm_fw_direct_mem_if<tlm::tlm_generic_payload>,
  public tlm::tlm_bw_direct_mem_if,
  public abstraction_level_switch_observer
{
private:
  // FIXME: optimize list
  typedef std::list<tlm::tlm_dmi> DmiRanges;
  typedef DmiRanges::iterator DmiRangesIter;
  typedef DmiRanges::const_iterator DmiRangesConstIter;

public:
  dmi_handler();
  ~dmi_handler();

  void set_interface(tlm::tlm_fw_direct_mem_if<tlm::tlm_generic_payload>* ifs);

  bool read(unsigned long long address,
            unsigned char* data,
            unsigned int dataLength,
            const unsigned char* byteEnables,
            unsigned int byteEnableLength,
            sc_core::sc_time& t);
  bool write(unsigned long long address,
             const unsigned char* data,
             unsigned int dataLength,
             const unsigned char* byteEnables,
             unsigned int byteEnableLength,
             sc_core::sc_time& t);
  bool read(unsigned long long address,
            unsigned char* data,
            unsigned int dataLength,
            sc_core::sc_time& t);
  bool write(unsigned long long address,
             const unsigned char* data,
             unsigned int dataLength,
             sc_core::sc_time& t);

  bool read_debug(unsigned long long address,
                  unsigned char* data,
                  unsigned int dataLength);
  bool write_debug(unsigned long long address,
                   const unsigned char* data,
                   unsigned int dataLength);

  bool transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  bool transport_debug(tlm::tlm_generic_payload& trans);

  bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData);
  void invalidate_direct_mem_ptr(sc_dt::uint64 startRange, sc_dt::uint64 endRange);

  tlm::tlm_dmi* get_read_range(unsigned long long address, unsigned int dataLength);
  tlm::tlm_dmi* get_write_range(unsigned long long address, unsigned int dataLength);

  void enable_dmi();
  void disable_dmi();
  bool is_dmi_enabled() const;

private:
  static bool contains(const tlm::tlm_dmi& dmiRange,
                       unsigned long long address);

  void invalidate(DmiRanges& ranges);

  tlm::tlm_dmi* get_read_range(unsigned long long address);
  tlm::tlm_dmi* get_write_range(unsigned long long address);
  tlm::tlm_dmi* get_read_range_slow(unsigned long long address);
  tlm::tlm_dmi* get_write_range_slow(unsigned long long address);

  tlm::tlm_dmi* load_range(unsigned long long address, bool readNotWrite);

  virtual void handle_abstraction_level_switched();

private:
  static logging::stream mError;

private:
  tlm::tlm_fw_direct_mem_if<tlm::tlm_generic_payload>* mFwDirectMemIf;
  tlm::tlm_generic_payload mTrans;
  DmiRanges mReadRanges;
  DmiRanges mWriteRanges;
  bool mDmiEnabled;
};

inline
bool
dmi_handler::
contains(const tlm::tlm_dmi& dmiRange, unsigned long long address)
{
  return (dmiRange.get_start_address() <= address &&
          dmiRange.get_end_address() >= address);
}

inline
tlm::tlm_dmi*
dmi_handler::
get_read_range(unsigned long long address)
{
  if (contains(mReadRanges.front(), address)) {
    return &mReadRanges.front();

  } else {
    return get_read_range_slow(address);
  }
}

inline
tlm::tlm_dmi*
dmi_handler::
get_read_range(unsigned long long address, unsigned int dataLength)
{
  tlm::tlm_dmi* range = get_read_range(address);
  assert(range);

  if (range->get_end_address() < (address + dataLength - 1) ||
      !range->is_read_allowed()) {
    return 0;
  }

  return range;
}

inline
tlm::tlm_dmi*
dmi_handler::
get_write_range(unsigned long long address)
{
  if (contains(mWriteRanges.front(), address)) {
    return &mWriteRanges.front();

  } else {
    return get_write_range_slow(address);
  }
}

inline
tlm::tlm_dmi*
dmi_handler::
get_write_range(unsigned long long address, unsigned int dataLength)
{
  tlm::tlm_dmi* range = get_write_range(address);
  assert(range);

  if (range->get_end_address() < (address + dataLength - 1) ||
      !range->is_write_allowed()) {
    return 0;
  }

  return range;
}

inline
bool
dmi_handler::
read(unsigned long long address,
     unsigned char* data,
     unsigned int dataLength,
     const unsigned char* byteEnables,
     unsigned int byteEnableLength,
     sc_core::sc_time& t)
{
  tlm::tlm_dmi* range = get_read_range(address, dataLength);

  if (range) {
    copy_data(data,
             range->get_dmi_ptr() + address - range->get_start_address(),
             dataLength,
             byteEnables,
             byteEnableLength);
    t += range->get_read_latency();
    return true;
  }

  return false;
}

inline
bool
dmi_handler::
write(unsigned long long address,
      const unsigned char* data,
      unsigned int dataLength,
      const unsigned char* byteEnables,
      unsigned int byteEnableLength,
      sc_core::sc_time& t)
{
  tlm::tlm_dmi* range = get_write_range(address, dataLength);

  if (range) {
    copy_data(range->get_dmi_ptr() + address - range->get_start_address(),
             data,
             dataLength,
             byteEnables,
             byteEnableLength);
    t += range->get_write_latency();
    return true;
  }

  return false;
}

inline
bool
dmi_handler::
read(unsigned long long address,
     unsigned char* data,
     unsigned int dataLength,
     sc_core::sc_time& t)
{
  return read(address, data, dataLength, 0, 0, t);
}

inline
bool
dmi_handler::
write(unsigned long long address,
      const unsigned char* data,
      unsigned int dataLength,
      sc_core::sc_time& t)
{
  return write(address, data, dataLength, 0, 0, t);
}

inline
bool
dmi_handler::
read_debug(unsigned long long address,
           unsigned char* data,
           unsigned int dataLength)
{
  tlm::tlm_dmi* range = get_read_range(address, dataLength);

  if (range) {
    copy_data(data,
              range->get_dmi_ptr() + address - range->get_start_address(),
              dataLength,
              0,
              0);
    return true;
  }

  return false;
}

inline
bool
dmi_handler::
write_debug(unsigned long long address,
            const unsigned char* data,
            unsigned int dataLength)
{
  tlm::tlm_dmi* range = get_write_range(address, dataLength);

  if (range) {
    copy_data(range->get_dmi_ptr() + address - range->get_start_address(),
              data,
              dataLength,
              0,
              0);
    return true;
  }

  return false;
}

inline
bool
dmi_handler::
transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  bool result = false;

  if (trans.get_streaming_width() >= trans.get_data_length()) {
    if (trans.is_read()) {
      result = read(trans.get_address(),
                    trans.get_data_ptr(),
                    trans.get_data_length(),
                    trans.get_byte_enable_ptr(),
                    trans.get_byte_enable_length(),
                    t);

    } else if (trans.is_write()) {
      result = write(trans.get_address(),
                     trans.get_data_ptr(),
                     trans.get_data_length(),
                     trans.get_byte_enable_ptr(),
                     trans.get_byte_enable_length(),
                     t);
    }

  } else {
    if (trans.is_read()) {
      tlm::tlm_dmi* range = get_read_range(trans.get_address(),
                                           trans.get_streaming_width());
      if (range) {
	const unsigned char* fastBackdoor =
	  range->get_dmi_ptr() + trans.get_address() - range->get_start_address();
        for (unsigned int i = 0; i < trans.get_data_length(); ++i) {
          if (!trans.get_byte_enable_ptr() ||
              trans.get_byte_enable_ptr()[i % trans.get_byte_enable_length()]) {
            trans.get_data_ptr()[i] = fastBackdoor[i % trans.get_streaming_width()];
          }
        }
        t += range->get_read_latency();
        result = true;
      }

    } else if (trans.is_write()) {
      tlm::tlm_dmi* range = get_write_range(trans.get_address(),
                                            trans.get_streaming_width());
      if (range) {
	unsigned char* fastBackdoor =
	  range->get_dmi_ptr() + trans.get_address() - range->get_start_address();
        for (unsigned int i = 0; i < trans.get_data_length(); ++i) {
          if (!trans.get_byte_enable_ptr() ||
              trans.get_byte_enable_ptr()[i % trans.get_byte_enable_length()]) {
            fastBackdoor[i % trans.get_streaming_width()] = trans.get_data_ptr()[i];
          }
        }
        t += range->get_write_latency();
        result = true;
      }
    }
  }

  if (result) {
    trans.set_dmi_allowed(true);
    trans.set_response_status(tlm::TLM_OK_RESPONSE);

  } else {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  return result;
}

inline
bool
dmi_handler::
transport_debug(tlm::tlm_generic_payload& trans)
{
  if (trans.is_read()) {
    return read_debug(trans.get_address(),
                      trans.get_data_ptr(),
                      trans.get_data_length());

  } else if (trans.is_write()) {
    return write_debug(trans.get_address(),
                       trans.get_data_ptr(),
                       trans.get_data_length());
  }

  return false;
}

inline
bool
dmi_handler::
is_dmi_enabled() const
{
  return mDmiEnabled;
}


}

#endif
