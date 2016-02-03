// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: simple Interrupt Priority Encoder (IPE)

#ifndef SIMPLE_IPE_PV_H
#define SIMPLE_IPE_PV_H

#include "systemc.h"
#include "scml.h"
#include "PV/PV.h"


class simple_IPE_PV : public sc_module {
public :
  //ports
  PVTarget_port< unsigned int, unsigned int > p_PV;
  sc_in<bool> p_irq_in[8];
  sc_out<bool> p_irq_out;
  
private :
  sc_event m_assign_irq_event;

  // Disable default and copy constructors
  simple_IPE_PV();
  simple_IPE_PV(const simple_IPE_PV&);          
  simple_IPE_PV& operator= (const simple_IPE_PV&);

  void f_clear_write(unsigned int new_value,
                     unsigned int accsize,
                     unsigned int offset);
  void f_enable_write(unsigned int new_value,
                      unsigned int accsize,
                      unsigned int offset);
  void f_arbitrate(bool called_from_PV = false);
  void f_irq_n(unsigned int n, bool call_arbitrate = true, 
	       bool called_from_PV = false);
  void f_irq(void);
  void f_assign_irq(void);
  
public :
  SC_HAS_PROCESS(simple_IPE_PV);
  
  explicit simple_IPE_PV(const sc_module_name &name);
  ~simple_IPE_PV();
  
  private :
    sc_uint<8> m_raw_irq;

    // real register bank
    scml_memory <unsigned int> m_regs;
    // register aliases
    scml_memory <unsigned int> ENABLE_REG;
    scml_memory <unsigned int> CLEAR_REG;
    scml_memory <unsigned int> IRQ_VEC_REG;
    scml_bitfield *m_ENABLE_BIT[8];
    
}; //class simple_IPE_PV


// inline implementations of simple_IPE_PV class
// -------------------------------------------

//constructor
inline simple_IPE_PV
::simple_IPE_PV(const sc_module_name &name) :
       sc_module(name),
       p_PV("p_PV"),
       p_irq_out("p_irq_out"),
       m_raw_irq(0),
       m_regs("m_regs",  scml_memsize(3)),
       ENABLE_REG("ENABLE_REG", m_regs, 0, 1),
       CLEAR_REG("CLEAR_REG", m_regs, 1, 1),
       IRQ_VEC_REG("IRQ_VEC_REG", m_regs, 2, 1) {

  m_regs.set_addressing_mode(8);
  // initialize m_regs to 0
  m_regs.initialize(0);
  IRQ_VEC_REG.set_read_only();

  //bind the PV port to the register bank
  p_PV(m_regs);

  SC_METHOD(f_irq);
    for (unsigned int i = 0; i < 8; i++) {
      sensitive << p_irq_in[i];
    }
    dont_initialize();

  SC_METHOD(f_assign_irq);
    sensitive << m_assign_irq_event;
    dont_initialize();

  // callback functions            
  MEMORY_REGISTER_WRITE(ENABLE_REG, f_enable_write);
  MEMORY_REGISTER_WRITE(CLEAR_REG, f_clear_write);

  // array of bitfields for enable
  for (unsigned int i = 0; i < 8; i++) {
    m_ENABLE_BIT[i] = 
      new scml_bitfield(sc_gen_unique_name("m_ENABLE_BIT"),
                      ENABLE_REG, i, 1);
  }    
} //end constructor

//destructor  
inline simple_IPE_PV
::~simple_IPE_PV() {
  for (unsigned int i = 0; i < 8; i++) {
    delete m_ENABLE_BIT[i];
  }
} //end destructor

inline void simple_IPE_PV
::f_enable_write(unsigned int new_value, 
		 unsigned int accsize,
		 unsigned int offset) {
  ENABLE_REG.put_bits(new_value, 0, offset, accsize);
  // update the raw interrupts
  for (unsigned int i = 0 ; i < 7 ; i++) {
    f_irq_n(i, false, true);
  }
  f_irq_n(7, true, true);  
}

inline void simple_IPE_PV
::f_arbitrate(bool called_from_PV) {
  IRQ_VEC_REG = 0;
  for (unsigned int i = 0 ; i < 8 ; i++) {
    if (m_raw_irq[i]) {
      IRQ_VEC_REG = 1 << i;
      break;
    }
  }
  if (p_irq_out != (IRQ_VEC_REG == 0)) {
    m_assign_irq_event.notify();
    if (called_from_PV) {
      wait(SC_ZERO_TIME);
    }
  }
}

inline void simple_IPE_PV
::f_clear_write(unsigned int new_value,
                unsigned int accsize,
                unsigned int offset) {
  CLEAR_REG.put_bits(new_value, 0, offset, accsize);
  for (unsigned int i = 0 ; i < 8 ; i++) {
    if ( (new_value & ( 1 << i )) != 0 ) {
      m_raw_irq[i] = 0;
    }
  }
  f_arbitrate(true);
}

inline void simple_IPE_PV
::f_irq_n(unsigned int n, 
	bool call_arbitrate, 
	bool called_from_PV) {
        
  if (*(m_ENABLE_BIT[n])) {
     m_raw_irq[n] = !p_irq_in[n];
  }
  if (call_arbitrate) {
    f_arbitrate(called_from_PV);
  }
}

inline void simple_IPE_PV
::f_irq(void) {
  bool highest(true);
  for (unsigned int i = 0 ; i < 8 ; i++) {
    if (p_irq_in[i]->event()) {
      f_irq_n(i, highest, false);
      highest = false;
    }
  }
}

inline void simple_IPE_PV
::f_assign_irq(void) {
  p_irq_out = (IRQ_VEC_REG == 0);
}



#endif //SIMPLE_IPE_PV_H
