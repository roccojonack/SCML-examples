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
 * Purpose of file : Header file for scml_property_registry
 *
 */

#ifndef SCML_PROPERTY_REGISTRY_H
#define SCML_PROPERTY_REGISTRY_H

#include <string>
#include <iostream>


class scml_property_server_if;
class scml_inmemory_property_server;

class scml_property_registry
{
public:
  static scml_property_registry& inst();
  ~scml_property_registry ();
  
  enum PropertyType {
    GLOBAL,
    CONSTRUCTOR,
    MODULE,
    PORT,
    PROTOCOL,
    PORT_ARRAY
  };
  
  // PropertyAPI
  long long getIntProperty(PropertyType type, const std::string& scHierName, 
  		           const std::string& name);
  unsigned long long getUIntProperty(PropertyType type, 
  				     const std::string& scHierName, 
  		                     const std::string& name);

  bool getBoolProperty(PropertyType type, const std::string& scHierName, 
   		       const std::string& name);
  std::string getStringProperty(PropertyType type, 
  				  const std::string& scHierName, 
  			          const std::string& name);
  double getDoubleProperty(PropertyType type, const std::string& scHierName, 
  			   const std::string& name);

  bool setCustomPropertyServer( scml_property_server_if * );

  void setXMLFile(const std::string& filePath);
  
  // Default is cerr
  void setOutputStream(std::ostream* output);

  enum PropertyCType {
    INTEGER, STRING, BOOL, DOUBLE, UNSIGNED_INTEGER, SIGNED_INTEGER
  };
  
  bool hasProperty(PropertyType type, PropertyCType ctype, 
    		   const std::string& scHierName, const std::string& name);
		   
  std::string getPropertyXmlFilePath() const;


  // Set properties
  void setIntProperty(PropertyType type, const std::string& scHierName, const std::string& name, long long value);
  void setUIntProperty(PropertyType type, const std::string& scHierName, const std::string& name, unsigned long long value);
  void setBoolProperty(PropertyType type, const std::string& scHierName, const std::string& name, bool value);
  void setStringProperty(PropertyType type, const std::string& scHierName, const std::string& name, const std::string& value);
  void setDoubleProperty(PropertyType type, const std::string& scHierName, const std::string& name, double value);

private:	
  std::ostream* mOs;
  std::string mXmlFilePath;
  scml_property_server_if * mCustomPropServer;
  scml_inmemory_property_server* mSetProperties;

private:

  scml_property_registry ();
  // disable assignment operator
  scml_property_registry& operator= (const scml_property_registry&);
  // disable copy constructor
  scml_property_registry(const scml_property_registry&);
};


#endif // SCML_PROPERTY_REGISTRY_H
