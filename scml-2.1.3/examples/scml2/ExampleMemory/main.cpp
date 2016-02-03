// Copyright (c) 2009 CoWare, Inc.
// All rights reserved worldwide.

#include <ExampleMemory.h>
#include <MemoryCheck.h>
#include <systemc>

int sc_main(int argc, char* argv[])
{
  MemoryCheck memoryCheck("memoryCheck");
  ExampleMemory exampleMemory("exampleMemory");

  memoryCheck.socket(exampleMemory.socket);

  sc_core::sc_start();

  return 0;
}
