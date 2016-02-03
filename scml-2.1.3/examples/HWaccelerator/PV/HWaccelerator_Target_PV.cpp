// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: HW accelerator PV module

#include "HWaccelerator_Target_PV.h"
#include "JPEG_globals.h"

HWaccelerator_Target_PV::HWaccelerator_Target_PV( const sc_module_name & n ) : 
  sc_module( n ),
  p_PV("p_PV"),
  regs("regs", scml_memsize(16)),
  ir0("ir0", regs, 0, 1),
  ir1("ir1", regs, 1, 1),
  ir2("ir2", regs, 2, 1),
  ir3("ir3", regs, 3, 1),
  ir4("ir4", regs, 4, 1),
  ir5("ir5", regs, 5, 1),
  ir6("ir6", regs, 6, 1),
  ir7("ir7", regs, 7, 1),
  r0("r0", regs, 8, 1),
  r1("r1", regs, 9, 1),
  r2("r2", regs, 10, 1),
  r3("r3", regs, 11, 1),
  r4("r4", regs, 12, 1),
  r5("r5", regs, 13, 1),
  r6("r6", regs, 14, 1),
  r7("r7", regs, 15, 1) {
  cout << name() << endl; 
  // set the addresingmode of the register
  regs.set_addressing_mode(8);
  // on a write to ir7, the acceleration function must be called
  MEMORY_REGISTER_NB_WRITE( ir7, acceleratorFunction);
  // initialize regs to 0
  for (int i = 0 ; i < 16 ; i++) {
    regs[i] = 0;
  }
  //bind the PV port to the register bank
  p_PV(regs);
};

void HWaccelerator_Target_PV::acceleratorFunction(
    value_type d, 
    unsigned int as,
    unsigned int offset) {

  ir7 =  d;
  cout << name() << " : acceleratorFunction is being called." << endl;
  signed int temp; 
  r0 = ir0 ;
  r1 = ir1 ;
  r2 = ir2 ;
  r3 = ir3 ;
  r4 = ir4 ;
  r5 = ir5 ;
  r6 = ir6 ;
  r7 = ir7 ;


  /* 1st stage:  2 butterflies                                 */
  /* r5=r5 */        /* F(0)                                 */
  /* r4=r4 */        /* F(4)                                 */
  /* r6=r6 */        /* F(2)                                 */
  /* r7=r7 */        /* F(6)                                 */
     
  temp=r3;           /* save a copy of F(5)                  */
  r3-=r0;            /* F(5)-F(3)                            */
  r0+=temp;          /* F(5)+F(3)                            */
  
  temp=r1;           /* save a copy of F(1)                  */
  r1-=r2;            /* F(1)-F(7)                            */
  r2+=temp;          /* F(1)+F(7)                            */
     
  /* 2st stage:  2 butterflies                                 */
  /* r5=r5 */        /* F(0)                                 */
  /* r4=r4 */        /* F(4)                                 */
  
  temp=r6;           /* save a copy of F(2)                  */
  r6-=r7;            /* F(2)-F(6)                            */
  r7+=temp;          /* F(2)+F(6)                            */
  
  /* r3=r3 */        /* F(5)-F(3)                            */
  /* r1=r1 */        /* F(1)-F(7)                            */
     
  temp=r2;           /* save a copy of F(1)+F(7)             */
  r2-=r0;            /* F(1)+F(7) - (F(5)+F(3))              */
  r0+=temp;          /* F(1)+F(7) + F(5)+F(3)                */
  
  /* 3st stage:  1 sum, 5 multiplies, 2 sums                   */
  
  /* r5=r5 */
  /* r4=r4 */
  
  MULT_BY_A1(r6);     /* A1*(F(2)-F(6))                       */
    /* r7=r7 */
    
  temp=r3;           /* prepare for A5 multiply              */
  temp+=r1;          /* NOTE: both signs flipped             */
  
  MULT_BY_A2(r3);     /* A2*(F(5)-F(3))                       */
  MULT_BY_A3(r2);     /* A3*(F(1)+F(7)-F(5)-F(3))             */
  MULT_BY_A4(r1);    /* A4*(F(1)-F(7))                       */
    /* r0=r0 */
  MULT_BY_A5(temp);   /* A5*(F(5)-F(3))+(F(1)-F(7)))          */
    
    r1-=temp;
  r3+=temp;
  
  /* 4th stage:  1 butterfly, 1 sum                            */
  
  temp=r5;           /* save a copy of F(0)                  */
  r5-=r4;            /* F(0)-F(4)                            */
  r4+=temp;          /* F(0)+F(4)                            */
  /* r6=r6 */        /* A1*(F(2)-F(6))                       */
  r7+=r6;            /* F(2)+F(6) + A1*(F(2)-F(6))           */
  
  /* r3=r3 */
  /* r2=r2 */        /* A3*(F(1)+F(7)-F(5)-F(3))             */
  /* r1=r1 */
  /* r0=r0 */        /* keep product precision constant      */
  
  /* 5th stage:  2 butterflies, 3 sums                         */
  
  temp=r4;           /* save a copy of r4                    */
  r4-=r7;            /* decrement by r7                      */
  r7+=temp;          /* r7+r4                                */
  
  temp=r5;           /* save a copy of r5                    */
  r5-=r6;            /* decrement by r6                      */
  r6+=temp;          /* r6+r5                                */
  
  r0+=r1;
  r1+=r2;
  r2+=r3;
  /* r3=r3 */
  
  /* 6th stage:  4 butterflies                                 */
  
  temp=r7;
  r7-=r0;
  r0+=temp;
  
  temp=r6;
  r6-=r1;
  r1+=temp;
  
  temp=r5;
  r5-=r2;
  r2+=temp;
  
  temp=r4;
  r4-=r3;
  r3+=temp;
  
}
