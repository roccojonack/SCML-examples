// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

#include <time.h>
 
#include "systemc.h"
#include "cache.h"
#include "initiator.h"
#include "target.h"
#include "scmlinc/scml_post_PV_transactor.h"

int sc_main(int argc, char* argv[])
{
  static float fSimulationCPUTime = 0;
  static float fSysCTimeStart = 0;
  static float fSysCTimeStop = 0;
        double SimTime = -1.0;
         
        if (argc > 1) {
          SimTime = (double)(atoi(argv[1]));
          cout << "Setting SimTime: " << argv[1] << "  ns" << endl;
        }

        scml_post_PV_transactor<unsigned int, unsigned int> scmlPost2PVXactor_init_cache("scmlPost2PVXactor_init_cache");
        scml_post_PV_transactor<unsigned int, unsigned int> scmlPost2PVXactor_init_cacheRegs("scmlPost2PVXactor_init_cacheRegs");
        scml_post_PV_transactor<unsigned int, unsigned int> scmlPost2PVXactor_cache("scmlPost2PVXactor_cache");
        cache<unsigned int, unsigned int, unsigned int> i_cache("i_cache");
        sc_signal<bool> stub_i_cache_p_reset("stub_cache_p_reset");
        initiator i_initiator("i_initiator");
        target<unsigned int, unsigned int, 0x800> i_target("i_target", 30);

        i_initiator.p_cache(scmlPost2PVXactor_init_cache);
        i_initiator.p_cache_regs(scmlPost2PVXactor_init_cacheRegs);
        scmlPost2PVXactor_init_cache.port(i_cache.p_pv);
        scmlPost2PVXactor_init_cacheRegs.port(i_cache.p_pv_regs);
        i_cache.p_post(scmlPost2PVXactor_cache);
        scmlPost2PVXactor_cache.port(i_target.p_pv);
        i_cache.p_reset(stub_i_cache_p_reset);
 
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
}

