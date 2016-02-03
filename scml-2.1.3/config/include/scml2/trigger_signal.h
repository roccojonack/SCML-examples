/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_TRIGGER_SIGNAL_H
#define SCML2_TRIGGER_SIGNAL_H

#include <ostream>
#include <systemc>

namespace scml {

// Note this forces all ports to be bound whereas the old snps_tlm::trigger_if allowed 
// ports to be unbound. PCT should take care of this by stubbing, I think.

class trigger_in_port : public sc_core::sc_in<unsigned int> {
public:
  explicit trigger_in_port(const char* name_) : sc_core::sc_in<unsigned int>(name_) {}
};

class trigger_inout_port : public sc_core::sc_inout<unsigned int> {
public:
  explicit trigger_inout_port(const char* name_) : sc_core::sc_inout<unsigned int>(name_) {}
  void Trigger() { write(read() + 1); }
};

class trigger_out_port : public sc_core::sc_out<unsigned int> {
public:
  explicit trigger_out_port(const char* name_) : sc_core::sc_out<unsigned int>(name_) {}
  void Trigger() { write(read() + 1); }
};

}

#endif

