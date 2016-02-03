/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scmlinc/scml_inmemory_property_server.h>
#include <iostream>
#include <stdlib.h>

long long scml_inmemory_property_server::getIntProperty( const std::string& name) {
  std::map<std::string, long long>::const_iterator i = intProperties.find(name);
  return i != intProperties.end() ? i->second : 0LL;
}

unsigned long long scml_inmemory_property_server::getUIntProperty( const std::string& name) {
  std::map<std::string, unsigned long long>::const_iterator i = unsignedIntProperties.find(name);
  return i != unsignedIntProperties.end() ? i->second : 0ULL;
}

bool scml_inmemory_property_server::getBoolProperty( const std::string& name) {
  std::map<std::string, bool>::const_iterator i = boolProperties.find(name);
  return i != boolProperties.end() ? i->second : false;
}

std::string scml_inmemory_property_server::getStringProperty( const std::string& name) {
  std::map<std::string, std::string>::const_iterator i = stringProperties.find(name);
  return i != stringProperties.end() ? i->second : "";
}

double scml_inmemory_property_server::getDoubleProperty( const std::string& name) {
  std::map<std::string, double>::const_iterator i = doubleProperties.find(name);
  return i != doubleProperties.end() ? i->second : 0;
}

bool scml_inmemory_property_server::hasIntProperty( const std::string& name) {
  return intProperties.find(name) != intProperties.end();
}

bool scml_inmemory_property_server::hasUIntProperty( const std::string& name) {
  return unsignedIntProperties.find(name) != unsignedIntProperties.end();
}

bool scml_inmemory_property_server::hasBoolProperty( const std::string& name) {
  return boolProperties.find(name) != boolProperties.end();
}

bool scml_inmemory_property_server::hasStringProperty( const std::string& name) {
  return stringProperties.find(name) != stringProperties.end();
}

bool scml_inmemory_property_server::hasDoubleProperty( const std::string& name) {
  return doubleProperties.find(name) != doubleProperties.end();
}


void scml_inmemory_property_server::setProperty( const std::string& name, long long value) {
  intProperties[name] = value;
}

void scml_inmemory_property_server::setProperty( const std::string& name, unsigned long long value) {
  unsignedIntProperties[name] = value;
}

void scml_inmemory_property_server::setProperty( const std::string& name, bool value) {
  boolProperties[name] = value;
}

void scml_inmemory_property_server::setProperty( const std::string& name, const std::string& value) {
  stringProperties[name] = value;
}

void scml_inmemory_property_server::setProperty( const std::string& name, double value) {
  doubleProperties[name] = value;
}
