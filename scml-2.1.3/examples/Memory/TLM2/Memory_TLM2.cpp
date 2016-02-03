// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: TLM2 SCML model of a simple byte addressed memory peripheral

#include "Memory_TLM2.h"

//------------------------------------------------------------------------------
// Constructor
//
Memory_TLM2::Memory_TLM2(sc_module_name name,
				   unsigned int Size )
  : sc_module(name)
  , socket("socket")
  , m_MemoryBank("m_MemoryBank", scml_memsize(Size >> 2) ) 
  , p_adaptor("p_adaptor")
{
  
  // Bind the TLM2 target socket to the memory object
  socket(p_adaptor.pIn);
  p_adaptor.pOut(m_MemoryBank);

} //Memory_TLM2()

//------------------------------------------------------------------------------
// Destructor
//
Memory_TLM2::~Memory_TLM2() {

}

//------------------------------------------------------------------------------
// start_of_simulation()
// This is called automatically by the kernel
//
void Memory_TLM2::start_of_simulation() {

  cout << this->name() << " : start of simulation" << endl;
  
}

