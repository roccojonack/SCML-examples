// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: TLM2 SCML model of a simple byte addressed memory peripheral

#ifndef _MEMORY_TLM2_H
#define _MEMORY_TLM2_H

#include "tlm.h"

// Include memory modeling objects
#include "scml.h"

//------------------------------------------------------------------------------
// Start of module definition:
//
class Memory_TLM2 : 
  public sc_core::sc_module
{
public :

  typedef tlm::tlm_generic_payload      transaction_type;
  typedef tlm::tlm_phase                phase_type;
  typedef tlm::tlm_sync_enum            sync_enum_type;
  typedef tlm::tlm_fw_transport_if<>    fw_interface_type;
  typedef tlm::tlm_bw_transport_if<>    bw_interface_type;
  typedef tlm::tlm_target_socket<32>    target_socket_type;

  target_socket_type socket;
    
  SC_HAS_PROCESS(Memory_TLM2);
  
  Memory_TLM2(sc_module_name name,
		   unsigned int Size);
    
  
  // --- Destructor
  ~Memory_TLM2();

private :
    
  // --- Process functions and methods
  // no processes in this simple peripheral

  // --- Kernel base methods
  void start_of_simulation();
  
  // memory bank
  scml_memory<unsigned int> m_MemoryBank;
  scml_tlm2_target_adaptor< 32 > p_adaptor;

}; // end class Memory_TLM2


#endif /* _MEMORY_TLM2_H */
