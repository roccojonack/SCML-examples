// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: Top level wrapper module header file for timer PV system

#ifndef _TOP_PV_H
#define _TOP_PV_H

#include "systemc.h"

#include "Memory_PV.h"
#include "TrafficGen_PV.h"

//------------------------------------------------------------------------------
// class top
// top level module definition for Memory and Traffic Gen PV system
//
class top : public sc_module {
public:
  
  // Constructor		
  top(sc_module_name nm);
	
  // Destructor	
  ~top();

private:
  // Instantiate aggregate members
  Memory_PV * pI_Memory_PV;
  TrafficGen_PV * pI_TrafficGen_PV;

};


#endif /* _TOP_PV_H */
