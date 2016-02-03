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
 * Purpose of file : Definition of scml_router modeling object
 *
 */

#ifndef SCML_ROUTER_H
#define SCML_ROUTER_H

#include "scmlinc/scml_router_operations.h"

/************************************************************************
 * scml_router defined here
 */

template< typename DT > class scml_router;

/************************************************************************
 * partial template specialisation
 *
 */

#define SCML_ROUTER_PTS_FOR_PODT(ptype)\
\
template< > \
class scml_router< ptype > : public scml_router_operations< ptype > { \
public: \
  typedef ptype value_type; \
  typedef value_type* pointer; \
  typedef const value_type* const_pointer; \
  typedef value_type* iterator; \
  typedef const value_type* const_iterator; \
  typedef value_type& reference; \
  typedef const value_type& const_reference; \
  typedef unsigned long long size_type; \
  typedef ptrdiff_t difference_type; \
 \
  typedef scml_router< value_type > this_type; \
  typedef this_type & this_reference_type; \
 \
  typedef scml_memory_pv32_if::request_type request32_type ; \
  typedef scml_memory_pv32_if::response_type response32_type; \
 \
  scml_router() {} \
  explicit scml_router( const ::std::string & n ); \
  explicit scml_router( const char * n ); \
  explicit scml_router( scml_memsize ); \
  scml_router( const ::std::string & n, scml_memsize s); \
  scml_router( const char * n, scml_memsize s); \
  virtual ~scml_router() {} \
 \
private: \
  /* disabled default implementation */ \
  scml_router( const scml_router & ); \
}; \
 \
inline \
scml_router< ptype >::scml_router( const char * n ) : \
  scml_router_operations< ptype > ( n )\
{} \
 \
inline \
scml_router< ptype >::scml_router( const ::std::string & n ) : \
  scml_router_operations< ptype > ( n.c_str()) \
{} \
 \
inline \
scml_router< ptype >::scml_router( scml_memsize a ) : \
  scml_router_operations< ptype > ( a ) \
{} \
 \
inline \
scml_router< ptype >::scml_router( const char * n, scml_memsize a ) : \
  scml_router_operations< ptype > ( n, a ) \
{} \
 \
inline \
scml_router< ptype >::scml_router( const ::std::string & n, scml_memsize a ) : \
  scml_router_operations< ptype > ( n.c_str(), a ) \
{} \

//SCML_ROUTER_PTS_FOR_PODT(bool);
//SCML_ROUTER_PTS_FOR_PODT(char);
//// SCML_ROUTER_PTS_FOR_PODT(float);
//// SCML_ROUTER_PTS_FOR_PODT(double);
//// SCML_ROUTER_PTS_FOR_PODT(long double);
//
//SCML_ROUTER_PTS_FOR_PODT(signed char);
//SCML_ROUTER_PTS_FOR_PODT(signed short int);
//SCML_ROUTER_PTS_FOR_PODT(signed int);
//SCML_ROUTER_PTS_FOR_PODT(signed long int);
//SCML_ROUTER_PTS_FOR_PODT(signed long long);

SCML_ROUTER_PTS_FOR_PODT(unsigned char);
SCML_ROUTER_PTS_FOR_PODT(unsigned short int);
SCML_ROUTER_PTS_FOR_PODT(unsigned int);
SCML_ROUTER_PTS_FOR_PODT(unsigned long int);
SCML_ROUTER_PTS_FOR_PODT(unsigned long long);

SCML_ROUTER_PTS_FOR_PODT(sc_dt::sc_biguint<128>);
SCML_ROUTER_PTS_FOR_PODT(sc_dt::sc_biguint<256>);
SCML_ROUTER_PTS_FOR_PODT(sc_dt::sc_biguint<512>);

#undef SCML_ROUTER_PTS_FOR_PODT

/************************************************************************
 * Generic Template
 */

// template< typename DT > 
// class scml_router : public scml_router_operations< DT > {
// private:
//   // disable
//   scml_router();
//   virtual ~scml_router();
//   scml_router( const scml_router & );
//   scml_router & operator= ( const scml_router & );
// };

#endif
