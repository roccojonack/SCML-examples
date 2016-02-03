// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: test initiator PV module 

#ifndef TESTINITIATOR_H
#define TESTINITIATOR_H

#include <systemc.h>
#include "PV/PV.h"

/************************************************************************
 * testInitiator
 */

class testInitiator : public sc_module {
public:  
  // port
  PVInitiator_port< unsigned int , unsigned int > p;
  
  // constructor
  SC_HAS_PROCESS( testInitiator);
  testInitiator( const sc_module_name & n);
  // default destructor OK
  // ~testInitiator();

  typedef PVResp< unsigned int > localPVResp;
  typedef PVReq < unsigned int , unsigned int > localPVReq;

private:  
  // thread body
  void initiatorThread();
  const sc_time timeSlice ;

private:
  // should disable these:
  // testInitiator( const testInitiator & );
  // testInitiator & operator= ( const testInitiator & );
};

#endif
