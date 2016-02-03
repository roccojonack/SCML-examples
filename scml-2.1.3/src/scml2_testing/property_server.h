/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#pragma once

#include <map>
#include <string>
#include <scmlinc/scml_property_server_if.h>

namespace scml2 { namespace testing {

class property_server : public scml_property_server_if {
  public:
    virtual long long getIntProperty( const std::string& name);
    virtual unsigned long long getUIntProperty( const std::string& name);
    virtual bool getBoolProperty( const std::string& name);
    virtual std::string getStringProperty( const std::string& name);
    virtual double getDoubleProperty( const std::string& name);
    virtual bool hasIntProperty( const std::string& name);
    virtual bool hasUIntProperty( const std::string& name);
    virtual bool hasBoolProperty( const std::string& name);
    virtual bool hasStringProperty( const std::string& name);
    virtual bool hasDoubleProperty( const std::string& name);
    virtual bool isFinal() const;
    void setProperty( const std::string& name, int value);
    void setProperty( const std::string& name, long long value);
    void setProperty( const std::string& name, unsigned long long value);
    void setProperty( const std::string& name, unsigned int value);
    void setProperty( const std::string& name, bool value);
    void setProperty( const std::string& name, const std::string& value);
    void setProperty( const std::string& name, double value);
    void setPropertyUntyped(const std::string name, const std::string& value);

  private:
    std::map<std::string, long long> intProperties;
    std::map<std::string, unsigned long long> unsignedIntProperties;
    std::map<std::string, bool> boolProperties;
    std::map<std::string, double> doubleProperties;
    std::map<std::string, std::string> stringProperties;
};


}}
