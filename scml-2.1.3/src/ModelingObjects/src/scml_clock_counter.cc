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
 * Purpose of file : Implementation of scml_clock_counter modeling object
 *
 */

#include "scml_clock_counter.h"
#include <scml2_logging/severity.h>
#include <iostream>

/************************************************************************
 * constructor & destructor
 */
scml_clock_counter::scml_clock_counter( const char * name, scml_clock_if & c ) :
  mWarning(name, scml2::logging::severity::warning()),
  mCif( &c),
  mLastWrittenCountValue( 0),
  m_name( name )
{
} 

scml_clock_counter::scml_clock_counter( const char * name ) :
  mWarning(name, scml2::logging::severity::warning()),
  mCif( 0),
  mLastWrittenCountValue( 0),
  m_name( name )
{
}

scml_clock_counter::~scml_clock_counter()
{
}

/************************************************************************
 * binding
 */

void scml_clock_counter::bind( scml_clock_if & i)
{
  mCif = &i;
}

void scml_clock_counter::operator()( scml_clock_if & i)
{
  bind( i);
}

/************************************************************************
 * counter manipulation
 */
scml_clock_counter::data_type
scml_clock_counter::get_count() const
{
  if( NULL == mCif) {
    SCML2_LOG(mWarning) << "scml_clock_counter " << name() 
                      << " not bound" << ::std::endl;
    return 0;
  }
  return (mCif->get_clock_count() - mLastWrittenCountValue); 
}

void scml_clock_counter::set_count( data_type v )
{
  mLastWrittenCountValue = mCif->get_clock_count() - v;
} 

/************************************************************************
 * see sc_object
 */

const char * scml_clock_counter::kind() const
{ 
  return "scml_clock_counter"; 
}

const char * scml_clock_counter::name() const
{
  return m_name.c_str();
}

/************************************************************************
 * read write interface
 */

scml_clock_counter::T
scml_clock_counter::read() const
{ 
  return get_count();
}

void scml_clock_counter::write( const T a )
{ 
  set_count( a);
}
  
scml_clock_counter::operator scml_clock_counter::T() const
{ 
  return get_count();
}

scml_clock_counter::T scml_clock_counter::operator = ( const T a )
{ 
  write( a );
  return a; 
}
