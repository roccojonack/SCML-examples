// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: n-way Set associative cache model with configurable n,
// different write policies, configurable cache size, configurable memory 
// size, configurable cache line size and also gathering of statistics

#ifndef CACHE_H
#define CACHE_H

#include "PV/PV.h"
#include "scml.h"
#include "linkedList.h"

/* Implementation of L2 Cache Controller using scml_router*/
template<typename ADDRESS, typename PV_DATA, typename DATA>
class cache : public sc_module
{ 
public :
    // Types
    enum WritePolicy {
        WriteThrough   = 0x0,
        WriteBackAll   = 0x1,
        WriteBackDirty = 0x2,
    };
    typedef PVTarget_port<PV_DATA, ADDRESS> slave_port_type;
    typedef PVReq<PV_DATA, ADDRESS> request_type; 
    typedef PVResp<PV_DATA> response_type; 
    typedef scml_post_port<PV_DATA, ADDRESS> initiator_port_type;
    
    // Ports
    slave_port_type p_pv;
    slave_port_type p_pv_regs;
    initiator_port_type p_post;
    sc_in<bool> p_reset; 
    SC_HAS_PROCESS(cache);

/* cache(sc_module_name name) 
** Constructor for cache
*/  
    cache(sc_module_name name)
            : sc_module(name)
            , p_pv("p_pv")
            , p_pv_regs("p_pv_regs")
            , p_post("p_post")
            , p_reset("p_reset")
            , memorySize("memorySize",0x800)
            , cacheSize("cacheSize",0x80)
            , setSize("setSize",0x4)
            , lineSize("lineSize",0x4)
            , writePolicy("writePolicy",1)
            , mCachedMemory("mCachedMemory", scml_memsize(memorySize))
            , mCacheStorage("mCacheStorage", scml_memsize(cacheSize))
            , mRegisters("mRegisters", scml_memsize(8))
            , mEnableStatsReg("ENABLESTATS_REG", mRegisters, 0, 1)
            , mEnableCacheReg("ENABLECACHE_REG", mRegisters, 1, 1)
            , mCacheHitsReg("CACHEHITS_REG", mRegisters, 2, 1)
            , mCacheMissesReg("CACHEMISSES_REG", mRegisters, 3, 1)
            , mMemoryReadsReg("MEMORYREADS_REG", mRegisters, 4, 1)
            , mMemoryWritesReg("MEMORYWRITES_REG", mRegisters, 5, 1)
            , mWritePolicyReg("WRITEPOLICY_REG", mRegisters, 6, 1)
            , mWriteBackOnReset("WRITEBACKONRESET", mRegisters, 7, 1)
            , mStatsEnabled(true)
            , mCacheEnabled(true)
            , dbgFlag(false) {
        // Check that we have a correct ratio
        assert(memorySize % cacheSize == 0);
        assert((lineSize==1) || ((lineSize % 2)==0));
        assert(setSize!=0);
        numberOfSets = ((cacheSize/lineSize)/setSize);

        p_pv(mCachedMemory);
        p_pv_regs(mRegisters);
        
        mRegisters.initialize(0);
        mEnableCacheReg.initialize(1);
        mCacheHitsReg.set_read_only();
        mCacheMissesReg.set_read_only();
        mMemoryReadsReg.set_read_only();
        mMemoryWritesReg.set_read_only();
        mWriteBackOnReset.set_write_only();
        // Initialize cache line Info array
        cacheLineInfoArray = new linkedList[numberOfSets];
        for(unsigned int loopVar=0; loopVar < numberOfSets; loopVar++)
            cacheLineInfoArray[loopVar].setSizeofSet(setSize);
        
        // Register callback functions
        ROUTER_REGISTER_TRANSPORT(mCachedMemory, transportCachedMemory);
        MEMORY_REGISTER_TRANSPORT(mCacheStorage, transportCacheStorage);
        MEMORY_REGISTER_WRITE(mEnableStatsReg, writeEnableStatsReg);
        MEMORY_REGISTER_WRITE(mEnableCacheReg, writeEnableCacheReg);
        MEMORY_REGISTER_WRITE(mWritePolicyReg, writeWritePolicy);

        // Reset function sensitive to reset pin
        SC_METHOD(resetCache);
        sensitive << p_reset;
        dont_initialize();

    }
    
    
    ~cache() {
        delete[] cacheLineInfoArray;
    }

/* scml_memory<unsigned int>::response32_type transportCachedMemory(const scml_memory<unsigned int>::request32_type& req)
** This callback is attached to scml_router implementing cache. This is invoked  in case of miss.
** It calculate sets to which this address belongs checks if corresponding set has any free cacheLine, if not replace a line.
** when a line is replaced node is deleted from head as it is least recently used node.
** Futher it maps this address to the free or replaced cacheIndex, update cacheLineInfoArray by adding a node at tail.
** Completes the access for current word from cache storage.
*/
    scml_memory<unsigned int>::response32_type transportCachedMemory(const scml_memory<unsigned int>::request32_type& localReq) {
        // Pass on debug access
        if(localReq.getMode()==pvDebug) {
            return p_post.transport(localReq);
        }

        assert(localReq.getOffset() == 0);
        assert(localReq.getDataSize() == (sizeof(DATA) * 8));

        PVResp<DATA> localResp = localReq.obtainResp();

        if(mStatsEnabled) {
            mCacheMissesReg++; 
        }
        
        //local vars
        unsigned int numberOflines = 0;
        unsigned int numberOfWords = 0;
        unsigned int cacheStorageAddress, cacheStorageIndex, loopCount;

        //burst info
        unsigned int burstSize = localReq.getBurstCount();
        unsigned int transferSize = localReq.getDataSize();
        uint64 burstEndAddr = (localReq.getAddress() + (burstSize * (transferSize/8))) - 1;

        //word and line info
        uint64 wordAddress = localReq.getAddress();
        size_t wordIndex = mCachedMemory.addressToIndex(wordAddress);
        size_t lineIndex = (wordIndex/lineSize)*lineSize;
        unsigned int lineAddress = mCachedMemory.indexToAddress(lineIndex);
        unsigned int lineEndAddress = (lineAddress + (lineSize * sizeof(DATA))) - 1;

        if(dbgFlag) {
            cout<<this->name()<<": Miss: for address - 0x"<<std::hex<<wordAddress<<" Burst Length - "<<burstSize<<endl;
        }
              
        //map all the lines which will be required to serve the burst
        while (1) {
            numberOflines++;
            //calculate cache location
            unsigned int setIndex = (lineIndex/lineSize) % numberOfSets;
            unsigned int tagIndex = (lineIndex/lineSize) / numberOfSets;
       
            int cacheIndexInSet = cacheLineInfoArray[setIndex].getFreeCacheIndex();
            int cacheIndex =  ((setIndex * setSize) + cacheIndexInSet) * lineSize;

            //replace a line if required
            if(cacheIndexInSet==-1) { 
                ptrCacheLineInfo replacedNode = cacheLineInfoArray[setIndex].removeNodeFromHead();
                cacheIndexInSet = replacedNode->cacheIndex;
                cacheIndex =  ((setIndex * setSize) + cacheIndexInSet) * lineSize;
                unsigned int replacedLineAddr = mCachedMemory.indexToAddress(((replacedNode->tag * numberOfSets) + setIndex)*lineSize);
                if((writePolicy == WriteBackAll) || ((writePolicy == WriteBackDirty) && (replacedNode->dirtyBit == true))) {
                    writeData(replacedLineAddr, cacheIndex, lineSize);
                }
                mCachedMemory.unmap(replacedLineAddr);
                if(dbgFlag) {
                    cout<<this->name()<<": Miss: Replacing cache Line: 0x"<<std::hex<<replacedLineAddr<<endl;
                }
                delete replacedNode;
            } 

            //Map the address to cache, update cacheLineInfoArray
            cacheLineInfoArray[setIndex].addNodeAtTail(false, cacheIndexInSet, tagIndex);
            if(dbgFlag) {
                cout<<this->name()<<": Miss: Mapping address to set - "<<setIndex <<" at line - "<<cacheIndexInSet<<endl;
            }
            mCachedMemory.map(lineAddress, lineSize * sizeof(DATA), mCacheStorage, mCacheStorage.indexToAddress(cacheIndex));

            //read the line from memory to cache
            readData(lineAddress, cacheIndex, lineSize);

            // Perform the access
            if(numberOflines == 1) {
                cacheStorageAddress =  mCacheStorage.indexToAddress(cacheIndex) + (wordAddress - lineAddress);
                cacheStorageIndex = mCacheStorage.addressToIndex(cacheStorageAddress);
                loopCount = lineSize-(wordIndex-lineIndex);
                if(dbgFlag) {
                    if(localReq.getType() == pvRead) {
                        cout<<this->name()<<": Reading from cache memory"<<endl;
                    }
                    else {
                        cout<<this->name()<<": Writing to cache memory"<<endl;
                    }
                }
            }    
            else {
                cacheStorageIndex = cacheIndex;
                cacheStorageAddress = mCacheStorage.indexToAddress(cacheIndex);
                loopCount = lineSize;
                if(dbgFlag) {
                    if(localReq.getType() == pvRead) {
                        cout<<this->name()<<": Reading from cache memory"<<endl;
                    }
                    else {
                        cout<<this->name()<<": Writing to cache memory"<<endl;
                    }
                }
            }

            if (localReq.getType() == pvRead) {
                for(unsigned int loopVar = 0; loopVar < loopCount; loopVar++) {
                    localResp.setReadData(mCacheStorage.get(cacheStorageIndex+loopVar), numberOfWords);
                    numberOfWords++;
                    if(numberOfWords == burstSize) {
                        break;
                    }
                }
            }
            else {
                for(unsigned int loopVar = 0; loopVar < loopCount; loopVar++) {
                    mCacheStorage.put(localReq.getWriteData(numberOfWords), cacheStorageIndex+loopVar);
                    numberOfWords++;
                    if(numberOfWords == burstSize) {
                        break;
                    }
                }
                cacheLineInfoArray[setIndex].setDirty(cacheIndexInSet);
                if(writePolicy==WriteThrough) {
                    writeData(lineAddress, cacheIndex, lineSize);
                }
            }

            //check if all required line fetched
            if(burstEndAddr <= lineEndAddress) {
                break;
            }
            else {
                lineAddress = (lineAddress + (lineSize * sizeof(DATA)));
                lineEndAddress = (lineAddress + (lineSize * sizeof(DATA))) - 1;
                lineIndex = mCachedMemory.addressToIndex(lineAddress);
            }
        }

        if(dbgFlag) {
            cout<<endl;
        }
 
        // Send response
        localResp.setResponse(pvOk);
        return localResp;
    }

/* scml_memory<unsigned int>::response32_type transportCacheStorage(const scml_memory<unsigned int>::request32_type& req)
** This function is callback attached to scml_memory implementing cache. This is invoked in case of a hit.
** This function updates the cacheInfo structure to move recently accessed node at tail.
** This further performs access and writeThrough in case of regular bus access / backdoors.
*/
    scml_memory<unsigned int>::response32_type transportCacheStorage(const scml_memory<unsigned int>::request32_type& localReq) {
        assert(localReq.getOffset() == 0);

        if(mStatsEnabled) {
            mCacheHitsReg++; 
        }

        unsigned int memoryAddr(0);
        unsigned int burstSize = localReq.getBurstCount();
        PVResp<DATA> localResp = localReq.obtainResp();

        // Compute the cache location
        uint64 address = localReq.getAddress();
        size_t wordIndex = mCachedMemory.addressToIndex(address);
        size_t lineIndex = (wordIndex/lineSize)*lineSize;
        unsigned int lineAddress = mCachedMemory.indexToAddress(lineIndex);
        unsigned int cacheIndex = (wordIndex/lineSize)*lineSize; 
        unsigned int setIndex = (cacheIndex/lineSize) / setSize;
        unsigned int cacheIndexInSet = (cacheIndex/lineSize) % setSize;

        if(dbgFlag || (writePolicy==WriteThrough)) {
            memoryAddr = mCachedMemory.indexToAddress((((cacheLineInfoArray[setIndex].getTag(cacheIndexInSet) * numberOfSets) + setIndex)*lineSize + (wordIndex-cacheIndex)));
        }

        if(dbgFlag) {
            cout<<this->name()<<": Hit: for Address - 0x"<<std::hex<<memoryAddr<<endl;
            cout<<this->name()<<": Hit: at set - "<<setIndex<<" line - "<<cacheIndexInSet<<" of cache"<<endl;
        }

        // Move the accessed node at the tail to implement least recently used replacement policy
            cacheLineInfoArray[setIndex].moveNodeToTail(cacheIndexInSet);

        //Perform the access
        if (localReq.getType() == pvRead) {
            if(dbgFlag) {
                cout<<this->name()<<": Reading from cache memory - "<<std::hex<<address<<endl;
            }
            for(unsigned int loopVar = 0; loopVar < burstSize; loopVar++) {
                localResp.setReadData(mCacheStorage.get(wordIndex+loopVar), loopVar);
            }
        }
        else {
            for(unsigned int loopVar = 0; loopVar < burstSize; loopVar++) {
                mCacheStorage.put(localReq.getWriteData(loopVar), wordIndex+loopVar);
            }
            if(dbgFlag) {
                cout<<this->name()<<": Writing to cache memory - "<<std::hex<<address<<endl;
            }
            cacheLineInfoArray[setIndex].setDirty(cacheIndexInSet);
            if(writePolicy==WriteThrough) {
                writeData(lineAddress, cacheIndex, lineSize);
            }
        }

        if(dbgFlag) {
            cout<<endl;
        }

        // Send response
        localResp.setResponse(pvOk);
        return localResp;      
    }

/* void writeData(unsigned int memAddress, unsigned int cacheIndex, unsigned int burstSize)
** This function writes burstSize number of words from cacheIndex of cache to 
** memAddress of memory architecture connected to p_post
*/ 
    void writeData(unsigned int memAddress, unsigned int cacheIndex, unsigned int burstSize) {
        DATA * data;
        data = new DATA[burstSize];

        for(unsigned int loopVar = 0; loopVar < burstSize; loopVar++) {
            data[loopVar] = mCacheStorage[cacheIndex+loopVar];
        }

        req.setType(pvWrite);
        req.setOffset(0);
        req.setDataSize((8 * sizeof(DATA)));
        req.setBurstCount(burstSize);
        req.setBurstType(pvIncr);
        req.setReadDataDestination(NULL);
        req.setWriteDataSource(data);
        req.setAddress(memAddress);
        resp = p_post.transport(req);
        assert(resp.getResponse() == pvOk);
        if(dbgFlag) {
            std::cerr << this->name() << ": Wrote from cacheIndex: "<<cacheIndex<<" to memory: 0x" << std::hex<<memAddress << std::endl;
        }

        if(mStatsEnabled) { 
            mMemoryWritesReg++; 
        }
        delete data;
    }

/* void readData(unsigned int memAddress, unsigned int cacheIndex, unsigned int burstSize)
** This function reads burstSize number of words to cacheIndex of cache from 
** memAddress of memory architecture connected to p_post
*/    
    void readData(unsigned int memAddress, unsigned int cacheIndex, unsigned int burstSize) {
        DATA * data;
        data = new DATA[burstSize];

        req.setType(pvRead);
        req.setAddress(memAddress);
        req.setOffset(0);
        req.setDataSize((8 * sizeof(DATA)));
        req.setBurstCount(burstSize);
        req.setBurstType(pvIncr);
        req.setReadDataDestination(data);
        req.setWriteDataSource(NULL);
        resp = p_post.transport(req);
        assert(resp.getResponse() == pvOk);
        if(dbgFlag) {
            std::cerr << this->name() << ": Read into cacheIndex: "<<cacheIndex<<" from memory: 0x" <<std::hex<<memAddress << std::endl;
        }

        for(unsigned int loopVar = 0; loopVar < burstSize; loopVar++) {
            mCacheStorage[cacheIndex+loopVar] = data[loopVar];
        }

        if(mStatsEnabled) {
            mMemoryReadsReg++; 
        }
        delete data;
    }

/* void writeBackCache()
** This function writes all the entry from cache back to memory when cache is disabled. 
** This function is called by command processor when disable_cache command
** is executed by user
*/ 
    void writeBackCache() {
        if(writePolicy==WriteThrough) {
            return;
        }
        for(unsigned int loop = 0; loop < numberOfSets; loop++) {
            ptrCacheLineInfo currNode = cacheLineInfoArray[loop].head;
            while(currNode!=NULL) {
                unsigned int cacheIndexInSet = currNode->cacheIndex;
                unsigned int cacheIndex = ((loop * setSize) + cacheIndexInSet) * lineSize;
                unsigned int memoryAddr = mCachedMemory.indexToAddress(((cacheLineInfoArray[loop].getTag(cacheIndexInSet) * numberOfSets) + loop)*lineSize);
                writeData(memoryAddr, cacheIndex, lineSize);
                currNode = currNode->next;
            } 
        }
    }

/* void writeEnableStatsReg(unsigned int value, unsigned int, unsigned int)
** This function is callback attached to mEnableStatsReg register
*/
    void writeEnableStatsReg(unsigned int value, unsigned int, unsigned int) {
        if(value == 1) {
            if(dbgFlag) {
                cout << sc_module::name() << " : Enabling Statistics " << endl;
            }
            mStatsEnabled = 1;
        }
        else 
        if(value == 0) {
            if(dbgFlag) {
                cout << sc_module::name() << " : Disabling Statistics " << endl;
            }
            mStatsEnabled = 0;
        } 
        else if(value == 2) {
            if(dbgFlag) {
                cout << sc_module::name() << " : Clearing Statistical data " << endl;
            }
            mCacheHitsReg = 0;
            mCacheMissesReg = 0; 
            mMemoryReadsReg = 0;
            mMemoryWritesReg = 0;
        }
        if(value != 2) {
            mEnableStatsReg = value;
        }
    }

/* void writeEnableCacheReg(unsigned int value, unsigned int, unsigned int)
** This function is callback attached to mEnableCacheReg register
*/
    void writeEnableCacheReg(unsigned int value, unsigned int, unsigned int) {
        if(mEnableCacheReg!=value) {
            if(value == 1) {
                mCacheEnabled = 1;
                if(dbgFlag) {
                    cout << sc_module::name() << " : Enabling Cache " << endl;
                }
                mCachedMemory.unmap_all();
                // Initialize cache line Info array
                cacheLineInfoArray = new linkedList[numberOfSets];
                for(unsigned int loopVar=0; loopVar < numberOfSets; loopVar++) {
                    cacheLineInfoArray[loopVar].setSizeofSet(setSize);
                }
            }
            else if(value == 0) {
                mCacheEnabled = 0;
                if(dbgFlag) {
                    cout << sc_module::name() << " : disabling Cache " << endl;
                }
                mCachedMemory.unmap_all();
                mCachedMemory.map(0x0, memorySize, p_post, 0x0);
                writeBackCache();
                delete[] cacheLineInfoArray;
            } 
            mEnableCacheReg = value;
        }
    }

/* void writeWritePolicy(unsigned int value, unsigned int, unsigned int)
** This function writes local varaible and mWritePolicyReg register.
** This function is callback attached to this register
*/
    void writeWritePolicy(unsigned int value, unsigned int, unsigned int) {
        writePolicy = value;
        mWritePolicyReg = value;
        if(dbgFlag) {
            cout << sc_module::name() << " : write_policy set to ";
            switch(value) {
                case WriteThrough:
                    cout<<"Write through"<<endl;
                    break;
                case WriteBackAll:
                    cout<<"Write Back All"<<endl;
                    break;
                case WriteBackDirty:
                    cout<<"Write Back Dirty"<<endl;
                    break;
            }
        }
    }

/* void resetCache() 
** Reset function, sensitive to p_reset
** Write back all data from cache to memory as per the write policy and writeBackOnReset value, 
** Set statistics to zero, delete old cacheLineInfo data and create a new, 
** set cache storage contents to zero
*/
    void resetCache() {
        if(p_reset==1) {
            writeEnableStatsReg(2,32,0);
            mCachedMemory.unmap_all();
            if(mWriteBackOnReset == 1) {
                writeBackCache();
            }
            delete[] cacheLineInfoArray;
            mCacheStorage.initialize(0);
            cacheLineInfoArray = new linkedList[numberOfSets];
            for(unsigned int loopVar=0; loopVar < numberOfSets; loopVar++) {
                cacheLineInfoArray[loopVar].setSizeofSet(setSize);
            }
            if(dbgFlag) {
                cout<< sc_module::name() << " : cache being reset"<<endl;
            }
        }
    }

/* void dumpInfo(std::ostream& os)
** This function prints attributes of cache instance
** This function is called by command processor when show_info command
** is executed by user
*/
   void dumpInfo(std::ostream& os) {
        os << sc_module::name() << "Memory size: " << memorySize << std::endl;
        os << sc_module::name() << "Cache size: " << cacheSize << std::endl;
        os << sc_module::name() << "Cache is "<< setSize << "-way set associative" << std::endl;
        os << sc_module::name() << "Cache Line size: " << lineSize << std::endl;
        os << sc_module::name() << "Write policy: ";
        switch (writePolicy) {
            case WriteThrough:   os << "Write through"<<endl; break;
            case WriteBackAll:   os << "Write back (all)"<<endl; break;
            case WriteBackDirty: os << "Write back (dirty only)"<<endl; break;
        }
    }
/* void dumpStatistics(std::ostream& os)
** This function prints statistical data collected if statistics is enabled
** This function is called by command processor when show_statistics command
** is executed by user
*/        
    void dumpStatistics(std::ostream& os) {
        os << sc_module::name() << "Cache hits: " << mCacheHitsReg << std::endl;
        os << sc_module::name() << "Cache misses: " << mCacheMissesReg << std::endl;
        os << sc_module::name() << "Memory reads: " << mMemoryReadsReg << std::endl;
        os << sc_module::name() << "Memory writes: " << mMemoryWritesReg << std::endl;
    }
  
private:
  // Configurable attributes of cache as scml_properties
  scml_property<unsigned int> memorySize;
  scml_property<unsigned int> cacheSize;
  scml_property<unsigned int> setSize;
  scml_property<unsigned int> lineSize;
  scml_property<unsigned int> writePolicy;

  // scml_router to implement cache and scml_meory to implement cache storage
  scml_router<DATA> mCachedMemory;
  scml_memory<DATA> mCacheStorage;

  // control registers
  scml_memory<unsigned int> mRegisters;
  scml_memory<unsigned int> mEnableStatsReg;
  scml_memory<unsigned int> mEnableCacheReg;
  scml_memory<unsigned int> mCacheHitsReg;
  scml_memory<unsigned int> mCacheMissesReg;
  scml_memory<unsigned int> mMemoryReadsReg;
  scml_memory<unsigned int> mMemoryWritesReg;
  scml_memory<unsigned int> mWritePolicyReg;
  scml_memory<unsigned int> mWriteBackOnReset;
  // Contains info - (dirtybit, tag, cacheIndex) for each cache line within each set
  linkedList * cacheLineInfoArray;

  // Other variables
  bool mStatsEnabled, mCacheEnabled;
  unsigned int numberOfSets;

  // Other variables
  bool dbgFlag;

  // Local request and response 
  PVReq<DATA,ADDRESS> req;
  PVResp<DATA> resp;
  
}; // end class cache

#endif // CACHE
