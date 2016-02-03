/*****************************************************************************
 *                   Copyright (C) 1996-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
/*
 * Modifications :
 *
 * Purpose of file : 
 *
 */

#ifndef SCML_TYPE_H
#define SCML_TYPE_H

#include <systemc>

enum scml_endian { scml_little_endian, scml_big_endian };

namespace scml {
  enum AccessType { ACCESS_TYPE_UNKNOWN = 0,
                    ACCESS_TYPE_READ    = 1,
                    ACCESS_TYPE_WRITE   = 2,
                    ACCESS_TYPE_ACCESS  = 3 };
  enum AccessMode { ACCESS_MODE_UNKNOWN = 0,
                    ACCESS_MODE_REGULAR = 1,
                    ACCESS_MODE_DEBUG   = 2,
                    ACCESS_MODE_ACCESS  = 3 };


  enum PVInterfaceType { PV_INTERFACE_UNKNOWN,
                         PV_INTERFACE_32_32,
                         PV_INTERFACE_32_64,
                         PV_INTERFACE_32_128,
                         PV_INTERFACE_32_256,
                         PV_INTERFACE_32_512,
                         PV_INTERFACE_64_32,
                         PV_INTERFACE_64_64,
                         PV_INTERFACE_64_128,
                         PV_INTERFACE_64_256,
                         PV_INTERFACE_64_512,
                         // FIXME: Backwards compatibility
                         PV_INTERFACE_32 = PV_INTERFACE_32_32,
                         PV_INTERFACE_64 = PV_INTERFACE_32_64,
                         PV_INTERFACE_128 = PV_INTERFACE_32_128,
                         PV_INTERFACE_256 = PV_INTERFACE_32_256,
                         PV_INTERFACE_512 = PV_INTERFACE_32_512
                       };

  //
  // convert
  //
  template <typename T> struct Type2Type {};

  // FIXME: No partial template specialization for functions (use overload)
  template <typename FROM, typename TO> inline TO convert(const FROM& x, const Type2Type<TO>&) { return x; }
  template <int N> inline bool convert(const sc_dt::sc_biguint<N>& x, const Type2Type<bool>&) { return x != 0; }
  template <int N> inline char convert(const sc_dt::sc_biguint<N>& x, const Type2Type<char>&) { return x.to_int(); }
  template <int N> inline unsigned char convert(const sc_dt::sc_biguint<N>& x, const Type2Type<unsigned char>&) { return x.to_uint(); }
  template <int N> inline signed char convert(const sc_dt::sc_biguint<N>& x, const Type2Type<signed char>&) { return x.to_int(); }
  template <int N> inline signed short convert(const sc_dt::sc_biguint<N>& x, const Type2Type<signed short>&) { return x.to_int(); }
  template <int N> inline unsigned short convert(const sc_dt::sc_biguint<N>& x, const Type2Type<unsigned short>&) { return x.to_uint(); }
  template <int N> inline signed int convert(const sc_dt::sc_biguint<N>& x, const Type2Type<signed int>&) { return x.to_int(); }
  template <int N> inline unsigned int convert(const sc_dt::sc_biguint<N>& x, const Type2Type<unsigned int>&) { return x.to_uint(); }
  template <int N> inline signed long convert(const sc_dt::sc_biguint<N>& x, const Type2Type<signed long>&) { return x.to_long(); }
  template <int N> inline unsigned long convert(const sc_dt::sc_biguint<N>& x, const Type2Type<unsigned long>&) { return x.to_ulong(); }
  template <int N> inline signed long long convert(const sc_dt::sc_biguint<N>& x, const Type2Type<signed long long>&) { return x.to_int64(); }
  template <int N> inline unsigned long long convert(const sc_dt::sc_biguint<N>& x, const Type2Type<unsigned long long>&) { return x.to_uint64(); }

  template <typename FROM, typename TO> inline TO convert(const FROM& x) { return convert(x, Type2Type<TO>()); }

  //
  // sizeOf
  //

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

  //
  // copy to/from array
  //
  template <typename T>
  inline void copyToArray(const T& v, unsigned char* a)
  {
    for (unsigned int i = 0; i < sizeOf<T>(); ++i) {
      a[i] = convert<T, unsigned char>(v >> (8 * i));
    }
  }

  template <typename T>
  inline void copyFromArray(T& v, unsigned char* a)
  {
    v = 0;
    for (unsigned int i = 0; i < sizeOf<T>(); ++i) {
      v |= convert<unsigned char, T>(a[i]) << (i * 8);
    }
  }

  template <typename T>
  inline void swapToArray(const T& v, unsigned char* a)
  {
    for (unsigned int i = 0; i < sizeOf<T >(); ++i) {
      a[i] = convert<T, unsigned char>(v >> (8 * (sizeOf<T>() - 1 - i)));
    }
  }

  template <typename T>
  inline void swapFromArray(T& v, unsigned char* a)
  {
    v = 0;
    for (unsigned int i = 0; i < sizeOf<T>(); ++i) {
      v |= (convert<unsigned char, T>(a[i]) << (8 * (sizeOf<T>() - 1 - i)));
    }
  }

}

typedef enum cwrMas {
  cwrMas08  = 0x00,
  cwrMas16  = 0x01,
  cwrMas24  = 0x02,
  cwrMas32  = 0x03,
  cwrMas40  = 0x04,
  cwrMas48  = 0x05,
  cwrMas56  = 0x06,
  cwrMas64  = 0x07,
  cwrMas96  = 0x08,
  cwrMas128 = 0x09
} cwrMas;

const int CWR_MAS_COUNT = 11;

typedef enum cwrEnd { 
  cwrLitend = 0x00,
  cwrBigend = 0x01,
  cwrUndefend = 0x02
} cwrEnd;

typedef unsigned int cwrMem32;
typedef unsigned long long cwrMem64;


#endif
