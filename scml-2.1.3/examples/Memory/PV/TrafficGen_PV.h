// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: PV model of a simple traffic generator
 
#ifndef _PV_TRAFFIC_GENERATOR_H
#define _PV_TRAFFIC_GENERATOR_H

#include "systemc.h"

// Add in the PV definitions
#include "PV/PV.h"


//------------------------------------------------------------------------------
// Start of module definition:
//
class TrafficGen_PV : public sc_module {
public :
  
  // Define an enumerated type to run thru possible
  // transaction types
  typedef enum {
    e32   =0,
    e16_0 =1, // lower half-word access
    e16_1 =2, // upper half-word access
    e8_0  =3, // byte-0 access
    e8_1  =4, // byte-1 access
    e8_2  =5, // byte-2 access
    e8_3  =6  // byte-3 access
  } eAccessType_t;
  
  // Instantiate main PV comms port
  PVInitiator_port< unsigned int, unsigned int > p_Comms;
      
  SC_HAS_PROCESS(TrafficGen_PV);

  // Constructor
  TrafficGen_PV(sc_module_name name,
                unsigned int NumTransactions = 100,
                unsigned int BurstSize = 16);
  
  // Destructor
  ~TrafficGen_PV();

private :
  // --- Private methods and process functions
  void main_TrafficGen_PV_process();      
  unsigned int getDataSize(eAccessType_t Curr);
  unsigned int getDataSizeInBytes(eAccessType_t Size);
  unsigned int getOffset(eAccessType_t Curr);
  eAccessType_t getNextAccessType(eAccessType_t Curr);
  unsigned int getMask(TrafficGen_PV::eAccessType_t AccessType);
  void setPVAddressOffset(PVReq< unsigned int, unsigned int >& Req);
  void burstAccess();
  void unrollBurstAccess();
  
  // Kernel methods
  void start_of_simulation();

  // --- Private module variables ----
  PVReq< unsigned int, unsigned int > BehavReq;
  PVResp< unsigned int > BehavResp;
  
  unsigned int m_NumWaitStates;
  unsigned int m_TransCount;
  int *m_WriteDataVal;
  int *m_ReadDataVal;
  unsigned int m_AddrVal;
  int m_DataVal;
  unsigned int m_DataSize;
  unsigned int m_NumTransactions;
  unsigned int m_BurstSize;
  unsigned int m_AddrOffset;
  eAccessType_t m_AccessType;
  
}; //SC_MODULE(TrafficGen_PV)


#endif /* _PV_TRAFFIC_GENERATOR_H */
