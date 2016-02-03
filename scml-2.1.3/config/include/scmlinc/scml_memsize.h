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
 * Purpose of file : Definition of scml_memsize modeling object
 *
 */

#ifndef SCML_MEMSIZE_H
#define SCML_MEMSIZE_H

#include <stddef.h>

class scml_memsize {
public:
  typedef unsigned long long size_type;

  explicit scml_memsize(size_type a) : s( a) {}

  // default OK
  // ~scml_memsize();  
  // scml_memsize( const scml_memsize & );
  // scml_memsize & operator= ( const scml_memsize & );

  operator size_type() const { return s; }

private:
  // disable
  scml_memsize();

private:
  // data member
  size_type s;
};

#endif
