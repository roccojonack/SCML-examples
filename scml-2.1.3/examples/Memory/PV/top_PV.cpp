// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: Top level wrapper module source file for timer PV system

#include "systemc.h"

#include "top_PV.h"

//------------------------------------------------------------------------------
// Constructor
//
top::top(sc_module_name nm) : sc_module(nm)  {
			
  // Instantiate the PV modules		
  pI_Memory_PV = new Memory_PV("I_Memory_PV",
                                0x10000, // size in bytes
			        8);
				
  pI_TrafficGen_PV = new TrafficGen_PV("I_TrafficGen_PV",
			                40, // num tests
			                4   // burst size
				        );
		
  // Bind the ports
  pI_TrafficGen_PV->p_Comms(pI_Memory_PV->p_Comms);
}


//------------------------------------------------------------------------------
// Destructor
//
top::~top() {
  delete pI_Memory_PV;
  delete pI_TrafficGen_PV;
}

