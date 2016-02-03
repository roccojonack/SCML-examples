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

#include "scml_divided_clock.h"

/************************************************************************
 * constructor & destructor
 */

scml_divided_clock::scml_divided_clock( const char * name,
					unsigned int period_multiplier,
					unsigned int start_multiplier ) :
  scml_clock( name ),
  m_orig_period_multiplier( period_multiplier),
  m_orig_start_multiplier( start_multiplier)
{
}

scml_divided_clock::scml_divided_clock( const char * name,
					scml_clock_if & clk_if,
					unsigned int period_multiplier,
					unsigned int start_multiplier ) :
  scml_clock( name, clk_if, period_multiplier, start_multiplier ),
  m_orig_period_multiplier( period_multiplier),
  m_orig_start_multiplier( start_multiplier)
{
}

scml_divided_clock::scml_divided_clock( const char * name,
					sc_in< bool > & clk,
					unsigned int period_multiplier,
					unsigned int start_multiplier ) :
  scml_clock( name, clk, period_multiplier, start_multiplier ),
  m_orig_period_multiplier( period_multiplier),
  m_orig_start_multiplier( start_multiplier)
{
}

scml_divided_clock::~scml_divided_clock()
{
}

/************************************************************************
 * binding
 */

void scml_divided_clock::bind( scml_clock_if & i)
{
  set_master( i, m_orig_period_multiplier, m_orig_start_multiplier);
}

void scml_divided_clock::bind( sc_in< bool> & s)
{
  set_master( s, m_orig_period_multiplier, m_orig_start_multiplier);
}

void scml_divided_clock::operator()( scml_clock_if & i)
{
  bind( i);
}

void scml_divided_clock::operator()( sc_in< bool> & s)
{
  bind( s);
}

/************************************************************************
 * at end of elaboration => clock tree constructed
 */
void scml_divided_clock::end_of_elaboration()
{
  scml_clock::end_of_elaboration();
  mOriginalPeriod = scml_clock::get_period();
}

/************************************************************************
 * constructor & destructor
 */
void scml_divided_clock::set_divider( unsigned int a )
{
  const sc_time newPeriod( a * mOriginalPeriod);
  set_period( newPeriod);
} 

unsigned int scml_divided_clock::get_divider() const
{
  return( get_period().value() / mOriginalPeriod.value());
}

/************************************************************************
 * see scml_clock
 * restricted access
 */
void scml_divided_clock::set_period( const sc_time & t)
{
  scml_clock::set_period( t);
}

void scml_divided_clock::master_changed()
{
  const unsigned int currentDivider( get_divider());
  mOriginalPeriod = m_master_clock->get_period();
  const sc_time newPeriod( currentDivider * mOriginalPeriod);
  set_period( newPeriod);  
}
