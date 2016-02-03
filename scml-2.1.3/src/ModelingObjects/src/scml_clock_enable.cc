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
 * Purpose of file : Definition of scml_clock_enable modeling object
 *
 */

#include "scml_clock_enable.h"

scml_clock_enable::scml_clock_enable( const char * name ) :
  sc_signal< bool >( name )
{
}

scml_clock_enable::~scml_clock_enable()
{
}
