/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_UTILS_H
#define SCML2_UTILS_H

#include <systemc>
#include <tlm.h>

#include <string>
#include <cstring>
#include <cassert>

#define SCML2_FOR_EACH_DT(doit) \
  doit(unsigned char) \
  doit(unsigned short) \
  doit(unsigned int) \
  doit(unsigned long long) \
  doit(sc_dt::sc_biguint<128>) \
  doit(sc_dt::sc_biguint<256>) \
  doit(sc_dt::sc_biguint<512>)

namespace scml2 {

template <typename T>
struct SizeOf {
  enum { result = sizeof(T) };
};

template <int N>
struct SizeOf<sc_dt::sc_biguint<N> > {
  //FIXME: assert(N % 8 );
  enum { result = N / 8 };
};

template <typename T>
inline
unsigned int sizeOf()
{
  return SizeOf<T>::result;
}

inline
void
copy_data(unsigned char* to,
          const unsigned char* from,
          unsigned int dataLength,
          const unsigned char* byteEnablePtr = 0,
          unsigned int byteEnableLength = 0)
{
  assert(to);
  assert(from);
  if (byteEnablePtr) {
    assert(byteEnableLength);
    for (unsigned int i = 0; i < dataLength; ++i) {
      if (byteEnablePtr[i % byteEnableLength]) {
        to[i] = from[i];
      }
    }
  } else {
    memcpy(to, from, dataLength);
  }
}

template <typename DT>
inline
void
to_char_array(DT from,
              unsigned char* to,
              unsigned int size,
              unsigned int offset)
{
  if (size == sizeOf<DT>()) {
    assert(!offset);
    *reinterpret_cast<DT*>(to) = from;

  } else {
    memcpy(to, reinterpret_cast<unsigned char*>(&from) + offset, size);
  }
}

template <int N>
inline
void
to_char_array(const sc_dt::sc_biguint<N>& from,
              unsigned char* to,
              unsigned int size,
              unsigned int offset)
{
  // FIXME: only works on LE host
  for (unsigned int i = 0; i < size; ++i) {
    to[i] = ((from >> (8 * (i + offset))).to_uint()) & 0xff;
  }
}

template <typename DT>
inline
void
from_char_array(const unsigned char* from,
                DT& to,
                unsigned int size,
                unsigned int offset)
{
  if (size == sizeOf<DT>()) {
    assert(!offset);
    to = *reinterpret_cast<const DT*>(from);

  } else {
    memcpy(reinterpret_cast<unsigned char*>(&to) + offset, from, size);
  }
}

template <int N>
inline
void
from_char_array(const unsigned char* from,
                sc_dt::sc_biguint<N>& to,
                unsigned int size,
                unsigned int offset)
{
  // FIXME: only works on LE host
  to = 0;
  for (unsigned int i = 0; i < size; ++i) {
    to |= sc_dt::sc_biguint<N>(from[i]) << (8 * (i + offset));
  }
}

template <typename DT>
inline
DT
get_bit_mask(unsigned int size)
{
  DT mask = ~(DT)0;
  if(size >= 8*sizeOf<DT>()) {
    return mask;

  } else {
    mask <<= size;
    return ~mask;
  }
}

template <typename DT>
inline
DT
extract_bits(const DT& v,
             unsigned int sizeBits,
             unsigned int offsetBits)
{
  const DT mask = get_bit_mask<DT>(sizeBits);

  return (v >> offsetBits) & mask;
}

template <typename DT>
inline
DT
insert_bits(const DT& v,
            const DT& rhs,
            unsigned int sizeBits,
            unsigned int offsetBits)
{
  DT mask = get_bit_mask<DT>(sizeBits);

  DT new_data = (rhs & mask);
  mask <<= offsetBits;
  new_data <<= offsetBits;

  return (v & ~mask) | new_data;
}

inline
unsigned long long
address_to_index(unsigned long long address, unsigned int width)
{
  return address / width;
}

template <typename DT>
inline
unsigned long long
address_to_index(unsigned long long address)
{
  return address_to_index(address, sizeOf<DT>());
}

inline
unsigned long long
index_to_address(unsigned long long index, unsigned int width)
{
  return index * width;
}

template <typename DT>
inline
unsigned long long
index_to_address(unsigned long long index)
{
  return index_to_address(index, sizeOf<DT>());
}

//FIXME
inline
void
copy_extension_pointers(tlm::tlm_generic_payload& from,
                        tlm::tlm_generic_payload& to)
{
  for (unsigned int i = 0; i < tlm::max_num_extensions(); ++i) {
    to.set_extension(i, from.get_extension(i));
  }
}

inline
void
clear_extension_pointers(tlm::tlm_generic_payload& trans)
{
  for (unsigned int i = 0; i < tlm::max_num_extensions(); ++i) {
    // FIXME: clear_extension is private
    trans.set_extension(i, 0);
  }
}

template <typename DT>
class dt_to_array
{
public:
  // FIXME: add size/offset?
  dt_to_array(const DT& v) :
    mArray(reinterpret_cast<const unsigned char*>(&v))
  {
  }

  operator const unsigned char*() const
  {
    return mArray;
  }

private:
  const unsigned char* mArray;
};

template <int N>
class dt_to_array<sc_dt::sc_biguint<N> >
{
public:
  // FIXME: add size/offset?
  dt_to_array(const sc_dt::sc_biguint<N>& v)
  {
    to_char_array(v, mArray, N / 8, 0);
  }

  operator const unsigned char*() const
  {
    return mArray;
  }

private:
  unsigned char mArray[N / 8];
};

template <typename DT>
class dt_from_array
{
public:
  // FIXME: add offset?
  dt_from_array(DT& v,
                unsigned int /* size */ = sizeof(DT),
                bool clearNotCopy = true) :
    mArray(reinterpret_cast<unsigned char*>(&v))
  {
    if (clearNotCopy) {
      v = 0;
    }
  }

  operator unsigned char*() const
  {
    return mArray;
  }

private:
  unsigned char* mArray;
};

template <int N>
class dt_from_array<sc_dt::sc_biguint<N> >
{
public:
  // FIXME: add offset?
  dt_from_array(sc_dt::sc_biguint<N>& v,
                unsigned int size = N / 8,
                bool clearNotCopy = true) :
    mValue(v),
    mSize(size)
  {
    if (clearNotCopy) {
      memset(mArray, 0, N / 8);

    } else {
      to_char_array(mValue, mArray, size, 0);
    }
  }

  ~dt_from_array()
  {
    from_char_array(mArray, mValue, mSize, 0);
  }

  operator unsigned char*()
  {
    return mArray;
  }

private:
  unsigned char mArray[N / 8];
  sc_dt::sc_biguint<N>& mValue;
  unsigned int mSize;
};

template <typename DT>
class array_to_dt
{
public:
  explicit array_to_dt(const unsigned char* a,
                       unsigned int size = sizeof(DT),
                       unsigned int offset = 0) :
    mArray(a),
    mSize(size),
    mOffset(offset)
  {
  }

  operator DT() const
  {
    if (mSize == sizeof(DT)) {
      assert(!mOffset);
      return *reinterpret_cast<const DT*>(mArray);

    } else {
      DT value = 0;
      from_char_array(mArray, value, mSize, mOffset);
      return value;
    }
  }

private:
  const unsigned char* mArray;
  const unsigned int mSize;
  const unsigned int mOffset;
};

template <int N>
class array_to_dt<sc_dt::sc_biguint<N> >
{
public:
  array_to_dt(const unsigned char* a,
              unsigned int size = N / 8,
              unsigned int offset = 0)
  {
    from_char_array(a, mValue, size, offset);
  }

  operator const sc_dt::sc_biguint<N>&() const
  {
    return mValue;
  }

private:
  sc_dt::sc_biguint<N> mValue;
};

template <typename DT>
class array_from_dt
{
public:
  array_from_dt(unsigned char* a,
                unsigned int size = sizeof(DT),
                unsigned int offset = 0,
                bool clearNotCopy = true) :
    mArray(a),
    mSize(size),
    mOffset(offset)
  {
    if (clearNotCopy) {
      mValue = 0;

    } else {
      from_char_array(a, mValue, mSize, mOffset);
    }
  }

  ~array_from_dt()
  {
    to_char_array(mValue, mArray, mSize, mOffset);
  }

  operator DT&()
  {
    return mValue;
  }

private:
  unsigned char* mArray;
  unsigned int mSize;
  unsigned int mOffset;
  DT mValue;
};

template <int N>
class array_from_dt<sc_dt::sc_biguint<N> >
{
public:
  array_from_dt(unsigned char* a,
                unsigned int size = N / 8,
                unsigned int offset = 0,
                bool clearNotCopy = true) :
    mArray(a),
    mSize(size),
    mOffset(offset)
  {
    if (clearNotCopy) {
      mValue = 0;

    } else {
      from_char_array(a, mValue, mSize, mOffset);
    }
  }

  ~array_from_dt()
  {
    to_char_array(mValue, mArray, mSize, mOffset);
  }

  operator sc_dt::sc_biguint<N>&()
  {
    return mValue;
  }

private:
  unsigned char* mArray;
  unsigned int mSize;
  unsigned int mOffset;
  sc_dt::sc_biguint<N> mValue;
};

//FIXME
inline
std::string
create_hierarchical_sc_name(const std::string& n)
{
  const sc_core::sc_simcontext* context = sc_core::sc_get_curr_simcontext();

  std::string name;
  if(context) {
    const sc_core::sc_module* module = context->hierarchy_curr();
    if(module) {
      name = module->name();
      if (!n.empty()) {
        name += '.';
      }
    }
  }
  name += n;
  return name;
}

}

#endif
