/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MAPPED_RANGE_H
#define SCML2_MAPPED_RANGE_H

#include <scml2/mappable_if.h>
#include <string>

namespace tlm {
  class tlm_generic_payload;
  class tlm_bw_direct_mem_if;
  class tlm_dmi;
}

namespace sc_core {
  class sc_time;
}

namespace scml2 {

class mapped_range
{
public:
  mapped_range(unsigned long long b,
              unsigned long long s,
              mappable_if& d,
              unsigned long long o);

  unsigned long long get_base() const;
  unsigned long long get_size() const;
  unsigned long long get_offset() const;

  bool contains(unsigned long long address) const;

  unsigned long long mapped_address(unsigned long long address) const;
  unsigned long long unmapped_address(unsigned long long address) const;

  std::string get_mapped_name() const;

  void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData);
  unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  void register_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface);
  void unregister_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface);

private:
  unsigned long long mBase;
  unsigned long long mSize;
  mappable_if& mDest;
  unsigned long long mOffset;
};

inline
mapped_range::
mapped_range(unsigned long long b,
            unsigned long long s,
            mappable_if& d,
            unsigned long long o) :
  mBase(b),
  mSize(s),
  mDest(d),
  mOffset(o)
{
}

inline
unsigned long long
mapped_range::
get_base() const
{
  return mBase;
}

inline
unsigned long long
mapped_range::
get_size() const
{
  return mSize;
}

inline
unsigned long long
mapped_range::
get_offset() const
{
  return mOffset;
}

inline
bool
mapped_range::
contains(unsigned long long address) const
{
  return (mBase <= address && address <= (mBase + (mSize - 1)));
}

inline
unsigned long long
mapped_range::
mapped_address(unsigned long long address) const
{
  return ((address - mBase) + mOffset);
}

inline
unsigned long long
mapped_range::
unmapped_address(unsigned long long address) const
{
  return ((address - mOffset) + mBase);
}

inline
std::string
mapped_range::
get_mapped_name() const
{
  return mDest.get_mapped_name();
}

inline
void
mapped_range::
b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  mDest.b_transport(trans, t);
}

inline
bool
mapped_range::
get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData)
{
  return mDest.get_direct_mem_ptr(trans, dmiData);
}

inline
unsigned int
mapped_range::
transport_dbg(tlm::tlm_generic_payload& trans)
{
  return mDest.transport_dbg(trans);
}

inline
void
mapped_range::
register_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  mDest.register_bw_direct_mem_if(bwInterface);
}

inline
void
mapped_range::
unregister_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  mDest.unregister_bw_direct_mem_if(bwInterface);
}

}

#endif
