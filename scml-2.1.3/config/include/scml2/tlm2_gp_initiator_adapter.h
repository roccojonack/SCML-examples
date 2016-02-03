/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_TLM2_GP_INITIATOR_ADAPTER_H
#define SCML2_TLM2_GP_INITIATOR_ADAPTER_H

#include <scml2/mappable_if.h>

#include <scml2_logging/stream.h>
#include <scml2_logging/severity.h>
#include <tlm.h>
#include <systemc>
#include <set>
#include <string>
#include <cassert>

namespace scml2 {

template <unsigned int BUSWIDTH,
          int N = 1,
          sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND>
class tlm2_gp_initiator_adapter :
  public sc_core::sc_object,
  public mappable_if,
  public tlm::tlm_bw_transport_if<>
{
public:
  typedef tlm::tlm_base_initiator_socket<BUSWIDTH,
                                         tlm::tlm_fw_transport_if<>,
                                         tlm::tlm_bw_transport_if<>,
                                         N,
                                         POL> socket_type;

public:
  tlm2_gp_initiator_adapter(const std::string& name, socket_type& s);
  virtual ~tlm2_gp_initiator_adapter();

  std::string get_name() const;

  virtual std::string get_mapped_name() const;

  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  virtual void register_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface);
  virtual void unregister_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface);

protected:
  virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload& trans,
                                             tlm::tlm_phase& phase,
                                             sc_core::sc_time& t);
  virtual void invalidate_direct_mem_ptr(unsigned long long startRange,
                                         unsigned long long endRange);

protected:
  socket_type& mSocket;
  std::set<tlm::tlm_bw_direct_mem_if*> mBwDirectMemIfs;
  mutable logging::stream mInternalError;
};

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
tlm2_gp_initiator_adapter(const std::string& name, socket_type& s) :
  sc_core::sc_object(name.c_str()),
  mSocket(s),
  mInternalError(this->name(), logging::severity::internal_error())
{
  mSocket(*this);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
~tlm2_gp_initiator_adapter()
{
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
std::string
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
get_name() const
{
  return name();
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
std::string
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
get_mapped_name() const
{
  return mSocket.name();
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
void
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  mSocket->b_transport(trans, t);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
bool
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmiData)
{
  return mSocket->get_direct_mem_ptr(trans, dmiData);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
unsigned int
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
transport_dbg(tlm::tlm_generic_payload& trans)
{
  return mSocket->transport_dbg(trans);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
void
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
register_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  assert(bwInterface);
  mBwDirectMemIfs.insert(bwInterface);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
void
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
unregister_bw_direct_mem_if(tlm::tlm_bw_direct_mem_if* bwInterface)
{
  mBwDirectMemIfs.erase(bwInterface);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
tlm::tlm_sync_enum
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
nb_transport_bw(tlm::tlm_generic_payload&,
                tlm::tlm_phase&,
                sc_core::sc_time&)
{
  SCML2_LOG(mInternalError) << "unexpected 'nb_transport_bw' call" << std::endl;
  return tlm::TLM_COMPLETED;
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
void
tlm2_gp_initiator_adapter<BUSWIDTH, N, POL>::
invalidate_direct_mem_ptr(unsigned long long startRange,
                          unsigned long long endRange)
{
  std::set<tlm::tlm_bw_direct_mem_if*>::iterator it = mBwDirectMemIfs.begin();
  std::set<tlm::tlm_bw_direct_mem_if*>::const_iterator end = mBwDirectMemIfs.end();
  for (; it != end; ++it) {
    (*it)->invalidate_direct_mem_ptr(startRange, endRange);
  }
}

}

#endif
