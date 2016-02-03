// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: HW accelerator PV module 

#ifndef HWACCELERATOR_TARGET_PV
#define HWACCELERATOR_TARGET_PV

#include "systemc.h"
#include "PV/PV.h"
#include "scml.h"

class HWaccelerator_Target_PV : public sc_module {
 public:
  // port list
  PVTarget_port< unsigned int, unsigned int > p_PV;

   // modeling objects typedefs
  typedef scml_memory<signed int>::value_type value_type;

  // constructor
  HWaccelerator_Target_PV( const sc_module_name & n ) ;
  SC_HAS_PROCESS( HWaccelerator_Target_PV ); 

  // default destructor OK
  // ~HWaccelerator_Target_PV();

 private:
  // methods
  void acceleratorFunction(value_type d, 
    unsigned int as,
    unsigned int offset);
 private:
  // should disable these
  HWaccelerator_Target_PV( const HWaccelerator_Target_PV & );          
  HWaccelerator_Target_PV & operator= ( const HWaccelerator_Target_PV & );

 private:
  // real register bank
  scml_memory <signed int> regs; 

  // aliases input registers
  scml_memory <signed int> ir0;
  scml_memory <signed int> ir1;
  scml_memory <signed int> ir2;
  scml_memory <signed int> ir3;
  scml_memory <signed int> ir4;
  scml_memory <signed int> ir5;
  scml_memory <signed int> ir6;
  scml_memory <signed int> ir7;
    
  // aliases output registers
  scml_memory <signed int> r0;
  scml_memory <signed int> r1;
  scml_memory <signed int> r2;
  scml_memory <signed int> r3;
  scml_memory <signed int> r4;
  scml_memory <signed int> r5;
  scml_memory <signed int> r6;
  scml_memory <signed int> r7;    
};

#endif // HWACCELERATOR_TARGET_PV
