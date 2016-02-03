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

#ifndef SCML_PROPERTY_SERVER_IF
#define SCML_PROPERTY_SERVER_IF

#include <string>

class scml_property_server_if {
public:
  virtual long long getIntProperty( const std::string & name);
  virtual unsigned long long getUIntProperty( const std::string & name);
  virtual bool getBoolProperty( const std::string & name);
  virtual std::string getStringProperty( const std::string & name);
  virtual double getDoubleProperty( const std::string & name);

  virtual bool hasIntProperty( const std::string & name);
  virtual bool hasUIntProperty( const std::string & name);
  virtual bool hasBoolProperty( const std::string & name);
  virtual bool hasStringProperty( const std::string & name);
  virtual bool hasDoubleProperty( const std::string & name);

  virtual bool isFinal() const;

protected:
  scml_property_server_if();
  virtual ~scml_property_server_if();

private: 
  // disable
  scml_property_server_if( const scml_property_server_if & );
  scml_property_server_if & operator= ( const scml_property_server_if & );
};

#endif
