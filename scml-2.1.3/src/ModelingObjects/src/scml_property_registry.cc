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
 * Purpose of file : Implementation file for scml_property_registry
 *
 */

#include "scml_property_registry.h"
#include "scml_property_server_if.h"
#include "scmlinc/scml_inmemory_property_server.h"

#include <sys/stat.h>
#include <cassert>


using std::string;
using std::cerr;
using std::endl;

static const char* const TAG_PARAMETERS    	      = "parameters";
static const char* const TAG_PARAMETER    	      = "parameter";
static const char* const TAG_CONSTRUCTOR_ARGUMENTS    = "constructor_arguments";
static const char* const TAG_PROTOCOL_PARAMETERS      = "protocol_parameters";
static const char* const TAG_MODULES                  = "modules";
static const char* const TAG_MODULE                   = "module";
static const char* const TAG_PORTS                    = "ports";
static const char* const TAG_PORT                     = "port";
static const char* const TAG_NAME                     = "name";
static const char* const TAG_VALUE                    = "value";

static const char* const TAG_PORT_ARRAYS              = "port_arrays";
static const char* const TAG_PORT_ARRAY               = "port_array";

scml_property_registry& scml_property_registry::inst() 
{
  static scml_property_registry instance;
  return instance;
}

scml_property_registry::scml_property_registry() : 
  mOs( &cerr), 
  mCustomPropServer( 0)
{
  mSetProperties = new scml_inmemory_property_server();
}

scml_property_registry::~scml_property_registry()
{
  delete mSetProperties;
}

bool scml_property_registry::setCustomPropertyServer( scml_property_server_if * p )
{
  mCustomPropServer = p;
  return (0 != mCustomPropServer);
}


long long scml_property_registry::getIntProperty(PropertyType type, 
				        	 const string& moduleName, 
  		   		        	 const string& name)
{
  const string completeName( moduleName + '.' + name);
  if (mSetProperties->hasIntProperty(completeName)) {
    return mSetProperties->getIntProperty(completeName);
  }
  if( 0 != mCustomPropServer) {
    if (mCustomPropServer->hasIntProperty(completeName) || mCustomPropServer->isFinal()) {
      return mCustomPropServer->getIntProperty( completeName);
    }
  } 
}
		   
unsigned long long scml_property_registry::getUIntProperty(PropertyType type, 
				        	    const string& moduleName, 
  		   		        	    const string& name)
{
  const string completeName( moduleName + '.' + name);
  if (mSetProperties->hasUIntProperty(completeName)) {
    return mSetProperties->getUIntProperty(completeName);
  }
  if( 0 != mCustomPropServer) {
    if (mCustomPropServer->hasUIntProperty(completeName) || mCustomPropServer->isFinal()) {
      return mCustomPropServer->getUIntProperty( completeName);
    }
  }
}

bool scml_property_registry::getBoolProperty(PropertyType type, 
					     const string& moduleName, 
   		     			     const string& name)
{
  const string completeName( moduleName + '.' + name);
  if (mSetProperties->hasBoolProperty(completeName)) {
    return mSetProperties->getBoolProperty(completeName);
  }
  if( 0 != mCustomPropServer) {
    if (mCustomPropServer->hasBoolProperty(completeName) || mCustomPropServer->isFinal()) {
      return mCustomPropServer->getBoolProperty( completeName);
    }
  } 
}
				       
string scml_property_registry::getStringProperty(PropertyType type, 
						 const string& moduleName, 
  			        		 const string& name)
{
  const string completeName( moduleName + '.' + name);
  if (mSetProperties->hasStringProperty(completeName)) {
    return mSetProperties->getStringProperty(completeName);
  }
  if( 0 != mCustomPropServer) {
    if (mCustomPropServer->hasStringProperty(completeName) || mCustomPropServer->isFinal()) {
      return mCustomPropServer->getStringProperty( completeName);
    }
  }
}
					   
double scml_property_registry::getDoubleProperty(PropertyType type, 
						 const string& moduleName, 
  			 			 const string& name)
{
  const string completeName( moduleName + '.' + name);
  if (mSetProperties->hasDoubleProperty(completeName)) {
    return mSetProperties->getDoubleProperty(completeName);
  }
  if( 0 != mCustomPropServer) {
    if (mCustomPropServer->hasDoubleProperty(completeName) || mCustomPropServer->isFinal()) {
      return mCustomPropServer->getDoubleProperty( completeName);
    }
  }
}

bool scml_property_registry::hasProperty(PropertyType type, 
					 PropertyCType ctype, 
    		 			 const std::string& scHierName, 
					 const std::string& name)
{
  const string completeName( scHierName + '.' + name);
  if( 0 != mCustomPropServer) {
    switch (ctype) {
      case SIGNED_INTEGER:
        if (mSetProperties->hasIntProperty(completeName)) {
          return true;
        }
        if (mCustomPropServer->hasIntProperty(completeName)) {
          return true;
        }
        break;
      case UNSIGNED_INTEGER:
        if (mSetProperties->hasUIntProperty(completeName)) {
          return true;
        }
        if (mCustomPropServer->hasUIntProperty(completeName)) {
          return true;
        }
        break;
      case INTEGER:
        if (mSetProperties->hasIntProperty(completeName) || mSetProperties->hasUIntProperty(completeName)) {
          return true;
        }
        if (mCustomPropServer->hasIntProperty(completeName) || mCustomPropServer->hasUIntProperty(completeName)) {
          return true;
        }
        break;
      case STRING:
        if (mSetProperties->hasStringProperty(completeName)) {
          return true;
        }
        if (mCustomPropServer->hasStringProperty(completeName)) {
          return true;
        }
        break;
      case BOOL:
        if (mSetProperties->hasBoolProperty(completeName)) {
          return true;
        }
        if (mCustomPropServer->hasBoolProperty(completeName)) {
          return true;
        }
        break;
      case DOUBLE:
        if (mSetProperties->hasDoubleProperty(completeName)) {
          return true;
        }
        if (mCustomPropServer->hasDoubleProperty(completeName)) {
          return true;
        }
        break;
      default:
        assert(0);
    }
    if (mCustomPropServer->isFinal()) {
      return false;
    }
  }
  return false;
}

// transform myMod.subMod/a to myMod/subMod.a
static bool shiftDot (string& module_name, string& param_name) 
{
   if (module_name.find(".") != string::npos) {
     string afterDot(module_name, module_name.rfind(".") + 1, string::npos);
     param_name = afterDot + "." + param_name;
     module_name.erase(module_name.rfind("."), string::npos);
     return true;
   }
   return false;
}


void scml_property_registry::setOutputStream(::std::ostream* output)
{
  mOs = output;
}

std::string scml_property_registry::getPropertyXmlFilePath() const
{
  return mXmlFilePath;
}  

static bool exists(const std::string& filename)
{
  struct stat st; 
  return (stat(filename.c_str(), &st) == 0) ? true : false;
}

void scml_property_registry::setXMLFile(const string& fileName)
{
}

void scml_property_registry::setIntProperty(PropertyType /* type */, const std::string& scHierName, const std::string& name, long long value) {
  mSetProperties->setProperty(std::string( scHierName + '.' + name), value);
}

void scml_property_registry::setUIntProperty(PropertyType /* type */, const std::string& scHierName, const std::string& name, unsigned long long value) {
  mSetProperties->setProperty(std::string( scHierName + '.' + name), value);
}

void scml_property_registry::setBoolProperty(PropertyType /* type */, const std::string& scHierName, const std::string& name, bool value) {
  mSetProperties->setProperty(std::string( scHierName + '.' + name), value);
}

void scml_property_registry::setStringProperty(PropertyType /* type */, const std::string& scHierName, const std::string& name, const std::string& value) {
  mSetProperties->setProperty(std::string( scHierName + '.' + name), value);
}

void scml_property_registry::setDoubleProperty(PropertyType /* type */, const std::string& scHierName, const std::string& name, double value) {
  mSetProperties->setProperty(std::string( scHierName + '.' + name), value);
}
