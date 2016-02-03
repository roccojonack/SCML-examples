/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ROUTER_BASE_H
#define SCML2_ROUTER_BASE_H

#include <scml2/memory_region.h>
#include <scml2/burst_unroller.h>
#include <scml2/debug_burst_unroller.h>
#include <scml2/mapped_ranges_observers.h>
#include <scml2/mappable_if.h>
#include <scml2/streams.h>

#include <scml2_logging/stream.h>
#include <tlm.h>
#include <list>
#include <set>
#include <vector>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

class Initializer;
class mapped_range;
class router_callback_base;
class router_debug_callback_base;

class router_base :
  public memory_region,
  public burst_unroller,
  public debug_burst_unroller,
  public mappable_if,
  public tlm::tlm_bw_direct_mem_if
{
private:
  typedef std::list<mapped_range*> MappedRanges;
  typedef MappedRanges::iterator MappedRangesIter;
  typedef MappedRanges::const_iterator MappedRangesConstIter;

public:
  router_base(const std::string& name,
              unsigned long long size,
              unsigned int width);
  virtual ~router_base();

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

  bool map(unsigned long long base,
           unsigned long long size,
           mappable_if& ifs,
           unsigned long long offset);
  bool map_read(unsigned long long base,
                unsigned long long size,
                mappable_if& ifs,
                unsigned long long offset);
  bool map_write(unsigned long long base,
                 unsigned long long size,
                 mappable_if& ifs,
                 unsigned long long offset);

  bool unmap(unsigned long long base);
  bool unmap_read(unsigned long long base);
  bool unmap_write(unsigned long long base);
  void unmap_all();

  unsigned int collect_mapped_read_ranges(std::vector<mapped_range*>& v) const;
  mapped_range* get_mapped_read_range(unsigned long long address) const;
  unsigned int collect_mapped_write_ranges(std::vector<mapped_range*>& v) const;
  mapped_range* get_mapped_write_range(unsigned long long address) const;

  void set_callback(router_callback_base* cb);
  void set_debug_callback(router_debug_callback_base* cb);

  router_callback_base* get_callback() const;
  router_debug_callback_base* get_debug_callback() const;

  virtual std::string get_mapped_name() const;

  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  virtual void register_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface);
  virtual void unregister_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface);

  virtual void invalidate_direct_mem_ptr(unsigned long long startRange,
                                         unsigned long long endRange);

  // Debugger API
  virtual unsigned int read(unsigned long long address,
                            unsigned char* data,
                            unsigned int size);
  virtual unsigned int write(unsigned long long address,
                             const unsigned char* data,
                             unsigned int size);

  virtual void enable_dmi();
  virtual void disable_dmi();
  virtual bool is_dmi_enabled() const;

  bool register_mapped_ranges_observer(mapped_ranges_observer* o);
  bool unregister_all_mapped_ranges_observers();
  bool unregister_mapped_ranges_observer(mapped_ranges_observer* o);

  // sc_object
  virtual const char* kind() const;

protected:
   virtual void invalidate_dmi();
   virtual void process_unrolled_transaction(tlm::tlm_generic_payload& trans,
                                             sc_core::sc_time& t);
   virtual unsigned int process_unrolled_debug_transaction(tlm::tlm_generic_payload& trans);

private:
  bool checkRange(unsigned long long base, unsigned long long size) const;
  bool checkOverlap(unsigned long long base, unsigned long long size) const;
  bool checkOverlap(const MappedRanges& ranges,
                    unsigned long long base,
                    unsigned long long size) const;

  bool unmap(MappedRanges& ranges, unsigned long long base);
  static mapped_range* getMappedRange(MappedRanges& ranges,
                                      unsigned long long address);

private:
  friend class Initializer;
  typedef void (*PostConstructorCallback)(router_base&);
  static void set_post_constructor_callback(PostConstructorCallback c);
  static PostConstructorCallback mPostConstructorCallback;

private:
  streams* mTheStreams;

  mutable MappedRanges mMappedReadRanges;
  mutable MappedRanges mMappedWriteRanges;

  router_callback_base* mCallback;
  router_debug_callback_base* mDebugCallback;

  bool mDmiPointersInUse;
  std::set<tlm::tlm_bw_direct_mem_if*> mBwDirectMemIfs;

  bool mDmiEnabled;

  mapped_ranges_observers mMappedRangesObservers;
};

inline
tlm::tlm_response_status
router_base::
put_with_triggering_callbacks(unsigned long long address,
                              const unsigned char* data,
                              unsigned int dataLength,
                              const unsigned char* byteEnablePtr,
                              unsigned int byteEnableLength,
                              sc_core::sc_time& t)
{
  // FIXME: pool
  tlm::tlm_generic_payload trans;
  trans.set_address(address);
  trans.set_write();
  trans.set_data_ptr(const_cast<unsigned char*>(data));
  trans.set_data_length(dataLength);
  trans.set_byte_enable_ptr(const_cast<unsigned char*>(byteEnablePtr));
  trans.set_byte_enable_length(byteEnableLength);
  trans.set_streaming_width(dataLength);
  b_transport(trans, t);
  return trans.get_response_status();
}

inline
tlm::tlm_response_status
router_base::
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

inline
tlm::tlm_response_status
router_base::
get_with_triggering_callbacks(unsigned long long address,
                              unsigned char* data,
                              unsigned int dataLength,
                              const unsigned char* byteEnablePtr,
                              unsigned int byteEnableLength,
                              sc_core::sc_time& t)
{
  // FIXME: pool
  tlm::tlm_generic_payload trans;
  trans.set_address(address);
  trans.set_read();
  trans.set_data_ptr(data);
  trans.set_data_length(dataLength);
  trans.set_byte_enable_ptr(const_cast<unsigned char*>(byteEnablePtr));
  trans.set_byte_enable_length(byteEnableLength);
  trans.set_streaming_width(dataLength);
  b_transport(trans, t);
  return trans.get_response_status();
}

inline
tlm::tlm_response_status
router_base::
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

inline
unsigned int
router_base::
put_debug_with_triggering_callbacks(unsigned long long address,
                                    const unsigned char* data,
                                    unsigned int dataLength,
                                    const unsigned char* byteEnablePtr,
                                    unsigned int)
{
  if (byteEnablePtr) {
    SCML2_LOG(get_streams().error())
      << "byteEnablePtr should be 0x0 for"
      << " put_debug_with_triggering_callbacks."
      << " TLM2 does not support byte enables for debug transactions"
      << std::endl;
  }

  // FIXME: pool
  tlm::tlm_generic_payload trans;
  trans.set_address(address);
  trans.set_write();
  trans.set_data_ptr(const_cast<unsigned char*>(data));
  trans.set_data_length(dataLength);
  trans.set_byte_enable_ptr(0x0);
  trans.set_streaming_width(dataLength);
  return transport_dbg(trans);
}

inline
unsigned int
router_base::
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

inline
unsigned int
router_base::
get_debug_with_triggering_callbacks(unsigned long long address,
                                    unsigned char* data,
                                    unsigned int dataLength,
                                    const unsigned char* byteEnablePtr,
                                    unsigned int)
{
  if (byteEnablePtr) {
    SCML2_LOG(get_streams().error())
      << "byteEnablePtr should be 0x0 for"
      << " get_debug_with_triggering_callbacks."
      << " TLM2 does not support byte enables for debug transactions"
      << std::endl;
  }

  // FIXME: pool
  tlm::tlm_generic_payload trans;
  trans.set_address(address);
  trans.set_read();
  trans.set_data_ptr(data);
  trans.set_data_length(dataLength);
  trans.set_byte_enable_ptr(0x0);
  trans.set_streaming_width(dataLength);
  return transport_dbg(trans);
}

inline
unsigned int
router_base::
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

}

#endif
