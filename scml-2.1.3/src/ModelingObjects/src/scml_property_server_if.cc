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
 * Purpose of file : 
 *
 */

#include "scml_property_server_if.h"

scml_property_server_if::scml_property_server_if()
{
}

scml_property_server_if::~scml_property_server_if()
{
}

long long
scml_property_server_if::getIntProperty( const std::string & ) 
{
  long long result( 0);  
  return result;
}

unsigned long long 
scml_property_server_if::getUIntProperty( const std::string & )
{
  unsigned long long result( 0);
  return result;
}

bool 
scml_property_server_if::getBoolProperty( const std::string & )
{
  bool result(  false);
  return result;
}

std::string 
scml_property_server_if::getStringProperty( const std::string & )
{
  std::string result( ""); 
  return result;
}

double 
scml_property_server_if::getDoubleProperty( const std::string & )
{
  double result( 0.0);
  return result;
}

bool
scml_property_server_if::hasIntProperty( const std::string & /*name*/)
{
  return true;
}

bool
scml_property_server_if::hasUIntProperty( const std::string & /*name*/)
{
  return true;
}

bool
scml_property_server_if::hasBoolProperty( const std::string & /*name*/)
{
  return true;
}

bool
scml_property_server_if::hasStringProperty( const std::string & /*name*/)
{
  return true;
}

bool
scml_property_server_if::hasDoubleProperty( const std::string & /*name*/)
{
  return true;
}

bool
scml_property_server_if::isFinal() const {
  return true;
}
