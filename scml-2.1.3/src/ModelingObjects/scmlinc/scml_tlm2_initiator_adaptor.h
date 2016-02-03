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
 * Purpose of file : Definition of the scml_tlm2_initiator_adaptor
 *
 */

#ifndef SCML_TLM2_INITIATOR_ADAPTOR_H
#define SCML_TLM2_INITIATOR_ADAPTOR_H

#include "scml2_logging/stream.h"
#include "scmlinc/scml_tlm2_initiator_adaptor_base.h"
#include <PV/PV.h>
#include <tlm.h>
#include <queue>

template <unsigned int BUSWIDTH>
class scml_tlm2_initiator_adaptor :
  public tlm::tlm_bw_transport_if<tlm::tlm_base_protocol_types>,
  public scml_tlm2_initiator_adaptor_base
{
public:
  typedef tlm::tlm_initiator_socket<BUSWIDTH, tlm::tlm_base_protocol_types> socket_type;
  enum Mode { MODE_LT, MODE_AT };

public:
  // FIXME: must be mutable to be able to call get_direct_mem_ptr
  mutable socket_type pOut;

public:
  scml_tlm2_initiator_adaptor(sc_core::sc_module_name name) :
    scml_tlm2_initiator_adaptor_base(name, BUSWIDTH),
    pOut("pOut"),
    mPendingTransaction(0),
    mMode(MODE_LT)
  {
    pOut(*this);
  }
  ~scml_tlm2_initiator_adaptor() {}

public:
  bool set_at_mode()
  {
    if (mMode != MODE_AT &&
        sc_core::sc_get_curr_simcontext()->elaboration_done()) {
      SCML2_LOG(mWarning)
        << "Not possible to switch abstraction level after elaboration" << std::endl;
      return false;

    } else {
      mMode = MODE_AT;
      return true;
    }
  }

  bool set_lt_mode()
  {
    if (mMode != MODE_LT &&
        sc_core::sc_get_curr_simcontext()->elaboration_done()) {
      SCML2_LOG(mWarning)
        << "Not possible to switch abstraction level after elaboration" << std::endl;
      return false;

    } else {
      mMode = MODE_LT;
      return true;
    }
  }

  bool set_mode(Mode mode)
  {
    if (mMode != mode &&
        sc_core::sc_get_curr_simcontext()->elaboration_done()) {
      SCML2_LOG(mWarning)
        << "Not possible to switch abstraction level after elaboration" << std::endl;
      return false;

    } else {
      mMode = mode;
      return true;
    }
  }

  bool is_at_mode() const
  {
    return mMode == MODE_AT;
  }

  bool is_lt_mode() const
  {
    return mMode == MODE_LT;
  }

  Mode get_mode() const
  {
    return mMode;
  }

  void transport(tlm::tlm_generic_payload& trans)
  {
    this->forwardTransaction(trans);
  }

public:
  virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload& trans,
                                             tlm::tlm_phase& phase,
                                             sc_core::sc_time& t)
  {
    switch (phase) {
    case tlm::END_REQ:
      assert(&trans == mPendingTransaction);
      // FIXME: send new transaction here? Or wait for end of transaction?
      return tlm::TLM_ACCEPTED;

    case tlm::BEGIN_RESP:
      assert(&trans == mPendingTransaction);
      mPendingTransaction = 0;
      mEndOfTransaction.notify(t);
      return tlm::TLM_COMPLETED;

    default:
      SCML2_LOG(mError) << "Illegal phase" << std::endl;
      assert(0); exit(1);
    } 
  }

  virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range)
  {
  }

protected:
  virtual void forwardTransaction(tlm::tlm_generic_payload& trans)
  {
    if (is_at_mode()) {
      // serialize transactions: wait for pending transactions
        while (mPendingTransaction) {
          sc_core::sc_event* e = new sc_event();
          mQueue.push(e);
          sc_core::wait(*e);
          delete e;
        }
    }

    sc_core::sc_time t = sc_core::SC_ZERO_TIME;

    if (is_at_mode()) {
      tlm::tlm_phase phase = tlm::BEGIN_REQ;
      assert(!mPendingTransaction);
      if (pOut->nb_transport_fw(trans, phase, t) != tlm::TLM_COMPLETED) {
        if (phase == tlm::BEGIN_RESP) {
          // begin resp returned with timing annotation
          // immediatelly notify end resp (no sync)
          phase = tlm::END_RESP;
          tlm::tlm_sync_enum r = pOut->nb_transport_fw(trans, phase, t);
          assert(r == tlm::TLM_COMPLETED);
        } else {
          mPendingTransaction = &trans;
          sc_core::wait(mEndOfTransaction);
          // Notify next transaction can start
          if (!mQueue.empty()) {
            mQueue.front()->notify(sc_core::SC_ZERO_TIME);
            mQueue.pop();
          }
          return;
        }
      }

    } else {
      assert(is_lt_mode());
      pOut->b_transport(trans, t);
    }

      if (t != sc_core::SC_ZERO_TIME) {
        sc_core::wait(t);
      }
  }

  virtual unsigned int forwardDebugTransaction(tlm::tlm_generic_payload& trans)
  {
    return pOut->transport_dbg(trans);
  }

  virtual bool forwardDMIRequest(tlm::tlm_generic_payload& trans,
                                 tlm::tlm_dmi& dmi_data) const
  {
    return pOut->get_direct_mem_ptr(trans, dmi_data);
  }

private:
  sc_core::sc_event mEndOfTransaction;
  tlm::tlm_generic_payload* mPendingTransaction;
  std::queue<sc_event*> mQueue;
  Mode mMode;
};

#endif

