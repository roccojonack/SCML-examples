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
 *  Example implementation of a scml_property_server
 *
 *  Property file syntax:
 *    file ::= {line}*
 *    line ::= typeLine | valueLine | commentLine
 *    typeline ::= '[int]' | '[uint]' | '[bool]' | '[string]' | '[double]'
 *    valueLine ::= name ':' value
 *    commentLine ::= '#' string
 *
 *  Where 'name' is the hierarchical name of the property and 'value' is the
 *  value for the property.
 *
 *  Example property file:
 *    [int]
 *    property1 : 0
 *    property2 : 1234
 *    [string]
 *    property3 : This is a string property
 */

#ifndef SCML_SIMPLE_PROPERTY_SERVER
#define SCML_SIMPLE_PROPERTY_SERVER

#include "scml_property_server_if.h"

#include <scml2_logging/stream.h>
#include <string>
#include <map>

class scml_simple_property_server : public scml_property_server_if {
public:
  scml_simple_property_server();
  virtual ~scml_simple_property_server();

  bool load(const std::string& fileName);

  virtual long long getIntProperty(const std::string& name);
  virtual unsigned long long getUIntProperty(const std::string& name);
  virtual bool getBoolProperty(const std::string& name);
  virtual std::string getStringProperty(const std::string& name);
  virtual double getDoubleProperty(const std::string& name);

  virtual bool hasIntProperty( const std::string & name);
  virtual bool hasUIntProperty( const std::string & name);
  virtual bool hasBoolProperty( const std::string & name);
  virtual bool hasStringProperty( const std::string & name);
  virtual bool hasDoubleProperty( const std::string & name);

private: 
  // disable
  scml_simple_property_server(const scml_simple_property_server& );
  scml_simple_property_server & operator= (const scml_simple_property_server& );

private:
  bool updateCurrentPropertyType(const std::string& line);
  bool parseLine(const std::string& line);

  static std::string strip(const std::string& s, const char* chars);

private:
  static scml2::logging::stream mWarning;
  // data members
  std::map<std::string, long long> mName2longLong;
  std::map<std::string, unsigned long long> mName2unsignedLongLong;
  std::map<std::string, bool> mName2bool;
  std::map<std::string, std::string> mName2string;
  std::map<std::string, double> mName2double;

  enum PropertyType { PT_INT = 0, PT_UINT, PT_BOOL, PT_STRING, PT_DOUBLE };
  PropertyType mCurrentPropertyType;
};

#endif
