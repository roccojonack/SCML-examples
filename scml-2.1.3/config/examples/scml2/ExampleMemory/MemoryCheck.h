// Copyright (c) 2009 CoWare, Inc.
// All rights reserved worldwide.

#ifndef MEMORYCHECK_H
#define MEMORYCHECK_H

#include <scml2.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include <tlm.h>
#include <systemc>

class MemoryCheck : public sc_core::sc_module
{
public:
  scml2::initiator_socket<32> socket;

public:
  SC_HAS_PROCESS(MemoryCheck);

  explicit MemoryCheck(sc_core::sc_module_name name) :
    sc_core::sc_module(name),
    socket("socket")
  {
    tlm_utils::tlm_quantumkeeper::set_global_quantum(sc_core::sc_time(1, sc_core::SC_MS));
    mQuantumKeeper.reset();

    socket.set_quantumkeeper(mQuantumKeeper);

    SC_THREAD(run);
  }

  void run()
  {
    unsigned int address = 0;
    unsigned int data = 0;
    sc_core::sc_time period(100, sc_core::SC_NS);

    std::cout << "TEST STARTED" << std::endl;

    for (; address < 0x4000; address += 4) {
      data = address * 2;
      if (!socket.write<unsigned int>(address, data)) {
        std::cerr << "ERROR: Write failed at address 0x" << std::hex << address << std::endl;
      }
      timeAdvance(period);
    }

    do {
      address -= 4;
      data = 0;
      if (!socket.read<unsigned int>(address, data)) {
        std::cerr << "ERROR: Read failed at address 0x" << std::hex << address << std::endl;
      }
      if (data != (address * 2)) {
        std::cerr << "ERROR: TEST FAILED, got 0x" << std::hex << data
                  << " at address 0x" << std::hex << address << std::endl;
      }
      timeAdvance(period);
    } while (address != 0);

    std::cout << "TEST DONE" << std::endl;
    sc_core::sc_stop();
  }

  void timeAdvance(sc_core::sc_time &period)
  {
    mQuantumKeeper.inc(period);
    if (mQuantumKeeper.need_sync()) {
      mQuantumKeeper.sync();
    }
  }

private:
  tlm_utils::tlm_quantumkeeper mQuantumKeeper;
};

#endif
