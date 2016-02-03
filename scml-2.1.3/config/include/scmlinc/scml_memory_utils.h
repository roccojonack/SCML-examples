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
 * Purpose of file : Utilities for scml_memory modeling object
 *
 */

#ifndef SCML_MEMORY_UTILS_H
#define SCML_MEMORY_UTILS_H

#include "scmlinc/scml_types.h"
#include "scmlinc/scml_memory_pv_if.h"

namespace  scml_memory_utils {
  extern cwrMas defaultMas(unsigned int d);
  extern bool hasHostEndianness( cwrEnd endianness);

  inline cwrMas convertPVdataSize2cwrMas( unsigned int d)
  {
    unsigned int result = (d >> 3) - 1;

    if (result > (unsigned int) cwrMas128 || (d & 0x7) != 0) {
      return defaultMas(d);
    }

    return (cwrMas) result;
  }


  inline cwrEnd convert_scml_to_cwrEnd( scml_endian endianness)
  {
    if( scml_big_endian == endianness) {
      return cwrBigend;
    }
    return cwrLitend;
  }

  inline scml_endian convert_cwrEnd_to_scml( cwrEnd endianness)
  {
    if( cwrBigend == endianness) {
      return scml_big_endian;
    }
    return scml_little_endian;
  }
  
    
  
  // Increment/Decrement helpers, with expected behavior for 'bool'
  // Return the increment/decrement of a value
  template <typename DT>
  inline DT do_inc(const DT& value)
  {
    return value+1;
  }
  
  template <typename DT>
  inline DT do_dec(const DT& value)
  {
    return value-1;
  }
  
  // Overload for 'bool'
  inline bool do_inc(bool /*value*/)
  {
    return true;
  }
  
  inline bool do_dec(bool /*value*/)
  {
    return false;
  }
  
  // Helpers for swapping bytes around
  inline unsigned char swap_bytes(unsigned char rhs)  { return rhs; }
  inline char swap_bytes(char rhs) { return rhs; }
  inline signed char swap_bytes(signed char rhs) { return rhs; }
  
#ifdef __linux__
#include <byteswap.h>
  
  inline unsigned short swap_bytes(unsigned short v) { return bswap_16(v); }
  inline signed short swap_bytes(signed short v) { return bswap_16(v); }

  inline unsigned int swap_bytes(unsigned int v) { return bswap_32(v); }
  inline signed int swap_bytes(signed int v) { return bswap_32(v); }
  
# if __WORDSIZE == 64
  inline unsigned long swap_bytes(unsigned long v) { return bswap_64(v); }
  inline signed long swap_bytes(signed long v) { return bswap_64(v); }
# else
  inline unsigned long swap_bytes(unsigned long v) { return bswap_32(v); }
  inline signed long swap_bytes(signed long v) { return bswap_32(v); }
# endif

  inline unsigned long long swap_bytes(unsigned long long v) { return bswap_64(v); }
  inline signed long long swap_bytes(signed long long v) { return bswap_64(v); }

#else

  inline unsigned short swap_bytes(unsigned short rhs) { return (rhs >> 8) | (rhs << 8); }
  inline signed short swap_bytes(signed short rhs) { return swap_bytes((unsigned short)rhs); }
  
  inline unsigned int swap_bytes(unsigned int rhs) { return (rhs << 24) | (rhs >> 24) | ((rhs << 8) & 0x00FF0000) | ((rhs >> 8) & 0x0000FF00); }
  inline signed int swap_bytes(signed int rhs) { return swap_bytes((unsigned int)rhs); }
  
  // assuming long is 32 bit as with WIN64
  inline unsigned long swap_bytes(unsigned long rhs) { return swap_bytes((unsigned int)rhs); }
  inline signed long swap_bytes(signed long rhs) { return swap_bytes((signed int)rhs); }

  inline unsigned long long swap_bytes(unsigned long long rhs) { return (static_cast<unsigned long long>(swap_bytes((unsigned int)rhs)) << 32) | swap_bytes((unsigned int)(rhs >> 32)); }
  inline signed long long swap_bytes(signed long long rhs) { return swap_bytes((unsigned long long)rhs); }

#endif
  
  template <typename DT>
  inline DT getBitsMask(unsigned int size)
  {
    DT mask = ~(DT)0;
    if(size >= 8*scml::sizeOf<DT>()) {
      return mask;

    } else {
      mask <<= size;
      return ~mask;
    }
  }
     
  template <typename DT>
  inline DT extractBits(const DT v, unsigned int offset, unsigned int acSize)
  {
    const DT mask = getBitsMask<DT>(acSize);
    
    return (v >> offset) & mask;
  }

  template <typename DT>
  inline DT insertBits(const DT rhs, const DT v, unsigned int offset, unsigned int acSize)
  {
    DT mask = getBitsMask<DT>(acSize);
    
    DT new_data = (rhs & mask);
    mask <<= offset;
    new_data <<= offset;

    return (v & ~mask) | new_data;
  }

};

#endif
