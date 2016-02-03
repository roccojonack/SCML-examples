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

#ifndef SCML_DIVIDED_CLOCK_H
#define SCML_DIVIDED_CLOCK_H

#include "systemc.h"
#include "scml_clock_b.h"

/************************************************************************
 * 
 */
class scml_divided_clock : public scml_clock {
public:
  explicit scml_divided_clock( const char * name,
			       unsigned int period_multiplier = 1,
			       unsigned int start_multiplier = 0 );  

  scml_divided_clock( const char * name,
		      scml_clock_if & clk_if,
		      unsigned int period_multiplier = 1,
		      unsigned int start_multiplier = 0 );

  scml_divided_clock( const char * name,
		      sc_in< bool > & clk,
		      unsigned int period_multiplier = 1,
		      unsigned int start_multiplier = 0 );  

  virtual ~scml_divided_clock();
  virtual void end_of_elaboration();

  // binding
  void bind( scml_clock_if & );
  void bind( sc_in< bool > & );
  void operator()( scml_clock_if & );
  void operator()( sc_in< bool > & );

  // clock period can be changed in multiples of parent clock
  void set_divider( unsigned int );
  unsigned int get_divider() const;

  // see scml_clock
  virtual void master_changed();
protected:
  virtual void set_period( const sc_time & t );
  
private:
  // data members
  sc_time mOriginalPeriod;
  const unsigned int m_orig_period_multiplier;
  const unsigned int m_orig_start_multiplier;

private:
  // disable
  scml_divided_clock();
  scml_divided_clock( const scml_divided_clock & );
  scml_divided_clock & operator= ( const scml_divided_clock & );
};

#endif
