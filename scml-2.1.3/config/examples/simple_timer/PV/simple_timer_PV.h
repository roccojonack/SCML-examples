// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose : simple timer to show usage of scml Clock Objects

#ifndef SIMPLE_TIMER_PV_H
#define SIMPLE_TIMER_PV_H

#include <iostream>

#include "systemc.h"
#include "scml.h"
#include "PV/PV.h"

class simple_timer_PV :  public sc_module {
 public:
 
  // port list
  PVTarget_port< unsigned int, unsigned int > p_PV;
  sc_in<bool> clk_in;
  
  SC_HAS_PROCESS(simple_timer_PV);
  //constructor  
  explicit simple_timer_PV(const sc_module_name &name);
  // destructor
  ~simple_timer_PV() {
  }
  
private :
  // Disable default and copy constructors
  simple_timer_PV();
  simple_timer_PV(const simple_timer_PV&);          
  simple_timer_PV& operator= (const simple_timer_PV&);

  //methods
  unsigned int f_read_curr_value(unsigned int accsize,
                                 unsigned int offset);
                                 
  void f_write_end_value(unsigned int new_value, unsigned int accsize,
                         unsigned int offset);
                         
  void f_timer_tick(void);
  
  //private data
  
  // real register bank
  scml_memory <unsigned int> m_regs;
  //aliases registers  
  scml_memory <unsigned int> CURRENT_VALUE_REG;
  scml_memory <unsigned int> END_VALUE_REG;
  // clock objects
  scml_divided_clock clock_mirror;
  scml_divided_clock timer_out_clock;
  scml_clock_counter counter;
};

inline simple_timer_PV::simple_timer_PV(const sc_module_name &name) :
  sc_module(name),
  p_PV("p_PV"),
  clk_in("clk_in"),
  m_regs("m_regs", scml_memsize(2)),
  CURRENT_VALUE_REG("CURRENT_VALUE_REG", m_regs, 0, 1),
  END_VALUE_REG("END_VALUE_REG", m_regs, 1, 1),
  clock_mirror("clock_mirror", clk_in, 1, 0),
  timer_out_clock("timer_out_clock", clock_mirror),
  counter("counter", clock_mirror) {
  //bind the PV port with the register bank
  p_PV(m_regs);
  m_regs.set_addressing_mode(8);
  //reset the register bank
  m_regs.initialize(0);
    
  MEMORY_REGISTER_NB_READ( CURRENT_VALUE_REG, f_read_curr_value);
  MEMORY_REGISTER_NB_WRITE( END_VALUE_REG, f_write_end_value);
    
  SC_METHOD(f_timer_tick);
  sensitive << timer_out_clock.posedge_event();
  dont_initialize();
}

inline unsigned int simple_timer_PV::f_read_curr_value(unsigned int accsize,
                                                       unsigned int offset) {
  assert(accsize == 32);
  assert(offset  == 0);
  return (unsigned int) counter.get_count(); 
}

inline void simple_timer_PV::f_write_end_value(unsigned int new_value,
                                               unsigned int accsize,
                                               unsigned int offset) {
  assert(accsize == 32);
  assert(offset  == 0);
  END_VALUE_REG = new_value;
  timer_out_clock.set_divider(new_value);
  counter.set_count(0);
}

inline void simple_timer_PV::f_timer_tick(void) {
  cerr << name() << " timer reached " << (unsigned int)counter.get_count() 
       << " @time " << sc_time_stamp() << endl;
  counter.set_count(0);
}

#endif // SIMPLE_TIMER_PV_H
