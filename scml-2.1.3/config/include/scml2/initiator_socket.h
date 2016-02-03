/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_INITIATOR_SOCKET_H
#define SCML2_INITIATOR_SOCKET_H

#include <scml2/mappable_if.h>
#include <scml2/dmi_handler.h>
#include <scml2/utils.h>
#include <scml2/quantumkeeper_if.h>
#include <scml2/quantumkeeper_wrapper.h>

#include <scml2_logging/stream.h>
#include <scml2_logging/severity.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm.h>
#include <systemc>
#include <string>
#include <set>
#include <vector>
#include <cassert>

namespace scml2 {

template <unsigned int BUSWIDTH>
class initiator_socket :
  public mappable_if,
  public tlm_utils::simple_initiator_socket<initiator_socket<BUSWIDTH>, BUSWIDTH>
{
public:
  typedef tlm_utils::simple_initiator_socket<initiator_socket<BUSWIDTH>, BUSWIDTH> base_type;

private:
  template <unsigned int WORDSIZE> struct WordSizeToDT { char dummy[WORDSIZE]; };
  // FIXME: workaround for windows compiler bug
  template <typename T> struct SizeOfBits { enum { result = SizeOf<T>::result * 8 }; };

public:
  initiator_socket();
  explicit initiator_socket(const char* n);
  ~initiator_socket();

  void end_of_elaboration();

  template <typename T> void set_quantumkeeper(T& quantumKeeper);
  void set_endianness(tlm::tlm_endianness endianness);

  template <typename DT> bool read(unsigned long long address, DT& data);
  template <typename DT> bool write(unsigned long long address, const DT& data);
  template <typename DT> bool read(unsigned long long address, DT* data, unsigned int count);
  template <typename DT> bool write(unsigned long long address, const DT* data, unsigned int count);
  template <typename DT> bool read(unsigned long long address, sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count);
  template <typename DT> bool write(unsigned long long address, const sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count);

  template <typename DT> bool read(unsigned long long address, DT& data, sc_core::sc_time& t);
  template <typename DT> bool write(unsigned long long address, const DT& data, sc_core::sc_time& t);
  template <typename DT> bool read(unsigned long long address, DT* data, unsigned int count, sc_core::sc_time& t);
  template <typename DT> bool write(unsigned long long address, const DT* data, unsigned int count, sc_core::sc_time& t);
  template <typename DT> bool read(unsigned long long address, sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count, sc_core::sc_time& t);
  template <typename DT> bool write(unsigned long long address, const sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count, sc_core::sc_time& t);

  template <typename DT> bool read_debug(unsigned long long address, DT& data);
  template <typename DT> bool write_debug(unsigned long long address, const DT& data);
  template <typename DT> bool read_debug(unsigned long long address, DT* data, unsigned int count);
  template <typename DT> bool write_debug(unsigned long long address, const DT* data, unsigned int count);
  template <typename DT> bool read_debug(unsigned long long address, sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count);
  template <typename DT> bool write_debug(unsigned long long address, const sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count);

  void enable_dmi();
  void disable_dmi();
  bool is_dmi_enabled() const;

  // mappable_if
  virtual std::string get_mapped_name() const;
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);
  virtual void register_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface);
  virtual void unregister_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface);

  tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans,
                                     tlm::tlm_phase& phase,
                                     sc_core::sc_time& t);
  typedef tlm::tlm_bw_nonblocking_transport_if<tlm::tlm_generic_payload, tlm::tlm_phase> BwTransportIf;
  virtual void register_bw_transport_if(BwTransportIf* bwInterface);
  virtual void unregister_bw_transport_if(BwTransportIf* bwInterface);

private:
  template <unsigned int WORDSIZE> bool read(unsigned long long address, unsigned char* data, unsigned int count);
  template <unsigned int WORDSIZE> bool write(unsigned long long address, const unsigned char* data, unsigned int count);
  template <unsigned int WORDSIZE> bool read(unsigned long long address, unsigned char* data, unsigned int count, sc_core::sc_time& t);
  template <unsigned int WORDSIZE> bool write(unsigned long long address, const unsigned char* data, unsigned int count, sc_core::sc_time& t);
  template <unsigned int WORDSIZE> unsigned int read_debug(unsigned long long address, unsigned char* data, unsigned int count);
  template <unsigned int WORDSIZE> unsigned int write_debug(unsigned long long address, const unsigned char* data, unsigned int count);

  static bool isAlignedAccess(unsigned long long address, unsigned int size);
  static bool isAddressAlignedOnWordsize(unsigned long long address,
                                         unsigned int wordSize);
  static unsigned long long convertAddress(unsigned long long address,
                                           unsigned int dataLength);

  void initTransaction(tlm::tlm_generic_payload& trans,
                       unsigned long long address,
                       unsigned char* data,
                       unsigned int dataLength,
                       bool readNotWrite);
  bool doBusAccess(unsigned long long address,
                   unsigned char* data,
                   unsigned int dataLength,
                   bool readNotWrite);
  bool doBusAccess(unsigned long long address,
                   unsigned char* data,
                   unsigned int dataLength,
                   bool readNotWrite,
                   sc_core::sc_time& t);
  unsigned int doDebugBusAccess(unsigned long long address,
                                unsigned char* data,
                                unsigned int dataLength,
                                bool readNotWrite);
  template <unsigned int WORDSIZE>
  bool doConvertedAccess(unsigned long long address,
                         unsigned char* data,
                         unsigned int dataLength,
                         bool readNotWrite);
  template <unsigned int WORDSIZE>
  bool doConvertedAccess(unsigned long long address,
                         unsigned char* data,
                         unsigned int dataLength,
                         bool readNotWrite,
                         sc_core::sc_time& t);

  void invalidate_direct_mem_ptr(sc_dt::uint64 startRange,
                                 sc_dt::uint64 endRange);
  tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload& trans,
                                     tlm::tlm_phase& phase,
                                     sc_core::sc_time& t);

  void incLocalTime(const sc_core::sc_time& t);
  void setLocalTime(const sc_core::sc_time& t);
  sc_core::sc_time getLocalTime() const;

private:
  quantumkeeper_if* mQuantumKeeper;
  dmi_handler mDmiHandler;
  bool mHasHostEndianness;
  std::set<tlm::tlm_bw_direct_mem_if*> mBwDirectMemIfs;
  BwTransportIf* mBwTransportIf;
  bool mDmiEnabled;
  mutable logging::stream mError;
};

template <unsigned int BUSWIDTH>
inline
initiator_socket<BUSWIDTH>::
initiator_socket() :
  base_type(sc_core::sc_gen_unique_name("initiator_socket")),
  mQuantumKeeper(0),
  mHasHostEndianness(true),
  mBwTransportIf(0),
  mDmiEnabled(true),
  mError(this->name(), logging::severity::error())
{
  register_invalidate_direct_mem_ptr(this, &initiator_socket::invalidate_direct_mem_ptr);
  register_nb_transport_bw(this, &initiator_socket::nb_transport_bw);
  register_bw_direct_mem_if(&mDmiHandler);
}

template <unsigned int BUSWIDTH>
inline
initiator_socket<BUSWIDTH>::
initiator_socket(const char* n) :
  base_type(n),
  mQuantumKeeper(0),
  mHasHostEndianness(true),
  mBwTransportIf(0),
  mDmiEnabled(true),
  mError(this->name(), logging::severity::error())
{
  register_invalidate_direct_mem_ptr(this, &initiator_socket::invalidate_direct_mem_ptr);
  register_nb_transport_bw(this, &initiator_socket::nb_transport_bw);
  register_bw_direct_mem_if(&mDmiHandler);
}

template <unsigned int BUSWIDTH>
inline
initiator_socket<BUSWIDTH>::
~initiator_socket()
{
  unregister_bw_direct_mem_if(&mDmiHandler);
  delete mQuantumKeeper;
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
end_of_elaboration()
{
  base_type::end_of_elaboration();
  mDmiHandler.set_interface(this->operator->());
}

template <unsigned int BUSWIDTH>
template <typename T>
inline
void
initiator_socket<BUSWIDTH>::
set_quantumkeeper(T& quantumKeeper)
{
  delete mQuantumKeeper;
  mQuantumKeeper = new quantumkeeper_wrapper<T>(quantumKeeper);
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
set_endianness(tlm::tlm_endianness endianness)
{
  mHasHostEndianness = tlm::has_host_endianness(endianness);
}

template <unsigned int BUSWIDTH>
inline
bool
initiator_socket<BUSWIDTH>::
isAlignedAccess(unsigned long long address, unsigned int size)
{
  return ((address % (BUSWIDTH / 8)) == 0 &&
          (size == (BUSWIDTH / 8)));
}

template <unsigned int BUSWIDTH>
inline
bool
initiator_socket<BUSWIDTH>::
isAddressAlignedOnWordsize(unsigned long long address,
                           unsigned int wordSize)
{
  return address % wordSize == 0;
}

template <unsigned int BUSWIDTH>
inline
unsigned long long
initiator_socket<BUSWIDTH>::
convertAddress(unsigned long long address, unsigned int dataLength)
{
  return address ^ ((BUSWIDTH / 8) - dataLength);
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
initTransaction(tlm::tlm_generic_payload& trans,
                unsigned long long address,
                unsigned char* data,
                unsigned int dataLength,
                bool readNotWrite)
{
  trans.set_address(address);
  trans.set_command(readNotWrite ? tlm::TLM_READ_COMMAND : tlm::TLM_WRITE_COMMAND);
  trans.set_data_ptr(data);
  trans.set_data_length(dataLength);
  trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
  trans.set_byte_enable_ptr(0);
  trans.set_byte_enable_length(0);
  trans.set_streaming_width(dataLength);
  trans.set_dmi_allowed(false);
}

template <unsigned int BUSWIDTH>
inline
bool
initiator_socket<BUSWIDTH>::
doBusAccess(unsigned long long address,
            unsigned char* data,
            unsigned int dataLength,
            bool readNotWrite)
{
  // FIXME: pool
  tlm::tlm_generic_payload trans;
  initTransaction(trans, address, data, dataLength, readNotWrite);

  sc_core::sc_time t = getLocalTime();
  (*this)->b_transport(trans, t);
  setLocalTime(t);

  return trans.is_response_ok();
}

template <unsigned int BUSWIDTH>
inline
bool
initiator_socket<BUSWIDTH>::
doBusAccess(unsigned long long address,
            unsigned char* data,
            unsigned int dataLength,
            bool readNotWrite,
            sc_core::sc_time& t)
{
  // FIXME: pool
  tlm::tlm_generic_payload trans;
  initTransaction(trans, address, data, dataLength, readNotWrite);

  (*this)->b_transport(trans, t);

  return trans.is_response_ok();
}

template <unsigned int BUSWIDTH>
inline
unsigned int
initiator_socket<BUSWIDTH>::
doDebugBusAccess(unsigned long long address,
                 unsigned char* data,
                 unsigned int dataLength,
                 bool readNotWrite)
{
  // FIXME: pool
  tlm::tlm_generic_payload trans;
  trans.set_address(address);
  trans.set_command(readNotWrite ? tlm::TLM_READ_COMMAND : tlm::TLM_WRITE_COMMAND);
  trans.set_data_ptr(data);
  trans.set_data_length(dataLength);
  trans.set_dmi_allowed(false);

  return (*this)->transport_dbg(trans);
}

template <unsigned int BUSWIDTH>
template <unsigned int WORDSIZE>
inline
bool
initiator_socket<BUSWIDTH>::
doConvertedAccess(unsigned long long address,
                  unsigned char* data,
                  unsigned int dataLength,
                  bool readNotWrite)
{
  // FIXME: pool
  tlm::tlm_generic_payload trans;
  initTransaction(trans, address, data, dataLength, readNotWrite);
  
  tlm::tlm_to_hostendian_generic<WordSizeToDT<WORDSIZE> >(&trans, BUSWIDTH / 8);

  bool result = false;
  sc_core::sc_time t = sc_core::SC_ZERO_TIME;
  if (mDmiHandler.transport(trans, t)) {
    if (t != sc_core::SC_ZERO_TIME) {
      incLocalTime(t);
    }
    result = true;

  } else {
    t = getLocalTime();
    (*this)->b_transport(trans, t);
    setLocalTime(t);
    result = trans.is_response_ok();
  }

  tlm::tlm_from_hostendian_generic<WordSizeToDT<WORDSIZE> >(&trans, BUSWIDTH / 8);

  return result;
}


template <unsigned int BUSWIDTH>
template <unsigned int WORDSIZE>
inline
bool
initiator_socket<BUSWIDTH>::
doConvertedAccess(unsigned long long address,
                  unsigned char* data,
                  unsigned int dataLength,
                  bool readNotWrite,
                  sc_core::sc_time& t)
{
  // FIXME: pool
  tlm::tlm_generic_payload trans;
  initTransaction(trans, address, data, dataLength, readNotWrite);
  
  tlm::tlm_to_hostendian_generic<WordSizeToDT<WORDSIZE> >(&trans, BUSWIDTH / 8);

  bool result = false;
  if (mDmiHandler.transport(trans, t)) {
    result = true;

  } else {
    (*this)->b_transport(trans, t);
    result = trans.is_response_ok();
  }

  tlm::tlm_from_hostendian_generic<WordSizeToDT<WORDSIZE> >(&trans, BUSWIDTH / 8);

  return result;
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
invalidate_direct_mem_ptr(sc_dt::uint64 startRange,
                          sc_dt::uint64 endRange)
{
  std::set<tlm::tlm_bw_direct_mem_if*>::iterator it = mBwDirectMemIfs.begin();
  std::set<tlm::tlm_bw_direct_mem_if*>::const_iterator end = mBwDirectMemIfs.end();
  for (; it != end; ++it) {
    (*it)->invalidate_direct_mem_ptr(startRange, endRange);
  }
}

template <unsigned int BUSWIDTH>
inline
tlm::tlm_sync_enum
initiator_socket<BUSWIDTH>::
nb_transport_bw(tlm::tlm_generic_payload& trans,
                tlm::tlm_phase& phase,
                sc_core::sc_time& t)
{
  if (!mBwTransportIf) {
    SCML2_LOG(mError) << "no nb_transport_bw interface registered" << std::endl;
    return tlm::TLM_COMPLETED;

  } else {
    return mBwTransportIf->nb_transport_bw(trans, phase, t);
  }
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
incLocalTime(const sc_core::sc_time& t)
{
  if (t != sc_core::SC_ZERO_TIME) {
    if (mQuantumKeeper) {
      mQuantumKeeper->inc(t);
  
    } else {
      sc_core::wait(t);
    }
  }
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
setLocalTime(const sc_core::sc_time& t)
{
  if (mQuantumKeeper) {
    mQuantumKeeper->set(t);
  
  } else {
    if (t != sc_core::SC_ZERO_TIME) {
      sc_core::wait(t);
    }
  }
}

template <unsigned int BUSWIDTH>
inline
sc_core::sc_time
initiator_socket<BUSWIDTH>::
getLocalTime() const
{
  if (mQuantumKeeper) {
    return mQuantumKeeper->get_local_time();
  
  } else {
    return sc_core::SC_ZERO_TIME;
  }
}

template <unsigned int BUSWIDTH>
template <unsigned int WORDSIZE>
inline
bool
initiator_socket<BUSWIDTH>::
read(unsigned long long address, unsigned char* data, unsigned int count)
{
  //assert(isPowerOf2(WORDSIZE));
  if (!mHasHostEndianness && !isAlignedAccess(address, WORDSIZE)) {
    if (isAddressAlignedOnWordsize(address, WORDSIZE) &&
        WORDSIZE <= (BUSWIDTH / 8) &&
        count == 1) {
      // aligned subword access: change address
      address = convertAddress(address, WORDSIZE);

    } else {
      return doConvertedAccess<WORDSIZE>(address, data, WORDSIZE * count, true);
    }
  }

  sc_core::sc_time t = sc_core::SC_ZERO_TIME;
  if (mDmiHandler.read(address, data, WORDSIZE * count, t)) {
    incLocalTime(t);
    return true;
  }

  return doBusAccess(address, data, WORDSIZE * count, true);
}

template <unsigned int BUSWIDTH>
template <unsigned int WORDSIZE>
inline
bool
initiator_socket<BUSWIDTH>::
write(unsigned long long address, const unsigned char* data, unsigned int count)
{
  //assert(isPowerOf2(WORDSIZE));
  if (!mHasHostEndianness && !isAlignedAccess(address, WORDSIZE)) {
    if (isAddressAlignedOnWordsize(address, WORDSIZE) &&
        WORDSIZE <= (BUSWIDTH / 8) &&
        count == 1) {
      // aligned subword access: change address
      address = convertAddress(address, WORDSIZE);

    } else {
      return doConvertedAccess<WORDSIZE>(address,
                                         const_cast<unsigned char*>(data),
                                         WORDSIZE * count,
                                         false);
    }
  }

  sc_core::sc_time t = sc_core::SC_ZERO_TIME;
  if (mDmiHandler.write(address, data, WORDSIZE * count, t)) {
    incLocalTime(t);
    return true;
  }

  return doBusAccess(address, const_cast<unsigned char*>(data), WORDSIZE * count, false);
}

template <unsigned int BUSWIDTH>
template <unsigned int WORDSIZE>
inline
bool
initiator_socket<BUSWIDTH>::
read(unsigned long long address, unsigned char* data, unsigned int count, sc_core::sc_time& t)
{
  //assert(isPowerOf2(WORDSIZE));
  if (!mHasHostEndianness && !isAlignedAccess(address, WORDSIZE)) {
    if (isAddressAlignedOnWordsize(address, WORDSIZE) &&
        WORDSIZE <= (BUSWIDTH / 8) &&
        count == 1) {
      // aligned subword access: change address
      address = convertAddress(address, WORDSIZE);

    } else {
      return doConvertedAccess<WORDSIZE>(address, data, WORDSIZE * count, true, t);
    }
  }

  if (mDmiHandler.read(address, data, WORDSIZE * count, t)) {
    return true;
  }

  return doBusAccess(address, data, WORDSIZE * count, true, t);
}

template <unsigned int BUSWIDTH>
template <unsigned int WORDSIZE>
inline
bool
initiator_socket<BUSWIDTH>::
write(unsigned long long address, const unsigned char* data, unsigned int count, sc_core::sc_time& t)
{
  //assert(isPowerOf2(WORDSIZE));
  if (!mHasHostEndianness && !isAlignedAccess(address, WORDSIZE)) {
    if (isAddressAlignedOnWordsize(address, WORDSIZE) &&
        WORDSIZE <= (BUSWIDTH / 8) &&
        count == 1) {
      // aligned subword access: change address
      address = convertAddress(address, WORDSIZE);

    } else {
      return doConvertedAccess<WORDSIZE>(address,
                                         const_cast<unsigned char*>(data),
                                         WORDSIZE * count,
                                         false,
                                         t);
    }
  }

  if (mDmiHandler.write(address, data, WORDSIZE * count, t)) {
    return true;
  }

  return doBusAccess(address, const_cast<unsigned char*>(data), WORDSIZE * count, false, t);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
read(unsigned long long address, DT& data)
{
  return read<SizeOf<DT>::result>(address,
                                  dt_from_array<DT>(data),
                                  1);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
write(unsigned long long address, const DT& data)
{
  return write<SizeOf<DT>::result>(address,
                                   dt_to_array<DT>(data),
                                   1);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
read(unsigned long long address, DT* data, unsigned int count)
{
  return read<SizeOf<DT>::result>(address,
                                  reinterpret_cast<unsigned char*>(data),
                                  count);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
write(unsigned long long address, const DT* data, unsigned int count)
{
  return write<SizeOf<DT>::result>(address,
                                   reinterpret_cast<const unsigned char*>(data),
                                   count);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
read(unsigned long long address, sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count)
{
  std::vector<unsigned char> array(sizeOf<DT>() * count);
  bool result = read<SizeOf<DT>::result>(address, &array[0], count);
  if (result) {
    for (unsigned int i = 0; i < count; ++i) {
      data[i] = array_to_dt<DT>(&array[i * SizeOf<DT>::result]);
    }
  }
  return result;
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
write(unsigned long long address, const sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count)
{
  std::vector<unsigned char> array(sizeOf<DT>() * count);
  for (unsigned int i = 0; i < count; ++i) {
    to_char_array(data[i], &array[i * SizeOf<DT>::result], SizeOf<DT>::result, 0);
  }
  return write<SizeOf<DT>::result>(address, &array[0], count);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
read(unsigned long long address, DT& data, sc_core::sc_time& t)
{
  return read<SizeOf<DT>::result>(address,
                                  dt_from_array<DT>(data),
                                  1,
                                  t);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
write(unsigned long long address, const DT& data, sc_core::sc_time& t)
{
  return write<SizeOf<DT>::result>(address,
                                   dt_to_array<DT>(data),
                                   1,
                                   t);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
read(unsigned long long address, DT* data, unsigned int count, sc_core::sc_time& t)
{
  return read<SizeOf<DT>::result>(address,
                                  reinterpret_cast<unsigned char*>(data),
                                  count,
                                  t);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
write(unsigned long long address, const DT* data, unsigned int count, sc_core::sc_time& t)
{
  return write<SizeOf<DT>::result>(address,
                                   reinterpret_cast<const unsigned char*>(data),
                                   count,
                                   t);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
read(unsigned long long address, sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count, sc_core::sc_time& t)
{
  std::vector<unsigned char> array(sizeOf<DT>() * count);
  bool result = read<SizeOf<DT>::result>(address, &array[0], count, t);
  if (result) {
    for (unsigned int i = 0; i < count; ++i) {
      data[i] = array_to_dt<DT>(&array[i * SizeOf<DT>::result]);
    }
  }
  return result;
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
write(unsigned long long address, const sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count, sc_core::sc_time& t)
{
  std::vector<unsigned char> array(sizeOf<DT>() * count);
  for (unsigned int i = 0; i < count; ++i) {
    to_char_array(data[i], &array[i * SizeOf<DT>::result], SizeOf<DT>::result, 0);
  }
  return write<SizeOf<DT>::result>(address, &array[0], count, t);
}

template <unsigned int BUSWIDTH>
template <unsigned int WORDSIZE>
inline
unsigned int
initiator_socket<BUSWIDTH>::
read_debug(unsigned long long address, unsigned char* data, unsigned int count)
{
  //assert(isPowerOf2(WORDSIZE));
  if (!mHasHostEndianness && !isAlignedAccess(address, WORDSIZE)) {
    if (isAddressAlignedOnWordsize(address, WORDSIZE) &&
        WORDSIZE <= (BUSWIDTH / 8) &&
        count == 1) {
      // aligned subword access: change address
      address = convertAddress(address, WORDSIZE);

    } else {
      // unroll to byte accesses
      for (unsigned int beat = 0; beat < count; ++beat) {
        for (unsigned int byte = 0; byte < WORDSIZE; ++byte) {
          const unsigned int index = beat * WORDSIZE + byte;
          const unsigned long long convertedAddress = convertAddress(address + beat * WORDSIZE + WORDSIZE - 1 - byte, 1);
          if (!mDmiHandler.read_debug(convertedAddress, &data[index], 1)) {
            unsigned char* nonConstData = const_cast<unsigned char*>(&data[index]);
            if (doDebugBusAccess(convertedAddress, nonConstData, 1, true) != 1) {
              return index;
            }
          }
        }
      }
      return WORDSIZE * count;
    }
  }

  if (mDmiHandler.read_debug(address, data, WORDSIZE * count)) {
    return WORDSIZE * count;
  }
  return doDebugBusAccess(address, data, WORDSIZE * count, true);
}

template <unsigned int BUSWIDTH>
template <unsigned int WORDSIZE>
inline
unsigned int
initiator_socket<BUSWIDTH>::
write_debug(unsigned long long address, const unsigned char* data, unsigned int count)
{
  //assert(isPowerOf2(WORDSIZE));
  if (!mHasHostEndianness && !isAlignedAccess(address, WORDSIZE)) {
    if (isAddressAlignedOnWordsize(address, WORDSIZE) &&
        WORDSIZE <= (BUSWIDTH / 8) &&
        count == 1) {
      // aligned subword access: change address
      address = convertAddress(address, WORDSIZE);

    } else {
      // unroll to byte accesses
      for (unsigned int beat = 0; beat < count; ++beat) {
        for (unsigned int byte = 0; byte < WORDSIZE; ++byte) {
          const unsigned int index = beat * WORDSIZE + byte;
          const unsigned long long convertedAddress = convertAddress(address + beat * WORDSIZE + WORDSIZE - 1 - byte, 1);
          if (!mDmiHandler.write_debug(convertedAddress, &data[index], 1)) {
            unsigned char* nonConstData = const_cast<unsigned char*>(&data[index]);
            if (doDebugBusAccess(convertedAddress, nonConstData, 1, false) != 1) {
              return index;
            }
          }
        }
      }
      return WORDSIZE * count;
    }
  }

  if (mDmiHandler.write_debug(address, data, WORDSIZE * count)) {
    return WORDSIZE * count;
  }
  return doDebugBusAccess(address, const_cast<unsigned char*>(data), WORDSIZE * count, false);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
read_debug(unsigned long long address, DT& data)
{
  return read_debug<SizeOf<DT>::result>(address,
                                        dt_from_array<DT>(data),
                                        1);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
write_debug(unsigned long long address, const DT& data)
{
  return write_debug<SizeOf<DT>::result>(address,
                                         dt_to_array<DT>(data),
                                         1);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
read_debug(unsigned long long address, DT* data, unsigned int count)
{
  return read_debug<SizeOf<DT>::result>(address,
                                        reinterpret_cast<unsigned char*>(data),
                                        count);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
write_debug(unsigned long long address, const DT* data, unsigned int count)
{
  return write_debug<SizeOf<DT>::result>(address,
                                         reinterpret_cast<const unsigned char*>(data),
                                         count);
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
read_debug(unsigned long long address, sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count)
{
  std::vector<unsigned char> array(sizeOf<DT>() * count);
  bool result = read_debug<SizeOf<DT>::result>(address, &array[0], count);
  if (result) {
    for (unsigned int i = 0; i < count; ++i) {
      data[i] = array_to_dt<DT>(&array[i * SizeOf<DT>::result]);
    }
  }
  return result;
}

template <unsigned int BUSWIDTH>
template <typename DT>
inline
bool
initiator_socket<BUSWIDTH>::
write_debug(unsigned long long address, const sc_dt::sc_biguint<SizeOfBits<DT>::result>* data, unsigned int count)
{
  std::vector<unsigned char> array(sizeOf<DT>() * count);
  for (unsigned int i = 0; i < count; ++i) {
    to_char_array(data[i], &array[i * SizeOf<DT>::result], SizeOf<DT>::result, 0);
  }
  return write_debug<SizeOf<DT>::result>(address, &array[0], count);
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
enable_dmi()
{
  if (!is_dmi_enabled()) {
    mDmiEnabled = true;
    mDmiHandler.enable_dmi();
    invalidate_direct_mem_ptr(0, (unsigned long long)-1);
  }
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
disable_dmi()
{
  if (is_dmi_enabled()) {
    mDmiEnabled = false;
    mDmiHandler.disable_dmi();
    invalidate_direct_mem_ptr(0, (unsigned long long)-1);
  }
}

template <unsigned int BUSWIDTH>
inline
bool
initiator_socket<BUSWIDTH>::
is_dmi_enabled() const
{
  return mDmiEnabled;
}

template <unsigned int BUSWIDTH>
inline
std::string
initiator_socket<BUSWIDTH>::
get_mapped_name() const
{
  return this->name();
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  // FIXME: convert endianness? Or forward transaction unmodified?

  if (mDmiHandler.transport(trans, t)) {
    return;
  }

  (*this)->b_transport(trans, t);
}

template <unsigned int BUSWIDTH>
inline
tlm::tlm_sync_enum
initiator_socket<BUSWIDTH>::
nb_transport_fw(tlm::tlm_generic_payload& trans,
                tlm::tlm_phase& phase,
                sc_core::sc_time& t)
{
  // FIXME: convert endianness? Or forward transaction unmodified?

  if (phase == tlm::BEGIN_REQ) {
    if (mDmiHandler.transport(trans, t)) {
      return tlm::TLM_COMPLETED;
    }
  }

  return (*this)->nb_transport_fw(trans, phase, t);
}

template <unsigned int BUSWIDTH>
inline
unsigned int
initiator_socket<BUSWIDTH>::
transport_dbg(tlm::tlm_generic_payload& trans)
{
  // FIXME: convert endianness? Or forward transaction unmodified?

  if (mDmiHandler.transport_debug(trans)) {
    return trans.get_data_length();
  }

  return (*this)->transport_dbg(trans);
}

template <unsigned int BUSWIDTH>
inline
bool
initiator_socket<BUSWIDTH>::
get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData)
{
  return mDmiHandler.get_direct_mem_ptr(trans, dmiData);
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
register_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  assert(bwInterface);
  mBwDirectMemIfs.insert(bwInterface);
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
unregister_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  mBwDirectMemIfs.erase(bwInterface);
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
register_bw_transport_if(BwTransportIf* bwInterface)
{
  assert(bwInterface);

  if (mBwTransportIf) {
    SCML2_LOG(mError)
      << "nb_transport_bw interface already registered"
      << std::endl;
  }

  mBwTransportIf = bwInterface;
}

template <unsigned int BUSWIDTH>
inline
void
initiator_socket<BUSWIDTH>::
unregister_bw_transport_if(BwTransportIf* bwInterface)
{
  assert(bwInterface);
  if (mBwTransportIf == bwInterface) {
    mBwTransportIf = 0;
  }
}

}

#endif
