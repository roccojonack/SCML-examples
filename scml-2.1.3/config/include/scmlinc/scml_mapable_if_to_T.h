/*****************************************************************************
 *                   Copyright (C) 2007-2010 Synopsys, Inc.                  *
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
 * Purpose of file : Definition of the scml_mapable_if_to_T
 *
 */

#ifndef SCML_MAPABLE_IF_TO_T
#define SCML_MAPABLE_IF_TO_T

#include "scmlinc/scml_mapable_if.h"

template< typename T>
class scml_mapable_if_to_T : public scml_mapable_if
{
public:
  scml_mapable_if_to_T(T& m) : mT(m) {}
  const char* getName() const { return mT.getName(); }
  void setPVInterfaceType(scml::PVInterfaceType pvInterfaceType)
  {
    mT.setPVInterfaceType(pvInterfaceType);
  }
  scml::PVInterfaceType getPVInterfaceType() const
  {
    return mT.getPVInterfaceType();
  }
  using scml_mapable_if::transport;
  #define DEFINE_TRANSPORT(IF) \
    IF::response_type transport(const IF::request_type& req) \
    { \
      return mT.transport(req); \
    }
  SCML_FOR_EACH_PV_INTERFACE_TYPE(DEFINE_TRANSPORT)
  #undef DEFINE_TRANSPORT
  void register_port(sc_core::sc_port_base& port, const char* if_typename)
  {
    mT.register_port(port, if_typename);
  }
public:
  virtual sc_object* get_interface_as_sc_object()
  {
    return dynamic_cast<sc_object*>(&mT);
  }
private:
  T& mT;
};

#endif
