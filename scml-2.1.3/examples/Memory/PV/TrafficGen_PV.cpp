// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

// Purpose: PV model of a simple traffic generator, source file

#include "TrafficGen_PV.h"

//------------------------------------------------------------------------------
// TrafficGen_PV()
// This is the constructor body
//
TrafficGen_PV::TrafficGen_PV(sc_module_name name,
                             unsigned int NumTransactions,
                             unsigned int BurstSize)
  : sc_module(name)
  , p_Comms("p_Comms")
  , m_NumTransactions(NumTransactions)
  , m_BurstSize(BurstSize)
  {
		
      SC_THREAD(main_TrafficGen_PV_process);
      // no sensitivity list
        
      m_WriteDataVal = new int[m_BurstSize];
      m_ReadDataVal  = new int[m_BurstSize];
        
      for (unsigned int i = 0; i < m_BurstSize; i++) {
        m_WriteDataVal[i] = 0;
        m_ReadDataVal[i] = 0;
      }
      
  } //TrafficGen_PV()
  
  // Destructor
  TrafficGen_PV::~TrafficGen_PV() {
    delete m_WriteDataVal;
    delete m_ReadDataVal;
  } //~TrafficGen_PV()


//------------------------------------------------------------------------------
// start_of_simulation()
// This is called automatically by the kernel
//
void TrafficGen_PV::start_of_simulation()
{
  cout << this->name() << " : start of simulation" << endl;
}

void TrafficGen_PV::burstAccess () {
   // Populate the data array for this burst
	 // NOTE: PV uses non word-aligned addressing.
	 // At this point we use byte-addressing mode and convert later
	 // Because we need to be interoperable with OCP it is easier to maintain word-alignment
    
    for (unsigned int i = 0; i < m_BurstSize; i++) {
      
      m_WriteDataVal[i] = ( (m_DataVal >> m_AddrOffset) & getMask(m_AccessType) );
      
      cout << name() << " : start WR [0x" << hex << (m_AddrVal + (m_DataSize >> 3)*i) << "]=" << m_WriteDataVal[i]
	   << " : Offset=" << dec << m_AddrOffset << " : Dsize=" << dec << m_DataSize
	   << " : Bsize=" << m_BurstSize << endl;
      m_DataVal++;
    }
	
    // Do a write burst transaction
    BehavReq.setAddress(m_AddrVal);
    BehavReq.setOffset(m_AddrOffset);
    BehavReq.setType(pvWrite);
    BehavReq.setWriteDataSource((unsigned int*)m_WriteDataVal);
    BehavReq.setDataSize(m_DataSize);
    BehavReq.setBurstCount(m_BurstSize);

    // Convert to PV address
    setPVAddressOffset(BehavReq);
    
    BehavResp = p_Comms.transport(BehavReq);
    
    if (BehavResp.getResponse() != pvOk) {
      cout << name() << " : WR STATUS ERROR!!!" << endl;
    }


    cout << endl;
    cout << name() << " : start RD [0x" << hex << m_AddrVal << "] : Dsize=" << dec << m_DataSize
         << " : Offset=" << dec << m_AddrOffset << " : Bsize=" << m_BurstSize << endl;

    // Do a read transaction
    BehavReq.setAddress(m_AddrVal);
    BehavReq.setOffset(m_AddrOffset);
    BehavReq.setType(pvRead);
    BehavReq.setDataSize(m_DataSize);
    BehavReq.setBurstCount(m_BurstSize);	  
    BehavReq.setReadDataDestination((unsigned int*)m_ReadDataVal);
	 
    // Convert to PV address
    setPVAddressOffset(BehavReq);
	 
    BehavResp = p_Comms.transport(BehavReq);
    if (BehavResp.getResponse() != pvOk) {
      cout << name() << " : RD STATUS ERROR!!!" << endl;
    }

    for (unsigned int i = 0; i < m_BurstSize; i++) {
      cout << this->name() << " : RD: Response: [0x" << hex << (m_AddrVal + 4*i) << "]=" << m_ReadDataVal[i]
           << " : " << BehavResp.getResponse() << dec << endl;
    }
    
    wait (m_TransCount % 3, SC_NS);
}

void TrafficGen_PV::unrollBurstAccess () {
   // Populate the data array for this burst
	 // NOTE: PV uses non word-aligned addressing.
	 // At this point we use byte-addressing mode and convert later
	 // Because we need to be interoperable with OCP it is easier to maintain word-alignment
    
    for (unsigned int i = 0; i < m_BurstSize; i++) {
      
      m_WriteDataVal[i] = ( (m_DataVal >> m_AddrOffset) & getMask(m_AccessType) );
      m_DataVal++;
    }
    
    unsigned int loc_WriteDataVal;
    // Do a write transaction
    BehavReq.setOffset(m_AddrOffset);
    BehavReq.setType(pvWrite);
    BehavReq.setWriteDataSource(&loc_WriteDataVal);
    BehavReq.setBurstCount(1);	  
    BehavReq.setDataSize(m_DataSize);
    
    for (unsigned int i = 0; i < m_BurstSize; i++) {
      loc_WriteDataVal = m_WriteDataVal[i];
      
      cout << name() << " : start WR [0x" << hex << (m_AddrVal + getDataSizeInBytes(m_AccessType)*i) << "]=" 
           << m_WriteDataVal[i]
	   << " : Offset=" << dec << m_AddrOffset << " : Dsize=" << dec << m_DataSize
	   << " : Bsize=" << 1 << endl;
	
      // Do a write transaction
      BehavReq.setAddress(m_AddrVal+getDataSizeInBytes(m_AccessType)*i);

      // Convert to PV address
      setPVAddressOffset(BehavReq);
    
      BehavResp = p_Comms.transport(BehavReq);
    
      if (BehavResp.getResponse() != pvOk) {
        cout << name() << " : WR STATUS ERROR!!!" << endl;
      }
      wait (m_TransCount % 3, SC_NS);
    }

    unsigned int loc_ReadDataVal;
    // Do a read transaction
    BehavReq.setOffset(m_AddrOffset);
    BehavReq.setType(pvRead);
    BehavReq.setDataSize(m_DataSize);
    BehavReq.setBurstCount(1);	  
    BehavReq.setReadDataDestination(&loc_ReadDataVal);
    for (unsigned int i = 0; i < m_BurstSize; i++) {
      cout << endl;
      cout << name() << " : start RD [0x" << hex << m_AddrVal+getDataSizeInBytes(m_AccessType)*i << "] : Dsize="
           << dec << m_DataSize
           << " : Offset=" << dec << m_AddrOffset << " : Bsize=" << m_BurstSize << endl;

      // Do a read transaction
      BehavReq.setAddress(m_AddrVal+getDataSizeInBytes(m_AccessType)*i);
	 
      // Convert to PV address
      setPVAddressOffset(BehavReq);
	 
      BehavResp = p_Comms.transport(BehavReq);
      if (BehavResp.getResponse() != pvOk) {
        cout << name() << " : RD STATUS ERROR!!!" << endl;
      }
      m_ReadDataVal[i] = loc_ReadDataVal;

      cout << this->name() << " : RD: Response: [0x" << hex << (m_AddrVal+getDataSizeInBytes(m_AccessType)*i ) << "]=" 
           << m_ReadDataVal[i]
           << " : " << BehavResp.getResponse() << dec << endl;
      
      wait (m_TransCount % 3, SC_NS);
    }
}

//------------------------------------------------------------------------------
// main_TrafficGen_PV_process()
// This is the main process that generates the traffic
//
void TrafficGen_PV::main_TrafficGen_PV_process() {
  // initialize transaction parameters
  m_TransCount = 0;
  m_DataVal = 0x55AA1234;
  m_AddrVal = 0;
  m_AddrOffset = 0;
  m_DataSize = 32;
  m_AccessType = e32;

  // sit in while loop until we have finished all tests
  while(m_TransCount < m_NumTransactions) {
	
    if (m_AccessType == e32) {
      burstAccess();
    } else {
      unrollBurstAccess();
    }

    // Test Data
    for (unsigned int i = 0; i < m_BurstSize; i++) {
      if ( m_ReadDataVal[i] != m_WriteDataVal[i] ) {
	cout << i << endl;
	cout << this->name() << " : R/W ERROR !!!! : WR Data: " << hex << m_WriteDataVal[i];
	cout << " != RD Data: " << hex << m_ReadDataVal[i] << dec << endl;
      }
    }
	 

    // Increment byte address
	 // Use word-aligned addresses for compatibility with OCP
	 // otherwise it just gets too complicated and confusing!!
    m_AddrVal += ( 4 * m_BurstSize);

    // Get the next access type
    m_AccessType = getNextAccessType(m_AccessType);
    
    
    // Get next data size and address offset
    m_DataSize = getDataSize(m_AccessType);
    m_AddrOffset = getOffset(m_AccessType);

    m_TransCount++;

  } // end while()
	
  cout << endl << name() << " : TEST COMPLETE : NumBursts=" << dec << m_TransCount << endl;
}


//------------------------------------------------------------------------------
// setPVAddressOffset()
// Helper function to convert from non-aligned byte address to required
// PVAddress
// NOTE: In order for this to work with OCP we need to ensure that some access are half-word
//       or word-aligned, i.e we cannot straddle a word or a half-word relative to a word boundary
//
void TrafficGen_PV::setPVAddressOffset(PVReq< unsigned int, unsigned int >& Req) {
  unsigned int ByteAddress, PVAddress, PVOffset, Offset;

  // assumption: address coming in is a non-aligned byte address with Offset =/= 0
  // Size stays the same
  // BurstSize stays the same
  ByteAddress = Req.getAddress();
  Offset = Req.getOffset();
  
  PVAddress = ByteAddress + (Offset >> 3);
  PVOffset = 0; 

#ifdef DEBUGTrafficGen_PV
  cout << this->name() << " : setPVAddressOffset() : Raw : " << ByteAddress << " : " << Offset   << endl;
  cout << this->name() << " : setPVAddressOffset() : PV : "  << PVAddress   << " : " << PVOffset << endl;
#endif

  // Pass modified parameters to request object
  Req.setAddress(PVAddress);
  Req.setOffset(PVOffset);

}


//------------------------------------------------------------------------------
// getNextAccessType()
// Helper function to cycle thru all 8,16,32 bit access types on subsequent bursts
//
TrafficGen_PV::eAccessType_t TrafficGen_PV::getNextAccessType(TrafficGen_PV::eAccessType_t Curr) {

  switch(Curr) {
    case e32:
      return e16_0;
    case e16_0:
      return e16_1;
    case e16_1:
      return e8_0;
    case e8_0:
      return e8_1;
    case e8_1:
      return e8_2;
    case e8_2:
      return e8_3;
    case e8_3:
      return e32;
    default:
      return e32;
  }

}


//------------------------------------------------------------------------------
// getDataSize()
// Helper function to get the address offset for the cirrent access type
//
unsigned int TrafficGen_PV::getDataSize(TrafficGen_PV::eAccessType_t Curr) {

  switch(Curr) {
    case e32:
      return 32;
    case e16_0:
    case e16_1:
      return 16;
    case e8_0:
    case e8_1:
    case e8_2:
    case e8_3:
      return 8;
    default:
      cout << name() << " : FATAL ERROR unrecognised AccessType = " << Curr << endl;
      sc_assert(false);
      return 32;
  }
}

//------------------------------------------------------------------------------
// getDataSize()
// Helper function to get the address offset for the current access type
//
unsigned int TrafficGen_PV::getDataSizeInBytes(TrafficGen_PV::eAccessType_t Size) {

  switch(Size) {
    case e32:
      return 4;
    case e16_0:
    case e16_1:
      return 2;
    case e8_0:
    case e8_1:
    case e8_2:
    case e8_3:
      return 1;
    default:
      cout << name() << " : FATAL ERROR unrecognised AccessType = " << Size << endl;
      sc_assert(false);
      return 4;
  }
}

//------------------------------------------------------------------------------
// getOffset()
// Helper function to cycle thru 8,16,32 bit data size on subsequent bursts
//
unsigned int TrafficGen_PV::getOffset(TrafficGen_PV::eAccessType_t Curr) {

  switch(Curr) {
    case e32:
    case e16_0:
    case e8_0:
      return 0;
    case e16_1:
    case e8_2:
      return 16;
    case e8_1:
      return 8;
    case e8_3:
      return 24;
    default:
      cout << name() << " : FATAL ERROR: unrecognised AccessType = " << Curr << endl;
      sc_assert(false);
      return 0;
  }
}


//------------------------------------------------------------------------------
// getMask()
// Gets the mask for the current data size. The mask is for masking off higher bytes
// once the data has been shifted down to 0 for the PV data
// e.g. data = 0x12345678, size=16, offset = 0, then we do not shift but need to mask off
// so that PV data = 0x00005678.
//
unsigned int TrafficGen_PV::getMask(TrafficGen_PV::eAccessType_t AccessType) {

  switch(AccessType) {
    case e32:
      return 0xFFFFFFFF;
    case e16_0:
    case e16_1:
      return 0x0000FFFF;
    case e8_0:
    case e8_1:
    case e8_2:
    case e8_3:
      return 0x000000FF;
    default:
      cout << name() << " : FATAL ERROR unrecognised AccessType = " << AccessType << endl;
      sc_assert(false);
      return 0;
  }
}
