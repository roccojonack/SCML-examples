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

#ifndef SCML_CLOCK_ENABLE_H
#define SCML_CLOCK_ENABLE_H

#include "systemc.h"

/************************************************************************
 * 
 */
class scml_clock_enable : public sc_signal< bool > {
public:
  explicit scml_clock_enable( const char * name );
  ~scml_clock_enable();

private:
  // disable
  scml_clock_enable();
  scml_clock_enable( const scml_clock_enable & );
  scml_clock_enable & operator= ( const scml_clock_enable & );
};

#endif
