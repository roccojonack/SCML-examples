/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/property_server.h>
#include <iostream>
#include <stdlib.h>

static bool toLongLong(const std::string& s, long long& v) {
   char* end;
#ifdef _WIN32
   v =  _strtoi64(s.c_str(), &end, 0);
#else
   v = strtoll(s.c_str(), &end, 0);
#endif
   return s != end;
}

static bool toULongLong(const std::string& s, unsigned long long& v) {
   char* end;
#ifdef _WIN32
   v =  _strtoui64(s.c_str(), &end, 0);
#else
   v = strtoull(s.c_str(), &end, 0);
#endif
   return s != end;
}

namespace scml2 { namespace testing {

long long property_server::getIntProperty( const std::string& name) {
  std::map<std::string, long long>::const_iterator i = intProperties.find(name);
  return i != intProperties.end() ? i->second : 0LL;
}

unsigned long long property_server::getUIntProperty( const std::string& name) {
  std::map<std::string, unsigned long long>::const_iterator i = unsignedIntProperties.find(name);
  return i != unsignedIntProperties.end() ? i->second : 0LL;
}

bool property_server::getBoolProperty( const std::string& name) {
  std::map<std::string, bool>::const_iterator i = boolProperties.find(name);
  return i != boolProperties.end() ? i->second : false;
}

std::string property_server::getStringProperty( const std::string& name) {
  std::map<std::string, std::string>::const_iterator i = stringProperties.find(name);
  return i != stringProperties.end() ? i->second : "";
}

double property_server::getDoubleProperty( const std::string& name) {
  std::map<std::string, double>::const_iterator i = doubleProperties.find(name);
  return i != doubleProperties.end() ? i->second : 0LL;
}

bool property_server::hasIntProperty( const std::string& name) {
  return intProperties.find(name) != intProperties.end();
}

bool property_server::hasUIntProperty( const std::string& name) {
  return unsignedIntProperties.find(name) != unsignedIntProperties.end();
}

bool property_server::hasBoolProperty( const std::string& name) {
  return boolProperties.find(name) != boolProperties.end();
}

bool property_server::hasStringProperty( const std::string& name) {
  return stringProperties.find(name) != stringProperties.end();
}

bool property_server::hasDoubleProperty( const std::string& name) {
  return doubleProperties.find(name) != doubleProperties.end();
}

bool property_server::isFinal() const {
  return false;
} 

void property_server::setProperty( const std::string& name, int value) {
  intProperties[name] = value;
}

void property_server::setProperty( const std::string& name, long long value) {
  intProperties[name] = value;
}

void property_server::setProperty( const std::string& name, unsigned long long value) {
  unsignedIntProperties[name] = value;
}

void property_server::setProperty( const std::string& name, unsigned int value) {
  unsignedIntProperties[name] = value;
}

void property_server::setProperty( const std::string& name, bool value) {
  boolProperties[name] = value;
}

void property_server::setProperty( const std::string& name, const std::string& value) {
  stringProperties[name] = value;
}

void property_server::setProperty( const std::string& name, double value) {
  doubleProperties[name] = value;
}

void property_server::setPropertyUntyped(const std::string name, const std::string& value) {
  if (hasIntProperty(name)) {
    long long actualValue;
    if (toLongLong(value, actualValue)) {
      setProperty(name, actualValue);
    }
    else {
      std::cerr << "Unable to parse int: " << value << std::endl;
    }
  }
  else if (hasUIntProperty(name)) {
    unsigned long long actualValue;
    if (toULongLong(value, actualValue)) {
      setProperty(name, actualValue);
    }
    else {
      std::cerr << "Unable to parse unsigned int: " << value << std::endl;
    }
  }
  else if (hasBoolProperty(name)) {
    if (value == "true") {
      setProperty(name, true);
    }
    else if (value == "false") {
      setProperty(name, false);
    }
    else {
      std::cerr << "Unable to parse bool: " << value << std::endl;
    }
  }
  else if (hasStringProperty(name)) {
    setProperty(name, value);
  }
  else if (hasDoubleProperty(name)) {
    char* endptr;
    double actualValue = strtod(value.c_str(), &endptr);
    if (value != endptr) {
      setProperty(name, actualValue);
    }
    else {
      std::cerr << "Unable to parse double: " << value << std::endl;
    }
  }
  else {
    std::cerr << "Warning: Unable to determine the type of parameter " << name << std::endl;
  }
}

}}
