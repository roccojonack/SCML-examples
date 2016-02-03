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
 * Purpose of file : Definition of the scml_tlm2_target_adaptor_base
 *
 */

#ifndef SCML_TLM2_TARGET_ADAPTOR_BASE_H
#define SCML_TLM2_TARGET_ADAPTOR_BASE_H

#include "scmlinc/scml_mapable_if.h"
#include <tlm.h>

class scml_tlm2_target_adaptor_base : public sc_core::sc_module
{
public:
  sc_core::sc_port<scml_mapable_if> pOut;

public:
  SC_HAS_PROCESS(scml_tlm2_target_adaptor_base);
  scml_tlm2_target_adaptor_base(sc_core::sc_module_name name, unsigned int busWidth);
  ~scml_tlm2_target_adaptor_base();

  void set_endianness(scml_endian e);
  scml_endian get_endianness() const;

protected:
  void forwardTransaction(tlm::tlm_generic_payload& trans, bool isDebug);
  template <typename IF>
  void forwardTransactionImp(tlm::tlm_generic_payload& trans, bool isDebug);
  template <typename IF>
  void unrollTransaction(tlm::tlm_generic_payload& trans, bool isDebug);

  bool forwardDMIRequest(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data);

private:
  const unsigned int mBusWidth;
  bool mHasHostEndianness;
};

#endif
