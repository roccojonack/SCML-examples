// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

#include <time.h>

#include "systemc.h"

#include "top_PV.h"
	
int sc_main(int argc, char* argv[])
{
  static float fSimulationCPUTime = 0;
  static float fSysCTimeStart = 0;
  static float fSysCTimeStop = 0;  
        double SimTime = 1500.0;
	
	if (argc > 1) {
	  SimTime = (double)(atoi(sc_argv()[1]));
	  cout << "Setting SimTime: " << sc_argv()[1] << "  ns" << endl;
	}
		
	top I_top("I_top");

  	// get SC start time
  	fSysCTimeStart = (float)sc_time_stamp().to_seconds();
  	clock();    

	cout << "Starting simulation: " << SimTime << " ns" << endl;
        sc_start(SimTime, SC_NS);

  	// Get the simulation duration
  	fSysCTimeStop = (float)sc_time_stamp().to_seconds();
  	fSimulationCPUTime = (float)( (float)clock() / (float)CLOCKS_PER_SEC );
    
  	cerr << endl << "simulation complete: Timimg results:" << endl;
  	cerr << "SystemC simulated duration: " << (fSysCTimeStop - fSysCTimeStart) << endl;
  	cerr << "                  CPU time: " << fSimulationCPUTime << endl << endl ;
	
	return 0;
};


