// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: simple Interrupt Priority Encoder (IPE) testbench

#ifndef SIMPLE_IPE_PV_TESTBENCH_H
#define SIMPLE_IPE_PV_TESTBENCH_H

#include "systemc.h"
#include "PV/PV.h"

class simple_IPE_PV_testbench : public sc_module {
  
  public :
  //ports
  PVInitiator_port< unsigned int, unsigned int > p_PV;
  sc_out<bool> p_irq_out[8];
  sc_in<bool> p_irq_in;
  
  private :    
    void do_it() {
      cerr << name() << " : test active low level triggered" << endl;
      //deactivate all interrupts
      for (unsigned int i = 0 ; i < 8; i++) {
        p_irq_out[i] = 1;
      }
      wait(m_my1ns);
      //m_enable all interrupts
      m_enable = (unsigned int)-1;
      m_enable_req.setType( pvWrite );
      p_PV.transport(m_enable_req);
      //activate all interrupts
      for (unsigned int i = 0 ; i < 8; i++) {
        p_irq_out[i] = 0;
      }
      wait(m_my1ns);
      process_interrupts();
      //disable all interrupts
      m_enable_req.setAddress(0);
      m_enable = 0;
      m_enable_req.setType( pvWrite );
      p_PV.transport(m_enable_req);
      //activate all interrupts
      for (unsigned int i = 0 ; i < 8; i++) {
        p_irq_out[i] = 0;
      }
      wait(m_my1ns);
      for( unsigned int i = 7 ; i != (unsigned int)-1 ; i-- ) {
        m_enable_req.setAddress(0);
        m_enable = (unsigned int)1 << i;
        m_enable_req.setType( pvWrite );
        p_PV.transport(m_enable_req);
        wait(m_my1ns);
        process_interrupts();
      }  
      cerr << name() << " : End of test" << endl;
      sc_stop();
      wait();
    }
      
    void irq_handler() {
      cerr << name() << " : irq_handler() called at time " << sc_time_stamp() 
           << ", p_irq_in is " << p_irq_in << endl;
    }

    unsigned int helper_m_byte_to_nr(void) {
      unsigned int nr(0);
      switch (m_byte) {
        case 1 : 
          nr = 0;
          break;
        case 2 :
          nr = 1;
          break;
        case 4 :
          nr = 2;
          break;
        case 8 :
          nr = 3;
          break;
        case 16 :
          nr = 4;  
          break;
        case 32 :
          nr = 5;
          break;
        case 64 :
          nr = 6;
          break;
        case 128 :
          nr = 7;
          break;
        default :
          cerr << name() << " : Error : no unique bit set : 0x" << hex << (unsigned int)m_byte << endl;
          break;
      }
      return nr;
    }
    
    void process_interrupts(void) {
      unsigned int irq_nr(0);
      m_read_irqvec_req.setAddress(8);
      m_resp = p_PV.transport(m_read_irqvec_req);
      while (m_irq_vector != 0) {
        cerr << name() << " : irq_vector is 0x" << m_irq_vector << endl;
        if ((m_irq_vector & 0xff) != 0) {
          m_byte = m_irq_vector & 0xff;
          irq_nr = helper_m_byte_to_nr();
        } 
        p_irq_out[irq_nr] = 1;
        
        //clear the interrupt in the IPE
        m_clear = (unsigned int)1 << irq_nr;
        m_clear_req.setAddress(4);
        m_clear_req.setDataSize(8);
        m_clear_req.setOffset(0);
        m_clear_req.setType(pvWrite);
        p_PV.transport(m_clear_req);
        wait(m_my1ns);
        // read the irq vector again
        m_read_irqvec_req.setAddress(8);
        m_resp = p_PV.transport(m_read_irqvec_req);
      }                            
    }
  
  public :
  SC_HAS_PROCESS(simple_IPE_PV_testbench);
  //constructor
  simple_IPE_PV_testbench(const sc_module_name &name) :
         sc_module(name),
         p_PV("p_PV"),
         p_irq_in("p_irq_in"),
         m_irq_vector(0),
         m_enable(0),
         m_clear(0),
         m_my1ns(1, SC_NS) {
    SC_THREAD(do_it);
    
    SC_METHOD(irq_handler);
      sensitive << p_irq_in;
      dont_initialize();
      
    m_read_irqvec_req.setReadDataDestination(&m_irq_vector);
    m_read_irqvec_req.setBurstCount(1);
    m_read_irqvec_req.setType( pvRead );
    m_read_irqvec_req.setDataSize(8);
    m_read_irqvec_req.setOffset(0);
    m_read_irqvec_req.setAddress(8);
    
    m_enable_req.setWriteDataSource(&m_enable);
    m_enable_req.setReadDataDestination(&m_enable);
    m_enable_req.setBurstCount(1);
    m_enable_req.setDataSize(8);
    m_enable_req.setOffset(0);
    m_enable_req.setAddress(0);
    
    m_clear_req.setWriteDataSource(&m_clear);
    m_clear_req.setReadDataDestination(&m_clear);
    m_clear_req.setBurstCount(1);
    m_clear_req.setDataSize(8);
    m_clear_req.setAddress(4);
  }
  
  private :
  PVReq<unsigned int, unsigned int> m_read_irqvec_req;
  PVReq<unsigned int, unsigned int> m_enable_req;

  PVReq<unsigned int, unsigned int> m_clear_req;
  PVResp<unsigned int> m_resp;
  unsigned int m_irq_vector;
  unsigned int m_enable;
  unsigned int m_clear;
  sc_time m_my1ns;
  unsigned char m_byte;
};

#endif //SIMPLE_IPE_PV_TESTBENCH_H
