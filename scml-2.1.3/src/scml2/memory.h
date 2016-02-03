/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_H
#define SCML2_MEMORY_H

#include <scml2/toplevel_memory_base.h>
#include <scml2/memory_fast_access.h>

#include <scml2/memory_index_reference.h>
#include <scml2/memory_iterator.h>
#include <scml2/memory_const_iterator.h>

#include <scml2/utils.h>

#include <tlm.h>
#include <string>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT> class memory_alias;
template <typename DT> class reg;
template <typename DT> class memory_slow_access_base;
template <typename DT> class memory_index_reference;

// toplevel memory:
// - can bind to TLM2 target socket
// - can have a transport/transportRead/transportWrite callback
// - can have aliases or registers (alias of size 1)
template <typename DT>
class memory :
  public toplevel_memory_base
{
public:
  typedef DT data_type;
  typedef memory_index_reference<DT> reference;
  typedef memory_iterator<DT> iterator;
  typedef memory_const_iterator<DT> const_iterator;

public:
  memory(const std::string& name, unsigned long long size);
  ~memory();


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

  void put(unsigned long long index,
           const DT& data,
           unsigned int size,
           unsigned int offset);
  void put(unsigned long long index,
           const DT& data);
  DT get(unsigned long long index,
         unsigned int size,
         unsigned int offset) const;
  DT get(unsigned long long index) const;

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

  void put_debug(unsigned long long index,
                 const DT& data,
                 unsigned int size,
                 unsigned int offset);
  void put_debug(unsigned long long index,
                 const DT& data);
  DT get_debug(unsigned long long index,
               unsigned int size,
               unsigned int offset) const;
  DT get_debug(unsigned long long index) const;

  using toplevel_memory_base::put_with_triggering_callbacks;
  using toplevel_memory_base::get_with_triggering_callbacks;

  tlm::tlm_response_status
  put_with_triggering_callbacks(unsigned long long index,
                                const DT& data,
                                unsigned int size,
                                unsigned int offset,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  put_with_triggering_callbacks(unsigned long long index,
                                const DT& data,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  get_with_triggering_callbacks(unsigned long long index,
                                DT& data,
                                unsigned int size,
                                unsigned int offset,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  get_with_triggering_callbacks(unsigned long long index,
                                DT& data,
                                sc_core::sc_time& t);

  using toplevel_memory_base::put_debug_with_triggering_callbacks;
  using toplevel_memory_base::get_debug_with_triggering_callbacks;

  unsigned int
  put_debug_with_triggering_callbacks(unsigned long long index,
                                      const DT& data,
                                      unsigned int size,
                                      unsigned int offset);
  unsigned int
  put_debug_with_triggering_callbacks(unsigned long long index,
                                      const DT& data);
  unsigned int
  get_debug_with_triggering_callbacks(unsigned long long index,
                                      DT& data,
                                      unsigned int size,
                                      unsigned int offset);
  unsigned int
  get_debug_with_triggering_callbacks(unsigned long long index,
                                      DT& data);

  void transport_without_triggering_callbacks(tlm::tlm_generic_payload& trans);
  void transport_debug_without_triggering_callbacks(tlm::tlm_generic_payload& trans);

  reference operator[](unsigned long long index);
  DT operator[](unsigned long long index) const;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  using memory_base::set_symbolic_name;
  bool set_symbolic_name(const DT& value, const std::string& name);

protected:
  virtual void update_fast_access();

  // basic handling for case where storage is not managed by scml. (eg scml2_erd)
  memory(const std::string& name, unsigned long long size, memory_storage_base *storage, bool delStorageOnDestruction);

private:
  friend class memory_index_reference<DT>;
  friend class memory_alias<DT>;
  friend class reg<DT>;

  void setup(memory_storage_base* storage, bool delStorageOnDestruction);

  memory_slow_access_base<DT>* create_slow_access(unsigned long long offset);

private:
  memory(const memory&);
  memory& operator =(const memory&);

protected:
  memory_fast_access<DT> mFastAccess;
};

template <typename DT>
inline
void
memory<DT>::
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
memory<DT>::
put(unsigned long long address,
    const unsigned char* data,
    unsigned int dataLength)
{
  put(address, data, dataLength, 0, 0);
}

template <typename DT>
inline
void
memory<DT>::
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
memory<DT>::
get(unsigned long long address,
    unsigned char* data,
    unsigned int dataLength) const
{
  get(address, data, dataLength, 0, 0);
}


template <typename DT>
inline
void
memory<DT>::
put(unsigned long long index,
    const DT& data,
    unsigned int size,
    unsigned int offset)
{
  mFastAccess.put(index, data, size, offset, false);
}

template <typename DT>
inline
void
memory<DT>::
put(unsigned long long index,
    const DT& data)
{
  mFastAccess.put(index, data, false);
}

template <typename DT>
inline
DT
memory<DT>::
get(unsigned long long index,
    unsigned int size,
    unsigned int offset) const
{
  return mFastAccess.get(index, size, offset, false);
}

template <typename DT>
inline
DT
memory<DT>::
get(unsigned long long index) const
{
  return mFastAccess.get(index, false);
}

template <typename DT>
inline
void
memory<DT>::
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
memory<DT>::
put_debug(unsigned long long address,
          const unsigned char* data,
          unsigned int dataLength)
{
  put_debug(address, data, dataLength, 0, 0);
}

template <typename DT>
inline
void
memory<DT>::
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
memory<DT>::
get_debug(unsigned long long address,
          unsigned char* data,
          unsigned int dataLength) const
{
  get_debug(address, data, dataLength, 0, 0);
}


template <typename DT>
inline
void
memory<DT>::
put_debug(unsigned long long index,
          const DT& data,
          unsigned int size,
          unsigned int offset)
{
  mFastAccess.put(index, data, size, offset, true);
}

template <typename DT>
inline
void
memory<DT>::
put_debug(unsigned long long index,
          const DT& data)
{
  mFastAccess.put(index, data, true);
}

template <typename DT>
inline
DT
memory<DT>::
get_debug(unsigned long long index,
          unsigned int size,
          unsigned int offset) const
{
  return mFastAccess.get(index, size, offset, true);
}

template <typename DT>
inline
DT
memory<DT>::
get_debug(unsigned long long index) const
{
  return mFastAccess.get(index, true);
}

template <typename DT>
inline
tlm::tlm_response_status
memory<DT>::
put_with_triggering_callbacks(unsigned long long index,
                              const DT& data,
                              unsigned int size,
                              unsigned int offset,
                              sc_core::sc_time& t)
{
  return put_with_triggering_callbacks(index_to_address<DT>(index) + offset,
                                       dt_to_array<DT>(data),
                                       size,
                                       t);
}

template <typename DT>
inline
tlm::tlm_response_status
memory<DT>::
put_with_triggering_callbacks(unsigned long long index,
                              const DT& data,
                              sc_core::sc_time& t)
{
  return put_with_triggering_callbacks(index,
                                       data,
                                       sizeOf<DT>(),
                                       0,
                                       t);
}

template <typename DT>
inline
tlm::tlm_response_status
memory<DT>::
get_with_triggering_callbacks(unsigned long long index,
                              DT& data,
                              unsigned int size,
                              unsigned int offset,
                              sc_core::sc_time& t)
{
  dt_from_array<DT> x(data, size);
  return get_with_triggering_callbacks(index_to_address<DT>(index) + offset,
                                       x,
                                       size,
                                       t);
}

template <typename DT>
inline
tlm::tlm_response_status
memory<DT>::
get_with_triggering_callbacks(unsigned long long index,
                              DT& data,
                              sc_core::sc_time& t)
{
  return get_with_triggering_callbacks(index,
                                       data,
                                       sizeOf<DT>(),
                                       0,
                                       t);
}

template <typename DT>
inline
unsigned int
memory<DT>::
put_debug_with_triggering_callbacks(unsigned long long index,
                                    const DT& data,
                                    unsigned int size,
                                    unsigned int offset)
{
  return put_debug_with_triggering_callbacks(index_to_address<DT>(index) + offset,
                                             dt_to_array<DT>(data),
                                             size);
}

template <typename DT>
inline
unsigned int
memory<DT>::
put_debug_with_triggering_callbacks(unsigned long long index,
                                    const DT& data)
{
  return put_debug_with_triggering_callbacks(index,
                                             data,
                                             sizeOf<DT>(),
                                             0);
}

template <typename DT>
inline
unsigned int
memory<DT>::
get_debug_with_triggering_callbacks(unsigned long long index,
                                    DT& data,
                                    unsigned int size,
                                    unsigned int offset)
{
  return get_debug_with_triggering_callbacks(index_to_address<DT>(index) + offset,
                                             dt_from_array<DT>(data, size),
                                             size);
}

template <typename DT>
inline
unsigned int
memory<DT>::
get_debug_with_triggering_callbacks(unsigned long long index,
                                    DT& data)
{
  return get_debug_with_triggering_callbacks(index,
                                             data,
                                             sizeOf<DT>(),
                                             0);
}

template <typename DT>
inline
void
memory<DT>::
transport_without_triggering_callbacks(tlm::tlm_generic_payload& trans)
{
  mFastAccess.transport(trans);
}

template <typename DT>
inline
void
memory<DT>::
transport_debug_without_triggering_callbacks(tlm::tlm_generic_payload& trans)
{
  mFastAccess.transport_debug(trans);
}

template <typename DT>
inline
typename memory<DT>::reference
memory<DT>::
operator[](unsigned long long index)
{
  return reference(this, index);
}

template <typename DT>
inline
DT
memory<DT>::
operator[](unsigned long long index) const
{
  return get(index);
}

template <typename DT>
inline
typename memory<DT>::iterator
memory<DT>::
begin()
{
  return iterator(this, 0);
}

template <typename DT>
inline
typename memory<DT>::const_iterator
memory<DT>::
begin() const
{
  return const_iterator(this, 0);
}

template <typename DT>
inline
typename memory<DT>::iterator
memory<DT>::
end()
{
  return begin() + get_size();
}

template <typename DT>
inline
typename memory<DT>::const_iterator
memory<DT>::
end() const
{
  return begin() + get_size();
}

}

#endif
