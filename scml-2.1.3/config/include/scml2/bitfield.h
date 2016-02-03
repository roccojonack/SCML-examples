/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_H
#define SCML2_BITFIELD_H

#include <scml2/bitfield_base.h>
#include <scml2/reg.h>
#include <scml2/bitfield_read_callback_base.h>
#include <scml2/bitfield_write_callback_base.h>
#include <scml2/bitfield_debug_read_callback_base.h>
#include <scml2/bitfield_debug_write_callback_base.h>
#include <scml2/bitfield_callback_observers.h>

#include <scml2/utils.h>
#include <scml2/scoped_reference.h>
#include <scml2/types.h>

#include <tlm.h>
#include <string>
#include <cassert>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT> class bitfield_callback_observer;

template <typename DT>
class bitfield : public bitfield_base
{
public:
  typedef DT data_type;

public:
  bitfield(const std::string& name,
           reg<DT>& r,
           unsigned int offset,
           unsigned int size);
  ~bitfield();

  void put(const DT& value);
  void put(const DT& value, const DT& bitMask);
  DT get() const;
  DT get(const DT& bitMask) const;

  void put_debug(const DT& value);
  void put_debug(const DT& value, const DT& bitMask);
  DT get_debug() const;
  DT get_debug(const DT& bitMask) const;

  bool put_with_triggering_callbacks(const DT& value,
                                     sc_core::sc_time& t);
  bool put_with_triggering_callbacks(const DT& value,
                                     const DT& bitMask,
                                     sc_core::sc_time& t);
  bool get_with_triggering_callbacks(DT& value,
                                     sc_core::sc_time& t) const;
  bool get_with_triggering_callbacks(DT& value,
                                     const DT& bitMask,
                                     sc_core::sc_time& t) const;

  bool put_debug_with_triggering_callbacks(const DT& value);
  bool put_debug_with_triggering_callbacks(const DT& value, const DT& bitMask);
  bool get_debug_with_triggering_callbacks(DT& value) const;
  bool get_debug_with_triggering_callbacks(DT& value, const DT& bitMask) const;

  operator DT() const;

  bitfield& operator=(DT value);
  bitfield& operator =(const bitfield& b);

  bitfield& operator+=(DT value);
  bitfield& operator-=(DT value);
  bitfield& operator/=(DT value);
  bitfield& operator*=(DT value);
  bitfield& operator%=(DT value);
  bitfield& operator^=(DT value);
  bitfield& operator&=(DT value);
  bitfield& operator|=(DT value);
  bitfield& operator<<=(DT value);
  bitfield& operator>>=(DT value);

  bitfield& operator--();
  DT operator--(int);
  bitfield& operator++();
  DT operator++(int);

  void set_read_callback(bitfield_read_callback_base<DT>* cb);
  void set_write_callback(bitfield_write_callback_base<DT>* cb);

  void remove_callback();
  void remove_read_callback();
  void remove_write_callback();

  bitfield_read_callback_base<DT>* get_read_callback() const;
  bitfield_write_callback_base<DT>* get_write_callback() const;

  void set_debug_read_callback(bitfield_debug_read_callback_base<DT>* cb);
  void set_debug_write_callback(bitfield_debug_write_callback_base<DT>* cb);

  void remove_debug_callback();
  void remove_debug_read_callback();
  void remove_debug_write_callback();

  bitfield_debug_read_callback_base<DT>* get_debug_read_callback() const;
  bitfield_debug_write_callback_base<DT>* get_debug_write_callback() const;

  bool has_default_read_behavior() const;
  bool has_default_write_behavior() const;
  bool has_default_debug_read_behavior() const;
  bool has_default_debug_write_behavior() const;
  bool has_never_syncing_read_behavior() const;
  bool has_never_syncing_write_behavior() const;

  bool register_callback_observer(bitfield_callback_observer<DT>* o);
  bool unregister_all_callback_observers();
  bool unregister_callback_observer(bitfield_callback_observer<DT>* o);

  // sc_object
  virtual const char* kind() const;

  using bitfield_base::set_symbolic_name;
  bool set_symbolic_name(const DT& value, const std::string& name);

private:
  void do_set_read_callback(bitfield_read_callback_base<DT>* cb);
  void do_set_write_callback(bitfield_write_callback_base<DT>* cb);
  void do_set_debug_read_callback(bitfield_debug_read_callback_base<DT>* cb);
  void do_set_debug_write_callback(bitfield_debug_write_callback_base<DT>* cb);

private:
  bitfield(const bitfield&);

private:
  reg<DT>& mRegister;

  bitfield_read_callback_base<DT>* mDefaultReadCallback;
  bitfield_write_callback_base<DT>* mDefaultWriteCallback;
  bitfield_debug_read_callback_base<DT>* mDefaultDebugReadCallback;
  bitfield_debug_write_callback_base<DT>* mDefaultDebugWriteCallback;
  bitfield_read_callback_base<DT>* mReadCallback;
  bitfield_write_callback_base<DT>* mWriteCallback;
  bitfield_debug_read_callback_base<DT>* mDebugReadCallback;
  bitfield_debug_write_callback_base<DT>* mDebugWriteCallback;

  bitfield_callback_observers<DT> mCallbackObservers;
};

template <typename DT>
inline
void
bitfield<DT>::
put(const DT& value)
{
  DT data = insert_bits(mRegister.get_debug(), value, mSize, mOffset);
  mRegister.put(data);
}

template <typename DT>
inline
void
bitfield<DT>::
put(const DT& value, const DT& bitMask)
{
  const DT maskedValue = (get_debug() & ~bitMask) | (value & bitMask);
  DT data = insert_bits(mRegister.get_debug(), maskedValue, mSize, mOffset);
  mRegister.put(data);
}

template <typename DT>
inline
DT
bitfield<DT>::
get() const
{
  return extract_bits(mRegister.get(), mSize, mOffset);
}

template <typename DT>
inline
DT
bitfield<DT>::
get(const DT& bitMask) const
{
  return extract_bits(mRegister.get(), mSize, mOffset) & bitMask;
}

template <typename DT>
inline
void
bitfield<DT>::
put_debug(const DT& value)
{
  DT data = insert_bits(mRegister.get_debug(), value, mSize, mOffset);
  mRegister.put_debug(data);
}

template <typename DT>
inline
void
bitfield<DT>::
put_debug(const DT& value, const DT& bitMask)
{
  const DT maskedValue = (get_debug() & ~bitMask) | (value & bitMask);
  DT data = insert_bits(mRegister.get_debug(), maskedValue, mSize, mOffset);
  mRegister.put_debug(data);
}

template <typename DT>
inline
DT
bitfield<DT>::
get_debug() const
{
  return extract_bits(mRegister.get_debug(), mSize, mOffset);
}

template <typename DT>
inline
DT
bitfield<DT>::
get_debug(const DT& bitMask) const
{
  return extract_bits(mRegister.get_debug(), mSize, mOffset) & bitMask;
}

template <typename DT>
inline
bool
bitfield<DT>::
put_with_triggering_callbacks(const DT& value, sc_core::sc_time& t)
{
  assert(mWriteCallback);
  scoped_reference<bitfield_write_callback_base<DT> > scopedRef(mWriteCallback);
  unsigned int id =
    mCallbackObservers.notify_begin(&value, 0, ACCESS_TYPE_WRITE, ACCESS_MODE_REGULAR);
  bool result = mWriteCallback->write(value, get_bit_mask<DT>(get_size()), t);
  mCallbackObservers.notify_end(0, id);
  return result;
}

template <typename DT>
inline
bool
bitfield<DT>::
put_with_triggering_callbacks(const DT& value,
                              const DT& bitMask,
                              sc_core::sc_time& t)
{
  assert(mWriteCallback);
  scoped_reference<bitfield_write_callback_base<DT> > scopedRef(mWriteCallback);
  unsigned int id =
    mCallbackObservers.notify_begin(&value, &bitMask, ACCESS_TYPE_WRITE, ACCESS_MODE_REGULAR);
  bool result = mWriteCallback->write(value, bitMask, t);
  mCallbackObservers.notify_end(0, id);
  return result;
}

template <typename DT>
inline
bool
bitfield<DT>::
get_with_triggering_callbacks(DT& value, sc_core::sc_time& t) const
{
  assert(mReadCallback);
  scoped_reference<bitfield_read_callback_base<DT> > scopedRef(mReadCallback);
  unsigned int id =
    mCallbackObservers.notify_begin(0, 0, ACCESS_TYPE_READ, ACCESS_MODE_REGULAR);
  bool result = mReadCallback->read(value, get_bit_mask<DT>(get_size()), t);
  mCallbackObservers.notify_end(&value, id);
  return result;
}

template <typename DT>
inline
bool
bitfield<DT>::
get_with_triggering_callbacks(DT& value,
                              const DT& bitMask,
                              sc_core::sc_time& t) const
{
  assert(mReadCallback);
  scoped_reference<bitfield_read_callback_base<DT> > scopedRef(mReadCallback);
  unsigned int id =
    mCallbackObservers.notify_begin(0, &bitMask, ACCESS_TYPE_READ, ACCESS_MODE_REGULAR);
  bool result = mReadCallback->read(value, bitMask, t);
  mCallbackObservers.notify_end(&value, id);
  return result;
}

template <typename DT>
inline
bool
bitfield<DT>::
put_debug_with_triggering_callbacks(const DT& value)
{
  assert(mDebugWriteCallback);
  scoped_reference<bitfield_debug_write_callback_base<DT> > scopedRef(mDebugWriteCallback);
  unsigned int id =
    mCallbackObservers.notify_begin(&value, 0, ACCESS_TYPE_WRITE, ACCESS_MODE_DEBUG);
  bool result = mDebugWriteCallback->write(value, get_bit_mask<DT>(get_size()));
  mCallbackObservers.notify_end(0, id);
  return result;
}

template <typename DT>
inline
bool
bitfield<DT>::
put_debug_with_triggering_callbacks(const DT& value, const DT& bitMask)
{
  assert(mDebugWriteCallback);
  scoped_reference<bitfield_debug_write_callback_base<DT> > scopedRef(mDebugWriteCallback);
  unsigned int id =
    mCallbackObservers.notify_begin(&value, &bitMask, ACCESS_TYPE_WRITE, ACCESS_MODE_DEBUG);
  bool result = mDebugWriteCallback->write(value, bitMask);
  mCallbackObservers.notify_end(0, id);
  return result;
}

template <typename DT>
inline
bool
bitfield<DT>::
get_debug_with_triggering_callbacks(DT& value) const
{
  assert(mDebugReadCallback);
  scoped_reference<bitfield_debug_read_callback_base<DT> > scopedRef(mDebugReadCallback);
  unsigned int id =
    mCallbackObservers.notify_begin(0, 0, ACCESS_TYPE_READ, ACCESS_MODE_DEBUG);
  bool result = mDebugReadCallback->read(value, get_bit_mask<DT>(get_size()));
  mCallbackObservers.notify_end(&value, id);
  return result;
}

template <typename DT>
inline
bool
bitfield<DT>::
get_debug_with_triggering_callbacks(DT& value, const DT& bitMask) const
{
  assert(mDebugReadCallback);
  scoped_reference<bitfield_debug_read_callback_base<DT> > scopedRef(mDebugReadCallback);
  unsigned int id =
    mCallbackObservers.notify_begin(0, &bitMask, ACCESS_TYPE_READ, ACCESS_MODE_DEBUG);
  bool result = mDebugReadCallback->read(value, bitMask);
  mCallbackObservers.notify_end(0, id);
  return result;
}

template <typename DT>
inline
bitfield<DT>::
operator DT() const
{
  return get();
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator=(DT value)
{
  put(value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator =(const bitfield& b)
{
  put(b);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator+=(DT value)
{
  put(get() + value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator-=(DT value)
{
  put(get() - value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator/=(DT value)
{
  put(get() / value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator*=(DT value)
{
  put(get() * value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator%=(DT value)
{
  put(get() % value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator^=(DT value)
{
  put(get() ^ value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator&=(DT value)
{
  put(get() & value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator|=(DT value)
{
  put(get() | value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator<<=(DT value)
{
  put(get() << value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator>>=(DT value)
{
  put(get() >> value);
  return *this;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator--()
{
  put(get() - 1);
  return *this;
}

template <typename DT>
inline
DT
bitfield<DT>::
operator--(int)
{
  DT tmp = *this;
  --(*this);
  return tmp;
}

template <typename DT>
inline
bitfield<DT>&
bitfield<DT>::
operator++()
{
  put(get() + 1);
  return *this;
}

template <typename DT>
inline
DT
bitfield<DT>::
operator++(int)
{
  DT tmp = *this;
  ++(*this);
  return tmp;
}

template <typename DT>
inline
bool
bitfield<DT>::
has_default_read_behavior() const
{
  assert(mReadCallback);
  return mReadCallback->has_default_behavior();
}

template <typename DT>
inline
bool
bitfield<DT>::
has_default_write_behavior() const
{
  assert(mWriteCallback);
  return mWriteCallback->has_default_behavior();
}

template <typename DT>
inline
bool
bitfield<DT>::
has_default_debug_read_behavior() const
{
  assert(mDebugReadCallback);
  return mDebugReadCallback->has_default_behavior();
}

template <typename DT>
inline
bool
bitfield<DT>::
has_default_debug_write_behavior() const
{
  assert(mDebugWriteCallback);
  return mDebugWriteCallback->has_default_behavior();
}

template <typename DT>
inline
bool
bitfield<DT>::
has_never_syncing_read_behavior() const
{
  assert(mReadCallback);
  return mReadCallback->has_never_syncing_behavior();
}

template <typename DT>
inline
bool
bitfield<DT>::
has_never_syncing_write_behavior() const
{
  assert(mWriteCallback);
  return mWriteCallback->has_never_syncing_behavior();
}

}

#endif
