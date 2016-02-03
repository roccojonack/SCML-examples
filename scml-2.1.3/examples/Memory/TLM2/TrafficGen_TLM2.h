// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: TLM2 model of a simple traffic generator

#ifndef _TRAFFICGEN_TLM2_H
#define _TRAFFICGEN_TLM2_H

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"

#include "scml.h"

class TrafficGen_TLM2 : public sc_core::sc_module
{
public:
  typedef tlm::tlm_generic_payload                            transaction_type;
  typedef tlm_utils::simple_initiator_socket<TrafficGen_TLM2> initiator_socket_type;

public:
  initiator_socket_type socket;

public:
  SC_HAS_PROCESS(TrafficGen_TLM2);
  TrafficGen_TLM2(sc_core::sc_module_name name) :
    sc_core::sc_module(name),
    socket("socket"),
    mMemSizeProp("memory_size",400),
    mNbrTransProp("number_of_transactions",20),
    mBaseAddressProp("base_address",0),
    mTransactionCount(0)
  {
    mNrOfTransactions = mNbrTransProp; 
    mBaseAddress = mBaseAddressProp;

    // Initiator thread
    SC_THREAD(run);
  }
  ~TrafficGen_TLM2() {
  }
    

  bool initTransaction(transaction_type& trans)
  {
    if (mTransactionCount < mNrOfTransactions) {
      trans.set_address(mBaseAddress + (4*mTransactionCount % mMemSizeProp));
      mData = mTransactionCount;
      trans.set_command(tlm::TLM_WRITE_COMMAND);

    } else if (mTransactionCount < 2 * mNrOfTransactions) {
      trans.set_address(mBaseAddress + (4*(mTransactionCount - mNrOfTransactions) % mMemSizeProp));
      mData = 0;
      trans.set_command(tlm::TLM_READ_COMMAND);
    } else {
      return false;
    }

    trans.set_data_ptr(reinterpret_cast<unsigned char*>(&mData));
    trans.set_data_length(4);
    trans.set_streaming_width(4);

    ++mTransactionCount;
    return true;
  }

  void logStartTransation(transaction_type& trans)
  {
    if (trans.get_command() == tlm::TLM_WRITE_COMMAND) {
      std::cout << name() << ": Send write request: A = 0x"
                << std::hex << (unsigned int)trans.get_address()
                << ", D = 0x" << mData << std::dec
                << " @ " << sc_core::sc_time_stamp() 
                << std::endl;
      
    } else {
      std::cout << name() << ": Send read request: A = 0x"
                << std::hex << (unsigned int)trans.get_address()
                << " @ " << sc_core::sc_time_stamp()
                << std::endl;
    }
  }

  void logEndTransaction(transaction_type& trans)
  {
    if (trans.get_response_status() != tlm::TLM_OK_RESPONSE) {
      std::cout << name() << ": Received error response @ "
                << sc_core::sc_time_stamp()
                << std::endl;

    } else {
      std::cout << name() <<  ": Received ok response";
      if (trans.get_command() == tlm::TLM_READ_COMMAND) {
          std::cout << ": D = 0x" << std::hex << mData << std::dec;
      }
      std::cout << " @ " 
                << sc_core::sc_time_stamp()
                << std::endl;
    }
  }

  void run()
  {
    transaction_type trans;

    while (initTransaction(trans)) {
      logStartTransation(trans);
      
      // exec instr
      socket->b_transport(trans, mTime);
      wait(mTime);

      logEndTransaction(trans);

      wait(10,SC_NS);
    }
    wait();
  }

private:
  scml_property<unsigned int> mMemSizeProp;
  scml_property<unsigned int> mNbrTransProp;
  scml_property<unsigned int> mBaseAddressProp;
  sc_core::sc_time mTime;
  unsigned int mNrOfTransactions;
  unsigned int mBaseAddress;
  unsigned int mTransactionCount;
  unsigned int mData;
};

#endif /* _TRAFFICGEN_TLM2_H */
