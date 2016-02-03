/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_REG_H
#define SCML2_REG_H

#include <scml2/memory_base.h>
#include <scml2/memory_fast_access.h>

#include <scml2/memory_iterator.h>
#include <scml2/memory_const_iterator.h>

#include <scml2/utils.h>

#include <tlm.h>
#include <vector>
#include <string>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT> class memory;
template <typename DT> class memory_alias;
class bitfield_base;
template <typename DT> class bitfield;
class memory_content_observer;
class memory_callback_base;
class memory_debug_callback_base;

// alias of size 1
// - no storage, toplevel memory has storage
// - must have parent (memory or memory_alias)
// - can have a transport/transportRead/transportWrite callback
// - can have a read/write callback
// - can NOT have other aliases or regs
// - can NOT bind to socket
template <typename DT>
class reg :
  public memory_base
{
public:
  typedef DT data_type;
  typedef memory_iterator<DT> iterator;
  typedef memory_const_iterator<DT> const_iterator;

public:
  reg(const std::string& name,
      memory<DT>& parent,
      unsigned long long offset);
  reg(const std::string& name,
      memory_alias<DT>& parent,
      unsigned long long offset);
  ~reg();

  void initialize(const DT& value = DT());

  void put(unsigned long long address,
           const unsigned char* data,
           unsigned int dataLength,
           const unsigned char* byteEnablePtr,
           unsigned int byteEnableLength);
  void put(unsigned long long address,
           const unsigned char* data,
           unsigned int dataLength);
  void get(unsigned long long address,
           unsigned char* data,
           unsigned int dataLength,
           const unsigned char* byteEnablePtr,
           unsigned int byteEnableLength) const;
  void get(unsigned long long address,
           unsigned char* data,
           unsigned int dataLength) const;

  void put(const DT& data,
           unsigned int size,
           unsigned int offset);
  void put(const DT& data);
  DT get(unsigned int size,
         unsigned int offset) const;
  DT get() const;

  void put_debug(unsigned long long address,
                 const unsigned char* data,
                 unsigned int dataLength,
                 const unsigned char* byteEnablePtr,
                 unsigned int byteEnableLength);
  void put_debug(unsigned long long address,
                 const unsigned char* data,
                 unsigned int dataLength);
  void get_debug(unsigned long long address,
                 unsigned char* data,
                 unsigned int dataLength,
                 const unsigned char* byteEnablePtr,
                 unsigned int byteEnableLength) const;
  void get_debug(unsigned long long address,
                 unsigned char* data,
                 unsigned int dataLength) const;

  void put_debug(const DT& data,
                 unsigned int size,
                 unsigned int offset);
  void put_debug(const DT& data);
  DT get_debug(unsigned int size,
               unsigned int offset) const;
  DT get_debug() const;

  tlm::tlm_response_status
  put_with_triggering_callbacks(unsigned long long address,
                                const unsigned char* data,
                                unsigned int dataLength,
                                const unsigned char* byteEnablePtr,
                                unsigned int byteEnableLength,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  put_with_triggering_callbacks(unsigned long long address,
                                const unsigned char* data,
                                unsigned int dataLength,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  get_with_triggering_callbacks(unsigned long long address,
                                unsigned char* data,
                                unsigned int dataLength,
                                const unsigned char* byteEnablePtr,
                                unsigned int byteEnableLength,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  get_with_triggering_callbacks(unsigned long long address,
                                unsigned char* data,
                                unsigned int dataLength,
                                sc_core::sc_time& t);

  tlm::tlm_response_status
  put_with_triggering_callbacks(const DT& data,
                                unsigned int size,
                                unsigned int offset,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  put_with_triggering_callbacks(const DT& data,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  get_with_triggering_callbacks(DT& data,
                                unsigned int size,
                                unsigned int offset,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  get_with_triggering_callbacks(DT& data,
                                sc_core::sc_time& t);

  unsigned int
  put_debug_with_triggering_callbacks(unsigned long long address,
                                      const unsigned char* data,
                                      unsigned int dataLength,
                                      const unsigned char* byteEnablePtr,
                                      unsigned int byteEnableLength);
  unsigned int
  put_debug_with_triggering_callbacks(unsigned long long address,
                                      const unsigned char* data,
                                      unsigned int dataLength);
  unsigned int
  get_debug_with_triggering_callbacks(unsigned long long address,
                                      unsigned char* data,
                                      unsigned int dataLength,
                                      const unsigned char* byteEnablePtr,
                                      unsigned int byteEnableLength);
  unsigned int
  get_debug_with_triggering_callbacks(unsigned long long address,
                                      unsigned char* data,
                                      unsigned int dataLength);

  unsigned int
  put_debug_with_triggering_callbacks(const DT& data,
                                      unsigned int size,
                                      unsigned int offset);
  unsigned int
  put_debug_with_triggering_callbacks(const DT& data);
  unsigned int
  get_debug_with_triggering_callbacks(DT& data,
                                      unsigned int size,
                                      unsigned int offset);
  unsigned int
  get_debug_with_triggering_callbacks(DT& data);

  void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  void transport_without_triggering_callbacks(tlm::tlm_generic_payload& trans);
  void transport_debug_without_triggering_callbacks(tlm::tlm_generic_payload& trans);

  operator DT() const;

  reg& operator=(DT value);
  reg& operator =(const reg& r);

  reg& operator+=(DT value);
  reg& operator-=(DT value);
  reg& operator/=(DT value);
  reg& operator*=(DT value);
  reg& operator%=(DT value);
  reg& operator^=(DT value);
  reg& operator&=(DT value);
  reg& operator|=(DT value);
  reg& operator>>=(DT value);
  reg& operator<<=(DT value);

  reg& operator--();
  DT operator--(int);
  reg& operator++();
  DT operator++(int);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  virtual void set_callback(memory_callback_base* cb);
  virtual void set_read_callback(memory_callback_base* cb);
  virtual void set_write_callback(memory_callback_base* cb);

  virtual void remove_callback();
  virtual void remove_read_callback();
  virtual void remove_write_callback();

  virtual void set_debug_callback(memory_debug_callback_base* cb);
  virtual void set_debug_read_callback(memory_debug_callback_base* cb);
  virtual void set_debug_write_callback(memory_debug_callback_base* cb);

  virtual void remove_debug_callback();
  virtual void remove_debug_read_callback();
  virtual void remove_debug_write_callback();

  // Debugger API
  virtual unsigned int read(unsigned long long address,
                            unsigned char* data,
                            unsigned int size);
  virtual unsigned int write(unsigned long long address,
                             const unsigned char* data,
                             unsigned int size);

  virtual bool register_content_observer(memory_content_observer* o);
  virtual bool unregister_all_content_observers();
  virtual bool unregister_content_observer(memory_content_observer* o);

  virtual unsigned int collect_bitfields(std::vector<bitfield_base*>& b) const;

  // sc_object
  virtual const char* kind() const;

  using memory_base::set_symbolic_name;
  bool set_symbolic_name(const DT& value, const std::string& name);

protected:
  virtual void invalidate_dmi();
  virtual void update_fast_access();

private:
  friend class bitfield<DT>;

  void setup();

  void register_bitfield(bitfield<DT>& bitfield);

  void bitfield_read_callback_registered();
  void bitfield_write_callback_registered();
  void bitfield_read_callback_unregistered();
  void bitfield_write_callback_unregistered();

  void bitfield_debug_read_callback_registered();
  void bitfield_debug_write_callback_registered();
  void bitfield_debug_read_callback_unregistered();
  void bitfield_debug_write_callback_unregistered();

private:
  reg(const reg&);

private:
  memory<DT>& mToplevel;
  memory_fast_access<DT> mFastAccess;

  typedef std::vector<bitfield<DT>*> Bitfields;
  typedef typename Bitfields::iterator BitfieldsIter;
  typedef typename Bitfields::const_iterator BitfieldsConstIter;
  Bitfields mBitfields;
  unsigned int mNrOfBitfieldReadCallbacks;
  unsigned int mNrOfBitfieldWriteCallbacks;
  unsigned int mNrOfBitfieldDebugReadCallbacks;
  unsigned int mNrOfBitfieldDebugWriteCallbacks;
};

template <typename DT>
inline
void
reg<DT>::
put(unsigned long long address,
    const unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength)
{
  mFastAccess.put(address,
                  data,
                  dataLength,
                  byteEnablePtr,
                  byteEnableLength,
                  false);
}

template <typename DT>
inline
void
reg<DT>::
put(unsigned long long address,
    const unsigned char* data,
    unsigned int dataLength)
{
  put(address, data, dataLength, 0, 0);
}

template <typename DT>
inline
void
reg<DT>::
get(unsigned long long address,
    unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength) const
{
  mFastAccess.get(address,
                  data,
                  dataLength,
                  byteEnablePtr,
                  byteEnableLength,
                  false);
}

template <typename DT>
inline
void
reg<DT>::
get(unsigned long long address,
    unsigned char* data,
    unsigned int dataLength) const
{
  get(address, data, dataLength, 0, 0);
}


template <typename DT>
inline
void
reg<DT>::
put(const DT& data,
    unsigned int size,
    unsigned int offset)
{
  mFastAccess.put(0, data, size, offset, false);
}

template <typename DT>
inline
void
reg<DT>::
put(const DT& data)
{
  mFastAccess.put(0, data, false);
}

template <typename DT>
inline
DT
reg<DT>::
get(unsigned int size,
    unsigned int offset) const
{
  return mFastAccess.get(0, size, offset, false);
}

template <typename DT>
inline
DT
reg<DT>::
get() const
{
  return mFastAccess.get(0, false);
}

template <typename DT>
inline
void
reg<DT>::
put_debug(unsigned long long address,
          const unsigned char* data,
          unsigned int dataLength,
          const unsigned char* byteEnablePtr,
          unsigned int byteEnableLength)
{
  mFastAccess.put(address,
                  data,
                  dataLength,
                  byteEnablePtr,
                  byteEnableLength,
                  true);
}

template <typename DT>
inline
void
reg<DT>::
put_debug(unsigned long long address,
          const unsigned char* data,
          unsigned int dataLength)
{
  put_debug(address, data, dataLength, 0, 0);
}

template <typename DT>
inline
void
reg<DT>::
get_debug(unsigned long long address,
          unsigned char* data,
          unsigned int dataLength,
          const unsigned char* byteEnablePtr,
          unsigned int byteEnableLength) const
{
  mFastAccess.get(address,
                  data,
                  dataLength,
                  byteEnablePtr,
                  byteEnableLength,
                  true);
}

template <typename DT>
inline
void
reg<DT>::
get_debug(unsigned long long address,
          unsigned char* data,
          unsigned int dataLength) const
{
  get_debug(address, data, dataLength, 0, 0);
}


template <typename DT>
inline
void
reg<DT>::
put_debug(const DT& data,
          unsigned int size,
          unsigned int offset)
{
  mFastAccess.put(0, data, size, offset, true);
}

template <typename DT>
inline
void
reg<DT>::
put_debug(const DT& data)
{
  mFastAccess.put(0, data, true);
}

template <typename DT>
inline
DT
reg<DT>::
get_debug(unsigned int size,
          unsigned int offset) const
{
  return mFastAccess.get(0, size, offset, true);
}

template <typename DT>
inline
DT
reg<DT>::
get_debug() const
{
  return mFastAccess.get(0, true);
}

template <typename DT>
inline
tlm::tlm_response_status
reg<DT>::
put_with_triggering_callbacks(unsigned long long address,
                              const unsigned char* data,
                              unsigned int dataLength,
                              const unsigned char* byteEnablePtr,
                              unsigned int byteEnableLength,
                              sc_core::sc_time& t)
{
  return mToplevel.put_with_triggering_callbacks(address + index_to_address<DT>(get_offset()),
                                                 data,
                                                 dataLength,
                                                 byteEnablePtr,
                                                 byteEnableLength,
                                                 t);
}

template <typename DT>
inline
tlm::tlm_response_status
reg<DT>::
put_with_triggering_callbacks(unsigned long long address,
                              const unsigned char* data,
                              unsigned int dataLength,
                              sc_core::sc_time& t)
{
  return put_with_triggering_callbacks(address,
                                       data,
                                       dataLength,
                                       0,
                                       0,
                                       t);
}

template <typename DT>
inline
tlm::tlm_response_status
reg<DT>::
get_with_triggering_callbacks(unsigned long long address,
                              unsigned char* data,
                              unsigned int dataLength,
                              const unsigned char* byteEnablePtr,
                              unsigned int byteEnableLength,
                              sc_core::sc_time& t)
{
  return mToplevel.get_with_triggering_callbacks(address + index_to_address<DT>(get_offset()),
                                                 data,
                                                 dataLength,
                                                 byteEnablePtr,
                                                 byteEnableLength,
                                                 t);
}

template <typename DT>
inline
tlm::tlm_response_status
reg<DT>::
get_with_triggering_callbacks(unsigned long long address,
                              unsigned char* data,
                              unsigned int dataLength,
                              sc_core::sc_time& t)
{
  return get_with_triggering_callbacks(address,
                                       data,
                                       dataLength,
                                       0,
                                       0,
                                       t);
}

template <typename DT>
inline
tlm::tlm_response_status
reg<DT>::
put_with_triggering_callbacks(const DT& data,
                              unsigned int size,
                              unsigned int offset,
                              sc_core::sc_time& t)
{
  return mToplevel.put_with_triggering_callbacks(get_offset(),
                                                 data,
                                                 size,
                                                 offset,
                                                 t);
}

template <typename DT>
inline
tlm::tlm_response_status
reg<DT>::
put_with_triggering_callbacks(const DT& data,
                              sc_core::sc_time& t)
{
  return put_with_triggering_callbacks(data,
                                       sizeOf<DT>(),
                                       0,
                                       t);
}

template <typename DT>
inline
tlm::tlm_response_status
reg<DT>::
get_with_triggering_callbacks(DT& data,
                              unsigned int size,
                              unsigned int offset,
                              sc_core::sc_time& t)
{
  return mToplevel.get_with_triggering_callbacks(get_offset(),
                                                 data,
                                                 size,
                                                 offset,
                                                 t);
}

template <typename DT>
inline
tlm::tlm_response_status
reg<DT>::
get_with_triggering_callbacks(DT& data,
                              sc_core::sc_time& t)
{
  return get_with_triggering_callbacks(data,
                                       sizeOf<DT>(),
                                       0,
                                       t);
}

template <typename DT>
inline
unsigned int
reg<DT>::
put_debug_with_triggering_callbacks(unsigned long long address,
                                    const unsigned char* data,
                                    unsigned int dataLength,
                                    const unsigned char* byteEnablePtr,
                                    unsigned int byteEnableLength)
{
  return mToplevel.put_debug_with_triggering_callbacks(address + index_to_address<DT>(get_offset()),
                                                       data,
                                                       dataLength,
                                                       byteEnablePtr,
                                                       byteEnableLength);
}

template <typename DT>
inline
unsigned int
reg<DT>::
put_debug_with_triggering_callbacks(unsigned long long address,
                                    const unsigned char* data,
                                    unsigned int dataLength)
{
  return put_debug_with_triggering_callbacks(address,
                                             data,
                                             dataLength,
                                             0,
                                             0);
}

template <typename DT>
inline
unsigned int
reg<DT>::
get_debug_with_triggering_callbacks(unsigned long long address,
                                    unsigned char* data,
                                    unsigned int dataLength,
                                    const unsigned char* byteEnablePtr,
                                    unsigned int byteEnableLength)
{
  return mToplevel.get_debug_with_triggering_callbacks(address + index_to_address<DT>(get_offset()),
                                                       data,
                                                       dataLength,
                                                       byteEnablePtr,
                                                       byteEnableLength);
}

template <typename DT>
inline
unsigned int
reg<DT>::
get_debug_with_triggering_callbacks(unsigned long long address,
                                    unsigned char* data,
                                    unsigned int dataLength)
{
  return get_debug_with_triggering_callbacks(address,
                                             data,
                                             dataLength,
                                             0,
                                             0);
}

template <typename DT>
inline
unsigned int
reg<DT>::
put_debug_with_triggering_callbacks(const DT& data,
                                    unsigned int size,
                                    unsigned int offset)
{
  return mToplevel.put_debug_with_triggering_callbacks(get_offset(),
                                                       data,
                                                       size,
                                                       offset);
}

template <typename DT>
inline
unsigned int
reg<DT>::
put_debug_with_triggering_callbacks(const DT& data)
{
  return put_debug_with_triggering_callbacks(data,
                                             sizeOf<DT>(),
                                             0);
}

template <typename DT>
inline
unsigned int
reg<DT>::
get_debug_with_triggering_callbacks(DT& data,
                                    unsigned int size,
                                    unsigned int offset)
{
  return mToplevel.get_debug_with_triggering_callbacks(get_offset(),
                                                       data,
                                                       size,
                                                       offset);
}

template <typename DT>
inline
unsigned int
reg<DT>::
get_debug_with_triggering_callbacks(DT& data)
{
  return get_debug_with_triggering_callbacks(data,
                                             sizeOf<DT>(),
                                             0);
}

template <typename DT>
inline
void
reg<DT>::
b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  const unsigned long long address = trans.get_address();
  trans.set_address(address + index_to_address<DT>(get_offset()));
  mToplevel.b_transport(trans, t);
  trans.set_address(address);
}

template <typename DT>
inline
unsigned int
reg<DT>::
transport_dbg(tlm::tlm_generic_payload& trans)
{
  const unsigned long long address = trans.get_address();
  trans.set_address(address + index_to_address<DT>(get_offset()));
  unsigned int result = mToplevel.transport_dbg(trans);
  trans.set_address(address);
  return result;
}

template <typename DT>
inline
void
reg<DT>::
transport_without_triggering_callbacks(tlm::tlm_generic_payload& trans)
{
  mFastAccess.transport(trans);
}

template <typename DT>
inline
void
reg<DT>::
transport_debug_without_triggering_callbacks(tlm::tlm_generic_payload& trans)
{
  mFastAccess.transport_debug(trans);
}

template <typename DT>
inline
reg<DT>::
operator DT() const
{
  return get();
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator=(DT value)
{
  put(value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator =(const reg& r)
{
  put(r);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator+=(DT value)
{
  mFastAccess.doAdd(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator-=(DT value)
{
  mFastAccess.doSubtract(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator/=(DT value)
{
  mFastAccess.doDivide(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator*=(DT value)
{
  mFastAccess.doMultiply(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator%=(DT value)
{
  mFastAccess.doModulo(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator^=(DT value)
{
  mFastAccess.doXor(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator&=(DT value)
{
  mFastAccess.doAnd(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator|=(DT value)
{
  mFastAccess.doOr(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator>>=(DT value)
{
  mFastAccess.doShiftRight(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator<<=(DT value)
{
  mFastAccess.doShiftLeft(0, value);
  return *this;
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator--()
{
  mFastAccess.doPreDecrement(0);
  return *this;
}

template <typename DT>
inline
DT
reg<DT>::
operator--(int)
{
  return mFastAccess.doPostDecrement(0);
}

template <typename DT>
inline
reg<DT>&
reg<DT>::
operator++()
{
  mFastAccess.doPreIncrement(0);
  return *this;
}

template <typename DT>
inline
DT
reg<DT>::
operator++(int)
{
  return mFastAccess.doPostIncrement(0);
}

template <typename DT>
inline
typename reg<DT>::iterator
reg<DT>::
begin()
{
  return iterator(&mToplevel, get_offset());
}

template <typename DT>
inline
typename reg<DT>::const_iterator
reg<DT>::
begin() const
{
  return const_iterator(&mToplevel, get_offset());
}

template <typename DT>
inline
typename reg<DT>::iterator
reg<DT>::
end()
{
  return begin() + 1;
}

template <typename DT>
inline
typename reg<DT>::const_iterator
reg<DT>::
end() const
{
  return begin() + 1;
}

}

#endif
