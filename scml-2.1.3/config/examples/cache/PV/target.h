// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: PV model of the cache example target

#ifndef TARGET_H
#define TARGET_H

#include <iostream>
#include <string>
#include <sstream>

#include "scml.h"
#include "PV/PV.h"

template<typename ADDRESS, typename DATA, unsigned int SIZE>
class target:public sc_module
{ 
public:
    typedef PVTarget_port<DATA, ADDRESS> slave_port_type;
    typedef PVReq<DATA, ADDRESS> request_type; 
    typedef PVResp<DATA> response_type; 

public:
    slave_port_type p_pv;
    
    SC_HAS_PROCESS(target);
  
    target(sc_module_name name, unsigned int initialVal) : sc_module(name) 
    , p_pv("p_pv") 
    , mMem("mMem", scml_memsize(SIZE))
    , dbgFlag(false) {  
        p_pv(mMem);
        for(unsigned int loop=0; loop < SIZE; loop++)
            mMem[loop] = initialVal+loop;
        MEMORY_REGISTER_TRANSPORT(mMem, mMemTransportCB);
    }

    scml_memory<unsigned int>::response32_type mMemTransportCB(const scml_memory<unsigned int>::request32_type& req) {
        scml_memory<unsigned int>::response32_type resp = req.obtainResp();
        unsigned int topAddress = req.getAddress();
        unsigned int memIndex = mMem.addressToIndex(topAddress);
        unsigned int burstCount = req.getBurstCount();
        if(req.getType()==pvRead) {
            if(dbgFlag) cout<<this->name()<<": Received read for "<<burstCount<<" words for address - 0x"<<std::hex<<topAddress<<endl;
            for(unsigned int loop = 0; loop < burstCount; loop++)
                resp.setReadData(mMem[memIndex+loop], loop);
        }
        else {
            if(dbgFlag) cout<<this->name()<<": Received write for "<<burstCount<<" words for address - 0x"<<std::hex<<topAddress<<endl;
            for(unsigned int loop = 0; loop < burstCount; loop++) 
                mMem[memIndex+loop] = req.getWriteData(loop);
        }
        resp.setResponse(pvOk);
        return resp;
    }

private:
  scml_memory<DATA> mMem;
  bool dbgFlag;
}; // end class target
#endif 
