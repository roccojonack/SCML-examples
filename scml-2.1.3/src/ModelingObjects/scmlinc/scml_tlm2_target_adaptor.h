/*****************************************************************************
 *                   Copyright (C) 2008-2012 Synopsys, Inc.                  *
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
 * Purpose of file : Definition of the scml_tlm2_target_adaptor
 *
 */

#ifndef SCML_TLM2_TARGET_ADAPTOR_H
#define SCML_TLM2_TARGET_ADAPTOR_H

#include "scmlinc/scml_tlm2_target_adaptor_base.h"
#include <PV/PV.h>
#include <tlm.h>
#include <tlm_utils/peq_with_get.h>
#include <scml2_logging/stream.h>
#include <scml2_logging/severity.h>

template <unsigned int BUSWIDTH>
class scml_tlm2_target_adaptor :
  public tlm::tlm_fw_transport_if<tlm::tlm_base_protocol_types>,
  public scml_tlm2_target_adaptor_base
{
public:
  typedef tlm::tlm_target_socket<BUSWIDTH, tlm::tlm_base_protocol_types> socket_type;

public:
  socket_type pIn;

public:
  SC_HAS_PROCESS(scml_tlm2_target_adaptor);
  scml_tlm2_target_adaptor(sc_core::sc_module_name n) :
    scml_tlm2_target_adaptor_base(n, BUSWIDTH),
    pIn("pIn"),
    mError(name(), scml2::logging::severity::error()),
    mPEQ("PEQ")
  {
    pIn(*this);

    SC_THREAD(main);
  }

  ~scml_tlm2_target_adaptor() {}

  void end_of_elaboration()
  {
    // FIXME: check word size of destination == BUSWIDTH?
    // FIXME: check data size of PV Interface type == BUSWIDTH?
  }

public:
  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, 
                                             tlm::tlm_phase& phase,
                                             sc_core::sc_time& t)
  {
    switch (phase) {
    case tlm::BEGIN_REQ:
      mPEQ.notify(trans, t);
      return tlm::TLM_ACCEPTED; // Or TLM_UPDATED??

    case tlm::END_RESP:
      mEndResponseEvent.notify(t);
      // FIXME: check transaction pointer?
      return tlm::TLM_COMPLETED;

    default:
      SCML2_LOG(mError) << "Illegal phase" << std::endl;
      return tlm::TLM_ACCEPTED;
    }
  }

  virtual void b_transport(tlm::tlm_generic_payload& trans, 
                           sc_core::sc_time& t)
  {
    if (t != sc_core::SC_ZERO_TIME) {
      sc_core::wait(t);
      t = sc_core::SC_ZERO_TIME;
    }
    this->forwardTransaction(trans, false);
  }

  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                  tlm::tlm_dmi&  dmi_data)
  {
    if (this->forwardDMIRequest(trans, dmi_data)) {
      return true;
    }
    return false;
  }

  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
  {
    this->forwardTransaction(trans, true);
    if (trans.get_response_status() == tlm::TLM_OK_RESPONSE) {
      // FIXME: what's the impact of byte enables on length?
      return trans.get_data_length();

    } else {
      return 0;
    }
  }

private:
  virtual void sendResponse(tlm::tlm_generic_payload& trans)
  {
    tlm::tlm_phase phase = tlm::BEGIN_RESP;
    sc_core::sc_time t = sc_core::SC_ZERO_TIME;
    tlm::tlm_sync_enum result = pIn->nb_transport_bw(trans, phase, t);

    if ((result == tlm::TLM_COMPLETED) ||
        ((result == tlm::TLM_UPDATED) && (phase == tlm::END_RESP))) {
      return;

    } else {
      sc_core::wait(mEndResponseEvent);
    }
  }

  void main()
  {
    while (true) {
      wait(mPEQ.get_event());

      tlm::tlm_generic_payload* trans;
      while ((trans = mPEQ.get_next_transaction()) != 0) {
        this->forwardTransaction(*trans, false);
        sendResponse(*trans);
      }
    }
  }

private:

private:
  mutable scml2::logging::stream mError;
  sc_core::sc_event mEndResponseEvent;

  tlm_utils::peq_with_get<tlm::tlm_generic_payload> mPEQ;
};

#endif
