// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

#include "testInitiator.h"
#include "HWaccelerator_Target_PV.h"

int sc_main( int, char **) {
  HWaccelerator_Target_PV I_HWaccelerator_Target_PV( "I_HWaccelerator_Target_PV");
  testInitiator aTestInitiator( "aTestInitiator");
  aTestInitiator.p( I_HWaccelerator_Target_PV.p_PV );

  const sc_time runTime( 10, SC_NS );
  sc_start( runTime );
  return 0;
}
