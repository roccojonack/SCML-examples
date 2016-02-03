/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_SLOW_ACCESS_STORAGE_DECORATOR_H
#define SCML2_MEMORY_SLOW_ACCESS_STORAGE_DECORATOR_H

#include <scml2/memory_storage_base.h>
#include <scml2/utils.h>

namespace scml2 {

template <typename DT>
class memory_slow_access_storage_decorator
{
public:
  memory_slow_access_storage_decorator(memory_storage_base& storage,
                                       unsigned long long offset);

  unsigned char* get_fast_backdoor() const;

  void put(unsigned long long address,
           const unsigned char* data,
           unsigned int dataLength,
           const unsigned char* byteEnablePtr,
           unsigned int byteEnableLength,
           bool isDebug = false);
  void get(unsigned long long address,
           unsigned char* data,
           unsigned int dataLength,
           const unsigned char* byteEnablePtr,
           unsigned int byteEnableLength,
           bool isDebug = false) const;

  void put(unsigned long long index,
           DT data,
           unsigned int size,
           unsigned int offset,
           bool isDebug = false);
  void put(unsigned long long index,
           DT data,
           bool isDebug = false);
  DT get(unsigned long long index,
         unsigned int size,
         unsigned int offset,
         bool isDebug = false) const;
  DT get(unsigned long long index,
         bool isDebug = false) const;

private:
  void write(unsigned long long address,
             const unsigned char* data,
             unsigned int dataLength,
             const unsigned char* byteEnablePtr,
             unsigned int byteEnableLength);
  void read(unsigned long long address,
            unsigned char* data,
            unsigned int dataLength,
            const unsigned char* byteEnablePtr,
            unsigned int byteEnableLength) const;

private:
  memory_storage_base& mStorage;
  unsigned long long mOffset;
};

template <typename DT>
inline
memory_slow_access_storage_decorator<DT>::
memory_slow_access_storage_decorator(memory_storage_base& storage,
                                     unsigned long long offset) :
  mStorage(storage),
  mOffset(offset)
{
}

template <typename DT>
inline
unsigned char*
memory_slow_access_storage_decorator<DT>::
get_fast_backdoor() const
{
 unsigned char* fastBackdoor = mStorage.get_fast_backdoor();
 if (fastBackdoor) {
   fastBackdoor -= index_to_address<DT>(mOffset);
 }
 return fastBackdoor;
}

template <typename DT>
inline
void
memory_slow_access_storage_decorator<DT>::
write(unsigned long long address,
      const unsigned char* data,
      unsigned int dataLength,
      const unsigned char* byteEnablePtr,
      unsigned int byteEnableLength)
{
  const unsigned long long toplevelAddress =
    address + index_to_address<DT>(mOffset);
  if (byteEnablePtr) {
    for (unsigned int i = 0; i < dataLength; ++i) {
      if (byteEnablePtr[i % byteEnableLength]) {
        mStorage.write(toplevelAddress + i,
                       data + i,
                       1);
      }
    }

  } else {
    mStorage.write(toplevelAddress,
                   data,
                   dataLength);
  }
}

template <typename DT>
inline
void
memory_slow_access_storage_decorator<DT>::
read(unsigned long long address,
     unsigned char* data,
     unsigned int dataLength,
     const unsigned char* byteEnablePtr,
     unsigned int byteEnableLength) const
{
  const unsigned long long toplevelAddress =
    address + index_to_address<DT>(mOffset);
  if (byteEnablePtr) {
    for (unsigned int i = 0; i < dataLength; ++i) {
      if (byteEnablePtr[i % byteEnableLength]) {
        mStorage.read(toplevelAddress + i,
                      data + i,
                      1);
      }
    }

  } else {
    mStorage.read(toplevelAddress,
                  data,
                  dataLength);
  }
}

template <typename DT>
inline
void
memory_slow_access_storage_decorator<DT>::
put(unsigned long long address,
    const unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength,
    bool)
{
  write(address, data, dataLength, byteEnablePtr, byteEnableLength);
}

template <typename DT>
inline
void
memory_slow_access_storage_decorator<DT>::
get(unsigned long long address,
    unsigned char* data,
    unsigned int dataLength,
    const unsigned char* byteEnablePtr,
    unsigned int byteEnableLength,
    bool) const
{
  read(address, data, dataLength, byteEnablePtr, byteEnableLength);
}

template <typename DT>
inline
void
memory_slow_access_storage_decorator<DT>::
put(unsigned long long index,
    DT data,
    unsigned int size,
    unsigned int offset,
    bool)
{
  write(index_to_address<DT>(index) + offset,
        dt_to_array<DT>(data),
        size,
        0,
        0);
}

template <typename DT>
inline
void
memory_slow_access_storage_decorator<DT>::
put(unsigned long long index,
    DT data,
    bool isDebug)
{
  put(index, data, sizeOf<DT>(), 0, isDebug);
}

template <typename DT>
inline
DT
memory_slow_access_storage_decorator<DT>::
get(unsigned long long index,
    unsigned int size,
    unsigned int offset,
    bool) const
{
  DT value = 0;
  read(index_to_address<DT>(index) + offset,
       dt_from_array<DT>(value, size),
       size,
       0,
       0);
  return value;
}

template <typename DT>
inline
DT
memory_slow_access_storage_decorator<DT>::
get(unsigned long long index,
    bool isDebug) const
{
  return get(index, sizeOf<DT>(), 0, isDebug);
}

}

#endif
