// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: PV model of the cache example initiator

#ifndef INITIATOR_H
#define INITIATOR_H

#include "systemc.h"
#include "scml.h"

#include <iostream>
#include <sstream>

class initiator : public sc_module {
public:
    typedef unsigned int address_type;
    typedef unsigned int data_type;
    scml_post_port< data_type, address_type > p_cache;
    scml_post_port< data_type, address_type > p_cache_regs;

    SC_HAS_PROCESS(initiator);
    
    initiator(sc_module_name n) 
            : sc_module( n)
            , p_cache("p_cache")
            , p_cache_regs("p_cache_regs") {
	    SC_THREAD(threadBody);
    }

    ~initiator() {}

private:  
	virtual void end_of_elaboration() {}
    
	void threadBody() {
        unsigned int data;
        unsigned int mem1base = 0x0, mem2base = 0x1000, enableStatsReg=0x0, enableCacheReg=0x4, writePolicyReg=0x18;
        unsigned int hits, misses, reads, writes;

        writeData(p_cache_regs, enableStatsReg, 0x1);
        // Do some writes and reads
        for(int loop=0;loop<0x1000;loop=loop+8) {
            data = readData(p_cache,(mem1base+loop)) + readData(p_cache,(mem2base+loop));
            writeData(p_cache,(mem2base + loop),data);
        }
        hits   = readData(p_cache_regs,0x08);
        misses = readData(p_cache_regs,0x0C);
        reads  = readData(p_cache_regs,0x10);
        writes = readData(p_cache_regs,0x14);
        cout<<this->name()<<": Write back all: Hits = "<<hits<<" Misses = "<<misses<<" Reads = "<<reads<<" Writes = "<<writes<<endl;
        writeData(p_cache_regs, enableCacheReg, 0x0);
        writeData(p_cache_regs, enableCacheReg, 0x1);
        writeData(p_cache_regs, writePolicyReg, 0x0);
        writeData(p_cache_regs, enableStatsReg, 0x2);

        for(int loop=0;loop<0x1000;loop=loop+8) {
            data = readData(p_cache,(mem1base+loop)) + readData(p_cache,(mem2base+loop));
            writeData(p_cache,(mem2base + loop),data);
        }
        hits   = readData(p_cache_regs,0x08);
        misses = readData(p_cache_regs,0x0C);
        reads  = readData(p_cache_regs,0x10);
        writes = readData(p_cache_regs,0x14);
        cout<<this->name()<<": Write through: Hits = "<<hits<<" Misses = "<<misses<<" Reads = "<<reads<<" Writes = "<<writes<<endl;
        writeData(p_cache_regs, enableCacheReg, 0x0);
        writeData(p_cache_regs, enableCacheReg, 0x1);
        writeData(p_cache_regs, writePolicyReg, 0x2);
        writeData(p_cache_regs, enableStatsReg, 0x2);

        for(int loop=0;loop<0x1000;loop=loop+8) {
            data = readData(p_cache,(mem1base+loop)) + readData(p_cache,(mem2base+loop));
            writeData(p_cache,(mem2base + loop),data);
        }
        hits   = readData(p_cache_regs,0x08);
        misses = readData(p_cache_regs,0x0C);
        reads  = readData(p_cache_regs,0x10);
        writes = readData(p_cache_regs,0x14);
        cout<<this->name()<<std::dec
          <<": Write back dirty: Hits = "<<hits
          <<" Misses = "<<misses<<" Reads = "<<reads
          <<" Writes = "<<writes<<endl;

        sc_stop();
    }

    void writeData(scml_post_port<data_type,address_type>& port, unsigned int address, unsigned int data) {
        PVReq< data_type, address_type> req;
        req.setType(pvWrite);
        req.setOffset(0);
        req.setDataSize(32);
        req.setBurstCount(1);
        req.setReadDataDestination(NULL);
        req.setWriteDataSource(&data);
        req.setAddress(address);
        PVResp<data_type> resp = port.transport(req);
        assert(resp.getResponse() == pvOk);
    }
    
    unsigned int readData(scml_post_port<data_type,address_type>& port, unsigned int address) {
        unsigned int data;
        PVReq< data_type, address_type> req;
        req.setType(pvRead);
        req.setAddress(address);
        req.setOffset(0);
        req.setDataSize(32);
        req.setBurstCount(1);
        req.setReadDataDestination(&data);
        req.setWriteDataSource(NULL);
        PVResp<data_type> resp = port.transport(req);
        assert(resp.getResponse() == pvOk);
        return data;
    }

private:
    initiator( const initiator & );
    initiator & operator= ( const initiator & );
};

#endif
