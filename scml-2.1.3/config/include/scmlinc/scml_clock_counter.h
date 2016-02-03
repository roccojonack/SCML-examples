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
 * Purpose of file : Definition of scml_clock_counter modeling object
 *
 */

#ifndef SCML_CLOCK_COUNTER_H
#define SCML_CLOCK_COUNTER_H

#include <scml2_logging/stream.h>
#include <string>
#include "systemc.h"
#include "scml_clock_b.h"

/************************************************************************
 * 
 */
class scml_clock_counter {
public:
  typedef sc_dt::uint64 data_type;
private:
  typedef data_type T;

public:
  // constructor & destructor
  explicit scml_clock_counter( const char * name );
  scml_clock_counter( const char * name, scml_clock_if & ); 
  virtual ~scml_clock_counter();

  // binding
  void bind( scml_clock_if & );
  void operator()( scml_clock_if & );

  // counter manipulation
  data_type get_count() const;
  void set_count( data_type );
 
  // read/write interface
  T read() const;
  void write( const T a );
  
  operator T() const;
  T operator = ( const T );

  // sc_object like functions
  virtual const char * kind() const;
  const char * name() const;

private:
  // disable
  scml_clock_counter();
  scml_clock_counter( const scml_clock_counter & );
  scml_clock_counter & operator= ( const scml_clock_counter & );

private:
  // data members
  mutable scml2::logging::stream mWarning;
  scml_clock_if * mCif;
  data_type mLastWrittenCountValue;
  ::std::string m_name;
};

#endif
