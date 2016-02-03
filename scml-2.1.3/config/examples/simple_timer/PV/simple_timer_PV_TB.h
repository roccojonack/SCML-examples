// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: simple PV timer testbench

#ifndef SIMPLE_TIMER_PV_TB_H
#define SIMPLE_TIMER_PV_TB_H

#include "systemc.h"

// Add in the PV definitions
#include "PV/PV.h"


//------------------------------------------------------------------------------
// Start of module definition:
//
class simple_timer_PV_TB : public sc_module {
public :
  
  // Module ports
  PVInitiator_port< unsigned int, unsigned int > p_PV;
      
  SC_HAS_PROCESS(simple_timer_PV_TB);

  // Constructor
  explicit simple_timer_PV_TB(sc_module_name name) : 
                               sc_module(name) {
    SC_THREAD(do_it);

    m_req.setWriteDataSource(&m_value);
    m_req.setReadDataDestination(&m_value);
    m_req.setBurstCount(1);
    m_req.setOffset(0);
    m_req.setDataSize(32);
  }

private :
  // --- Private methods and process functions
  	       
  void do_it(void);
  
  // --- Private module variables ----
  PVReq< unsigned int, unsigned int > m_req;
  PVResp< unsigned int > m_resp;
  unsigned int m_value;
  
}; // end class definition

inline void simple_timer_PV_TB :: do_it(void) {
  while(1) {
    // setup end value,
    m_value = 50;
    m_req.setType( pvWrite );
    m_req.setAddress(4);
    m_resp = p_PV.transport(m_req);
    assert(m_resp.getResponse() == pvOk);

    // now readout the timer value from time to time
    for (unsigned int i = 0; i < 10; i++) {
      wait(40, SC_NS);
      m_req.setType( pvRead );
      m_req.setAddress(0);
      m_resp = p_PV.transport(m_req);
      assert(m_resp.getResponse() == pvOk);
      cerr << name() << " timer value is " << m_value << " @time " 
                     << sc_time_stamp() << endl;
    }
        
    // now write a new end value
    m_value = 100;
    m_req.setType( pvWrite );
    m_req.setAddress(4);
    m_resp = p_PV.transport(m_req);
    assert(m_resp.getResponse() == pvOk);
    
    // so we keep it running for a while
    
    wait(1000, SC_NS);
    
    // and then we quit the test
    
    sc_stop();
  }
}

#endif /* SIMPLE_TIMER_PV_TB_H */
