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

#include <string>
#include <scml2_testing/property_server.h>

namespace scml2 { namespace testing {

template <typename T>
class property_proxy {
  public:
    property_proxy(const std::string& name, property_server* propertyServer) : name(name), propertyServer(propertyServer), haveBufferedValue(false), initialized(false) {
    }

    void initialize(const std::string& modelName, const std::string& mirrorModelName) {
      assert(!initialized);
      this->modelName = modelName;
      this->mirrorModelName = mirrorModelName;
      initialized = true;
      if (haveBufferedValue) {
        set_value(bufferedValue);
      }
      else {
        set_value(T());
      }
    }

    property_proxy& operator=(const T& value) {
      if (initialized) {
        set_value(value);
      }
      else {
        bufferedValue = value;
        haveBufferedValue = true;
      }
      return *this;
    }

    operator T() const {
      if (initialized) {
        return get_value(modelName + "." + name);
      }
      else {
        return bufferedValue;
      }
    }


  private:
    T get_value(const std::string& name) const;

    void set_value(const T& value) {
      propertyServer->setProperty(modelName + "." + name, value);
      propertyServer->setProperty(mirrorModelName + "." + name, value);
    }

  private:
    std::string name;
    std::string modelName;
    std::string mirrorModelName;
    property_server* propertyServer;
    T bufferedValue;
    bool haveBufferedValue;
    bool initialized;
};

template<> inline
unsigned int property_proxy<unsigned int>::get_value(const std::string& name) const {
  return (unsigned int) propertyServer->getUIntProperty(name);
}

template<> inline
unsigned long long property_proxy<unsigned long long>::get_value(const std::string& name) const {
  return propertyServer->getUIntProperty(name);
}

template<> inline
int property_proxy<int>::get_value(const std::string& name) const {
  return (int) propertyServer->getIntProperty(name);
}

template<> inline
long long property_proxy<long long>::get_value(const std::string& name) const {
  return propertyServer->getIntProperty(name);
}

template<> inline
bool property_proxy<bool>::get_value(const std::string& name) const {
  return propertyServer->getBoolProperty(name);
}

template<> inline
double property_proxy<double>::get_value(const std::string& name) const {
  return propertyServer->getDoubleProperty(name);
}

template<> inline
std::string property_proxy<std::string>::get_value(const std::string& name) const {
  return propertyServer->getStringProperty(name);
}

}}
