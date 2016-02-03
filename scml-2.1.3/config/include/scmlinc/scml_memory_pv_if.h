/*****************************************************************************
 *                   Copyright (C) 1996-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
/*
 * Modifications :
 *
 * Purpose of file : Definition of PV used in scml_memory
 *
 */

#ifndef SCML_MEMORY_PV_IF_H
#define SCML_MEMORY_PV_IF_H

#include <vector>
using std::vector;
#include <string>
using std::string;

#include <PV/PV.h>
//FIXME
#include "scmlinc/scml_types.h"
#include <systemc>

namespace PV {
  template< unsigned int > struct dataWidth2Type; 
  template<> struct dataWidth2Type < 0 > { typedef unsigned int result; };

  template<> struct dataWidth2Type < 1 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 2 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 3 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 4 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 5 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 6 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 7 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 8 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 9 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 10 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 11 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 12 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 13 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 14 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 15 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 16 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 17 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 18 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 19 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 20 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 21 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 22 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 23 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 24 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 25 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 26 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 27 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 28 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 29 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 30 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 31 > { typedef unsigned int result; };
  template<> struct dataWidth2Type < 32 > { typedef unsigned int result; };

  template<> struct dataWidth2Type < 33 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 34 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 35 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 36 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 37 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 38 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 39 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 40 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 41 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 42 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 43 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 44 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 45 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 46 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 47 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 48 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 49 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 50 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 51 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 52 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 53 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 54 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 55 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 56 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 57 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 58 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 59 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 60 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 61 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 62 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 63 > { typedef unsigned long long result; };
  template<> struct dataWidth2Type < 64 > { typedef unsigned long long result; };

  template<> struct dataWidth2Type < 128 > { typedef sc_dt::sc_biguint<128> result; };
  template<> struct dataWidth2Type < 256 > { typedef sc_dt::sc_biguint<256> result; };
  template<> struct dataWidth2Type < 512 > { typedef sc_dt::sc_biguint<512> result; };
}

/************************************************************************
 * 
 */
template< unsigned int address_width = 32, 
	  unsigned int data_width = 64 >
class scml_memory_pv_if : 
  virtual public PV_if< typename PV::dataWidth2Type< data_width >::result,
                        typename PV::dataWidth2Type< address_width >::result > 
{
public:
  typedef typename PV::dataWidth2Type< data_width >::result data_type;
  typedef typename PV::dataWidth2Type< address_width >::result address_type;
  typedef PVReq< data_type, address_type > request_type; 
  typedef PVResp< data_type > response_type; 
  typedef PV_if< data_type, address_type > interface_type; 
  typedef interface_type * interface_pointer_type ; 
  
protected:
  scml_memory_pv_if() {} 
  virtual ~scml_memory_pv_if() {}
  
private:
  // disable
  scml_memory_pv_if( const  scml_memory_pv_if & ); 
  scml_memory_pv_if & operator= ( const  scml_memory_pv_if & );
};

typedef scml_memory_pv_if< 32, 32 > scml_memory_pv_32_32_if;
typedef scml_memory_pv_if< 32, 64 > scml_memory_pv_32_64_if;
typedef scml_memory_pv_if< 32, 128 > scml_memory_pv_32_128_if;
typedef scml_memory_pv_if< 32, 256 > scml_memory_pv_32_256_if;
typedef scml_memory_pv_if< 32, 512 > scml_memory_pv_32_512_if;

typedef scml_memory_pv_if< 64, 32 > scml_memory_pv_64_32_if;
typedef scml_memory_pv_if< 64, 64 > scml_memory_pv_64_64_if;
typedef scml_memory_pv_if< 64, 128 > scml_memory_pv_64_128_if;
typedef scml_memory_pv_if< 64, 256 > scml_memory_pv_64_256_if;
typedef scml_memory_pv_if< 64, 512 > scml_memory_pv_64_512_if;

// FIXME: Backwards compatibility
typedef scml_memory_pv_32_32_if scml_memory_pv32_if;
typedef scml_memory_pv_32_64_if scml_memory_pv64_if;
typedef scml_memory_pv_32_128_if scml_memory_pv128_if;
typedef scml_memory_pv_32_256_if scml_memory_pv256_if;
typedef scml_memory_pv_32_512_if scml_memory_pv512_if;

#define SCML_FOR_EACH_PV_INTERFACE_TYPE(doit) \
  doit(scml_memory_pv_32_32_if) \
  doit(scml_memory_pv_32_64_if) \
  doit(scml_memory_pv_32_128_if) \
  doit(scml_memory_pv_32_256_if) \
  doit(scml_memory_pv_32_512_if) \
  doit(scml_memory_pv_64_32_if) \
  doit(scml_memory_pv_64_64_if) \
  doit(scml_memory_pv_64_128_if) \
  doit(scml_memory_pv_64_256_if) \
  doit(scml_memory_pv_64_512_if)
  

//FIXME
namespace scml {
  template< typename DT, typename AT> struct Types2If;
#define TYPES2IF(IF) \
  template<> struct Types2If<IF::data_type, IF::address_type> { typedef IF result; };
SCML_FOR_EACH_PV_INTERFACE_TYPE(TYPES2IF)
#undef TYPES2IF

  template<typename IF> struct If2PVInterfaceType;
  template<> struct If2PVInterfaceType<scml_memory_pv_32_32_if> { enum { result = PV_INTERFACE_32_32}; };
  template<> struct If2PVInterfaceType<scml_memory_pv_32_64_if> { enum { result = PV_INTERFACE_32_64}; };
  template<> struct If2PVInterfaceType<scml_memory_pv_32_128_if> { enum { result = PV_INTERFACE_32_128}; };
  template<> struct If2PVInterfaceType<scml_memory_pv_32_256_if> { enum { result = PV_INTERFACE_32_256}; };
  template<> struct If2PVInterfaceType<scml_memory_pv_32_512_if> { enum { result = PV_INTERFACE_32_512}; };
  template<> struct If2PVInterfaceType<scml_memory_pv_64_32_if> { enum { result = PV_INTERFACE_64_32}; };
  template<> struct If2PVInterfaceType<scml_memory_pv_64_64_if> { enum { result = PV_INTERFACE_64_64}; };
  template<> struct If2PVInterfaceType<scml_memory_pv_64_128_if> { enum { result = PV_INTERFACE_64_128}; };
  template<> struct If2PVInterfaceType<scml_memory_pv_64_256_if> { enum { result = PV_INTERFACE_64_256}; };
  template<> struct If2PVInterfaceType<scml_memory_pv_64_512_if> { enum { result = PV_INTERFACE_64_512}; };

  
}

#endif
