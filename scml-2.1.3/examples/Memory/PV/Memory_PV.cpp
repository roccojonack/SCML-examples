// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: PV model of a simple byte addressed memory peripheral

#include "Memory_PV.h"

//------------------------------------------------------------------------------
// Constructor
//
Memory_PV::Memory_PV(sc_module_name name,
                     unsigned int Size,
		     unsigned int AddressingMode )
  : sc_module(name)
  , p_Comms("p_Comms")	
  , m_MemoryBank("m_MemoryBank", scml_memsize(Size >> 2) ) {
  
      cout << this->name() << " : PV Addressing Mode = " << AddressingMode << endl;
      sc_assert( (AddressingMode == 8) || (AddressingMode == 16) || (AddressingMode == 32) );
		
      m_MemoryBank.set_addressing_mode(AddressingMode);
      
      // Bind the PV port directly to memory object
      p_Comms(m_MemoryBank);
				  
	              
} //Memory_PV()

//------------------------------------------------------------------------------
// Destructor
//
Memory_PV::~Memory_PV() {

}

//------------------------------------------------------------------------------
// start_of_simulation()
// This is called automatically by the kernel
//
void Memory_PV::start_of_simulation() {

  cout << this->name() << " : start of simulation" << endl;
  
}

