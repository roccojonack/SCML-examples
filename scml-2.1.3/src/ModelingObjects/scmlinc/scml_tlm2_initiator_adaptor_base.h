/*****************************************************************************
 *                   Copyright (C) 2008-2010 Synopsys, Inc.                  *
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
 * Purpose of file : Definition of the scml_tlm2_initiator_adaptor_base
 *
 */

#ifndef SCML_TLM2_INITIATOR_ADAPTOR_BASE_H
#define SCML_TLM2_INITIATOR_ADAPTOR_BASE_H

#include "scmlinc/scml_mapable_if.h"
#include "scmlinc/scml_pool.h"
#include <tlm.h>
#include <scml2_logging/stream.h>

template <typename T> class scml_mapable_if_to_T;

class scml_tlm2_initiator_adaptor_base :
  public tlm::tlm_mm_interface,
  public sc_core::sc_module
{
public:
  scml_tlm2_initiator_adaptor_base(sc_core::sc_module_name name, unsigned int busWidth);
  ~scml_tlm2_initiator_adaptor_base();

  void set_endianness(scml_endian e);
  scml_endian get_endianness() const;

public:
  // conversion operator to scml_mapable_if
  template <typename T> friend class scml_mapable_if_to_T;
  operator scml_mapable_if&();
  operator const scml_mapable_if&() const;

  virtual const char* getName() const { return name(); }


  // FIXME
  virtual void setPVInterfaceType(scml::PVInterfaceType /*pvInterfaceType*/) {}
  virtual scml::PVInterfaceType getPVInterfaceType() const { return scml::PV_INTERFACE_UNKNOWN; }

  #define TRANSPORT(IF) \
    virtual IF::response_type transport(const IF::request_type& req);
  SCML_FOR_EACH_PV_INTERFACE_TYPE(TRANSPORT)
  #undef TRANSPORT

protected:
  virtual void forwardTransaction(tlm::tlm_generic_payload& trans) = 0;
  virtual unsigned int forwardDebugTransaction(tlm::tlm_generic_payload& trans) = 0;


  virtual void register_port(sc_port_base& /*port*/, const char* /*if_typename*/) {}

private:
  template <typename IF>
  typename IF::response_type forwardRequest(const typename IF::request_type& req);

  void free(tlm::tlm_generic_payload* trans);


protected:
  mutable scml2::logging::stream mWarning;
  mutable scml2::logging::stream mError;

private:
  const unsigned int mBusWidth;
  scml_pool<tlm::tlm_generic_payload> mPool;
  bool mHasHostEndianness;
  scml_mapable_if* mMapableIf;
};

#endif

