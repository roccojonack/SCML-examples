// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

//  Purpose: test initiator PV module 

#include "testInitiator.h"

/************************************************************************
 * constructor
 */

testInitiator::testInitiator( const sc_module_name & n ) : 
  sc_module( n),
  p("iniP") {
  SC_THREAD( initiatorThread );
  cout << name() << endl; 
}

/************************************************************************
 * clock thread
 */
  
void testInitiator::initiatorThread() {
  localPVReq theReq;
  localPVResp theResp;
  signed int q0, q1, q2, q3, q4, q5, q6, q7;
  
  signed int r0 = -15561 ;
  signed int r1 = -31941 ;
  signed int r2 = 0 ;
  signed int r3 = 0 ;
  signed int r4 = -6144;
  signed int r5 = 590540 ;
  signed int r6 = -30398 ;
  signed int r7 = 0 ;

  cout << name() << " Starting " << endl ;
  theReq.setBurstCount( 1);
  theReq.setDataSize(32);
  
  theReq.setAddress( 0x00000000 );
  theReq.setWriteDataSource( (unsigned int*)& r0 );
  theReq.setType( pvWrite );
  theResp = p.transport( theReq );

  theReq.setAddress( 0x00000001 << 2 );
  theReq.setWriteDataSource( (unsigned int*)& r1 );
  theReq.setType( pvWrite );
  theResp = p.transport( theReq );

  theReq.setAddress( 0x00000002 << 2 );
  theReq.setWriteDataSource( (unsigned int*)& r2 );
  theReq.setType( pvWrite );
  theResp = p.transport( theReq );

  theReq.setAddress( 0x00000003 << 2 );
  theReq.setWriteDataSource( (unsigned int*)& r3 );
  theReq.setType( pvWrite );
  theResp = p.transport( theReq );

  theReq.setAddress( 0x00000004 << 2 );
  theReq.setWriteDataSource( (unsigned int*)& r4 );
  theReq.setType( pvWrite );
  theResp = p.transport( theReq );

  theReq.setAddress( 0x00000005 << 2 );
  theReq.setWriteDataSource( (unsigned int*)& r5 );
  theReq.setType( pvWrite );
  theResp = p.transport( theReq );

  theReq.setAddress( 0x00000006 << 2 );
  theReq.setWriteDataSource( (unsigned int*)& r6 );
  theReq.setType( pvWrite );
  theResp = p.transport( theReq );

  theReq.setAddress( 0x00000007 << 2 );
  theReq.setWriteDataSource( (unsigned int*)& r7 );
  theReq.setType( pvWrite );
  theResp = p.transport( theReq );


  //  IN row 0       : -15561 -31941 0 0 -6144 590540 -30398 0
  // OUT row 0       : 449538 528144 608746 638438 634136 627608 622238 615472
  theReq.setReadDataDestination( (unsigned int*)&q0);
  theReq.setAddress( 0x00000008 << 2 );
  theReq.setType( pvRead );
  theResp = p.transport( theReq );
  
  theReq.setReadDataDestination( (unsigned int*)&q1);
  theReq.setAddress( 0x00000009 << 2 );
  theReq.setType( pvRead );
  theResp = p.transport( theReq );

  theReq.setReadDataDestination( (unsigned int*)&q2);
  theReq.setAddress( 0x0000000a << 2 );
  theReq.setType( pvRead );
  theResp = p.transport( theReq );

  theReq.setReadDataDestination( (unsigned int*)&q3);
  theReq.setAddress( 0x0000000b << 2 );
  theReq.setType( pvRead );
  theResp = p.transport( theReq );

  theReq.setReadDataDestination((unsigned int*) &q4);
  theReq.setAddress( 0x0000000c << 2 );
  theReq.setType( pvRead );
  theResp = p.transport( theReq );

  theReq.setReadDataDestination((unsigned int*) &q5);
  theReq.setAddress( 0x0000000d << 2 );
  theReq.setType( pvRead );
  theResp = p.transport( theReq );

  theReq.setReadDataDestination( (unsigned int*)&q6);
  theReq.setAddress( 0x0000000e << 2 );
  theReq.setType( pvRead );
  theResp = p.transport( theReq );

  theReq.setReadDataDestination( (unsigned int*)&q7);
  theReq.setAddress( 0x0000000f << 2 );
  theReq.setType( pvRead );
  theResp = p.transport( theReq );

  assert( 449538 == q0 );
  assert( 528144 == q1 );
  assert( 608746 == q2 );
  assert( 638438 == q3 );
  assert( 634136 == q4 );
  assert( 627608 == q5 );
  assert( 622238 == q6 );
  assert( 615472 == q7 );
  
  cout << name() << " OK" << endl ;
  sc_stop();
}
