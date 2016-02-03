// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

#include "simple_IPE_PV.h"
#include "simple_IPE_PV_testbench.h"

int sc_main(int argc, char**argv) {

  simple_IPE_PV I_simple_IPE_PV("I_simple_IPE_PV");
  simple_IPE_PV_testbench I_simple_IPE_PV_testbench("I_simple_IPE_PV_testbench");
 
  sc_signal<bool> s_irq_o("s_irq_o");
  sc_signal<bool> s_irq [8];

  for (unsigned int i = 0 ; i < 8 ; i++) {
    I_simple_IPE_PV.p_irq_in[i](s_irq[i]);
    I_simple_IPE_PV_testbench.p_irq_out[i](s_irq[i]); 
  }
 
  I_simple_IPE_PV.p_irq_out(s_irq_o);
  I_simple_IPE_PV_testbench.p_irq_in(s_irq_o);
 
  I_simple_IPE_PV_testbench.p_PV(I_simple_IPE_PV.p_PV);
 
  sc_start();

  return 0;
}
