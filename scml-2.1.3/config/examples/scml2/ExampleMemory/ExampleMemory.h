// Copyright (c) 2009 CoWare, Inc.
// All rights reserved worldwide.

#ifndef EXAMPLE_MEMORY_H
#define EXAMPLE_MEMORY_H

#include <scml2.h>
#include <tlm.h>
#include <systemc>

class ExampleMemory : public sc_core::sc_module
{
private:
  static const unsigned int MEMORY_SIZE = 0x10000;

public:
  tlm::tlm_target_socket<32> socket;

public:
  SC_HAS_PROCESS(ExampleMemory);

  explicit ExampleMemory(sc_core::sc_module_name name) :
    sc_core::sc_module(name),
    socket("socket"),
    mAdapter("mAdapter", socket),
    mMemory("mMemory", MEMORY_SIZE >> 2)
  {
    mAdapter(mMemory);
  }

private:
  scml2::tlm2_gp_target_adapter<32> mAdapter;
  scml2::memory<unsigned int> mMemory;
};

#endif
