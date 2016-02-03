/*****************************************************************************
 *                   Copyright (C) 2010-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include "scml_simple_property_server.h"

#include <scml2_logging/severity.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

#undef STRTOLL
#undef STRTOULL

#ifdef _WIN32
  // Windows
  #define STRTOLL _strtoi64
  #define STRTOULL _strtoui64
#else
  // Linux/Solaris
  #define STRTOLL strtoll
  #define STRTOULL strtoull
#endif

scml2::logging::stream
  scml_simple_property_server::mWarning("scml_simple_property_server",
                                        scml2::logging::severity::warning());

scml_simple_property_server::scml_simple_property_server() :
  mCurrentPropertyType(PT_INT)
{
}

scml_simple_property_server::~scml_simple_property_server()
{
}

bool scml_simple_property_server::load(const std::string& fileName)
{
  std::ifstream file(fileName.c_str());

  if (!file.good()) {
    SCML2_LOG(mWarning) << "Could not open file: '" << fileName << "'" << std::endl;
    return false;
  }

  unsigned int lineNr = 1;
  bool syntaxError = false;
  std::string line;
  while (getline(file, line)) {
    if (!parseLine(line)) {
      SCML2_LOG(mWarning) << "Syntax error in " << fileName << "(" << lineNr
                        << "): '" << line << "'" << std::endl;
      syntaxError = true;
    }
    ++lineNr;
  }

  return !syntaxError;
}

std::string scml_simple_property_server::strip(const std::string& s, const char* chars)
{
  const std::string::size_type first = s.find_first_not_of(chars);
  
  if (first == std::string::npos) {
    return std::string();
  }

  const std::string::size_type last = s.find_last_not_of(chars);
  assert(last != std::string::npos);
  assert(last >= first);
  return s.substr(first, last - first + 1);
}

bool scml_simple_property_server::updateCurrentPropertyType(const std::string& line)
{
  if (line == "[int]") {
    mCurrentPropertyType = PT_INT;
    return true;
  } else if (line == "[uint]") {
    mCurrentPropertyType = PT_UINT;
    return true;
  } else if (line == "[bool]") {
    mCurrentPropertyType = PT_BOOL;
    return true;
  } else if (line == "[string]") {
    mCurrentPropertyType = PT_STRING;
    return true;
  } else if (line == "[double]") {
    mCurrentPropertyType = PT_DOUBLE;
    return true;
  }

  return false;
}

bool scml_simple_property_server::parseLine(const std::string& line)
{
  const std::string stripped = strip(line, " \t");

  if (stripped.empty() || stripped[0] == '#') {
    return true;
  }

  if (updateCurrentPropertyType(stripped)) {
    return true;
  }

  const std::string::size_type i = stripped.find_first_of(":");

  if (i == std::string::npos || i == stripped.size() - 1) {
    return false;
  }

  const std::string name = strip(stripped.substr(0, i), " \t");
  const std::string valueString = strip(stripped.substr(i + 1, stripped.size() - i), " \t");

  if (name.empty() || valueString.empty()) {
    return false;
  }
  
  switch (mCurrentPropertyType) {
  case PT_INT:
    {
      char * endptr = 0;
      const char * s = valueString.c_str();
      long long value = STRTOLL(s, &endptr, 0);
      if (*endptr) {
        return false;
      }
      mName2longLong[name] = value;
      return true;
    } 
  case PT_UINT:
    {
      char * endptr = 0;
      const char * s = valueString.c_str();
      unsigned long long value = STRTOULL(s, &endptr, 0);
      if (*endptr) {
        return false;
      }
      mName2unsignedLongLong[name] = value;
      return true;
    } 
  case PT_BOOL:
    {
      if (valueString == "0" || valueString == "false" || valueString == "FALSE") {
        mName2bool[name] = false;
        return true;
      } else if (valueString == "1" || valueString == "true" || valueString == "TRUE") {
        mName2bool[name] = true;
        return true;
      }
      return false;
    } 
  case PT_STRING:
    mName2string[name] = valueString;
    return true;
  case PT_DOUBLE:
    {
      char * endptr = 0;
      const char * s = valueString.c_str();
      double value = strtod(s, &endptr);
      if (*endptr) {
#ifdef _WIN32
        // strtod on windows is not C99 compliant: it is not possible to parse a 
        // hex number with strtod.
        value = (double)STRTOLL(s, &endptr, 0);
        if (*endptr) {
          return false;
        }
#else
        return false;
#endif
      }
      mName2double[name] = value;
      return true;
    } 
  default:
    assert(false);
    return false;
  };
}


long long
scml_simple_property_server::getIntProperty(const std::string & name) 
{
  const std::map<std::string, long long>::iterator it = mName2longLong.find(name);
  if (it == mName2longLong.end()) {
    SCML2_LOG(mWarning)
      << "'Int' Property '" << name << "' not found, "
      << "using default value." << std::endl;
    return 0;
  }
  return it->second;
}

unsigned long long 
scml_simple_property_server::getUIntProperty(const std::string & name)
{
  const std::map<std::string, unsigned long long>::iterator it =
    mName2unsignedLongLong.find(name);
  if (it == mName2unsignedLongLong.end()) {
    SCML2_LOG(mWarning)
      << "'UInt' Property '" << name << "' not found, "
      << "using default value." << std::endl;
    return 0;
  }
  return it->second;
}

bool 
scml_simple_property_server::getBoolProperty(const std::string & name)
{
  const std::map<std::string, bool>::iterator it = mName2bool.find(name);
  if (it == mName2bool.end()) {
    SCML2_LOG(mWarning)
      << "'Bool' Property '" << name << "' not found, "
      << "using default value." << std::endl;
    return false;
  }
  return it->second;
}

std::string
scml_simple_property_server::getStringProperty(const std::string & name)
{
  const std::map<std::string, std::string>::iterator it = mName2string.find(name);
  if (it == mName2string.end()) {
    SCML2_LOG(mWarning)
      << "'String' Property '" << name << "' not found, "
      << "using default value." << std::endl;
    return std::string();
  }
  return it->second;
}

double 
scml_simple_property_server::getDoubleProperty(const std::string & name)
{
  const std::map<std::string, double>::iterator it = mName2double.find(name);
  if (it == mName2double.end()) {
    SCML2_LOG(mWarning)
      << "'Double' Property '" << name << "' not found, "
      << "using default value." << std::endl;
    return 0.0;
  }
  return it->second;
}

bool
scml_simple_property_server::hasIntProperty( const std::string & name)
{
  return mName2longLong.find(name) != mName2longLong.end();
}

bool
scml_simple_property_server::hasUIntProperty( const std::string & name)
{
  return mName2unsignedLongLong.find(name) != mName2unsignedLongLong.end();
}

bool
scml_simple_property_server::hasBoolProperty( const std::string & name)
{
  return mName2bool.find(name) != mName2bool.end();
}

bool
scml_simple_property_server::hasStringProperty( const std::string & name)
{
  return mName2string.find(name) != mName2string.end();
}

bool
scml_simple_property_server::hasDoubleProperty( const std::string & name)
{
  return mName2double.find(name) != mName2double.end();
}
