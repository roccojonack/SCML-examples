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
 * Purpose of file : Implementation file for Properties
 *
 */

#include "scml_property.h"
#include "scml_property_registry.h"
#include <sstream>

using std::string;
using std::ostream;
using std::istream;

/************************************************************************
 * scml_property_b::WrongTypeException IMPLEMENTATIONS
 */

scml_property_b::WrongTypeException::WrongTypeException(const string &badType,
                                                        const string &goodType)
  : mBadType(badType), mGoodType(goodType)
{
}

string scml_property_b::WrongTypeException::getBadType() const
{
  return mBadType;
}

string scml_property_b::WrongTypeException::getGoodType() const
{
  return mGoodType;
}

string scml_property_b::WrongTypeException::getDescription() const
{
  ::std::ostringstream ss;
  ss << "Incorrect type (" << mBadType << ") for scml_property<"
     << mGoodType << ">";
  return ss.str();
}

/************************************************************************
 * scml_property_b IMPLEMENTATIONS
 */

scml_property_b::scml_property_b(const string &name) :
  mName(name),
  mModule(sc_get_curr_simcontext()->hierarchy_curr())
{
}

scml_property_b::~scml_property_b()
{
}

int scml_property_b::getIntValue() const
{
  throw WrongTypeException("int", getType());
  return 0;
}

bool scml_property_b::getBoolValue() const
{
  throw WrongTypeException("bool", getType());
  return false;
}

double scml_property_b::getDoubleValue() const
{
  throw WrongTypeException("double", getType());
  return 0.0;
}

string scml_property_b::getStringValue() const
{
  throw WrongTypeException("string", getType());
  return "";
}

unsigned int scml_property_b::getUIntValue() const
{
  throw WrongTypeException("unsigned int", getType());
  return 0;
}

void scml_property_b::setIntValue(int)
{
  throw WrongTypeException("int", getType());
}

void scml_property_b::setBoolValue(bool)
{
  throw WrongTypeException("bool", getType());
}

void scml_property_b::setDoubleValue(double)
{
  throw WrongTypeException("double", getType());
}

void scml_property_b::setStringValue(const ::std::string&)
{
  throw WrongTypeException("string", getType());
}

void scml_property_b::setUIntValue(unsigned int)
{
  throw WrongTypeException("unsigned int", getType());
}

void scml_property_b::setLongLongValue(long long)
{
  throw WrongTypeException("long long", getType());
}

void scml_property_b::setULongLongValue(unsigned long long)
{
  throw WrongTypeException("unsigned long long", getType());
}


::std::string scml_property_b::getType() const
{
  return "UNKNOWN";
}

::std::string scml_property_b::getName() const
{
  return mName;
}


/************************************************************************
 * scml_property<int> IMPLEMENTATIONS
 */

scml_property<int>::scml_property(const string& name) 
  : scml_property_base<int>(name)
{
  if (mModule) {
    mValue = scml_property_registry::inst().getIntProperty(
    	scml_property_registry::MODULE, mModule->name(), mName);
  }
}

scml_property<int>::scml_property(const string& name, int default_value) 
  : scml_property_base<int>(name)
{
  mValue = default_value;
  if (mModule) {
    if (scml_property_registry::inst().hasProperty(
    		scml_property_registry::MODULE, 
		scml_property_registry::SIGNED_INTEGER, 
		mModule->name(), mName)) {
      mValue = scml_property_registry::inst().getIntProperty(
    	  scml_property_registry::MODULE, mModule->name(), mName);
    }
  }
}

int scml_property<int>::getIntValue() const
{
  return mValue;
}

void scml_property<int>::setIntValue(int value)
{
  mValue = value;
}

string scml_property<int>::getType() const
{
  return "int";
}

/************************************************************************
 * scml_property<unsigned int> IMPLEMENTATIONS
 */

scml_property<unsigned int>::scml_property(const string& name) 
  : scml_property_base<unsigned int>(name)
{
  if (mModule) {
    mValue = scml_property_registry::inst().getUIntProperty(
    	scml_property_registry::MODULE, mModule->name(), mName);
  }
}

scml_property<unsigned int>::scml_property(const string& name, 
							 unsigned int default_value) 
  : scml_property_base<unsigned int>(name)
{
  mValue = default_value;
  if (mModule) {
    if (scml_property_registry::inst().hasProperty(
    		scml_property_registry::MODULE, 
		scml_property_registry::UNSIGNED_INTEGER, 
		mModule->name(), mName)) {
      mValue = scml_property_registry::inst().getUIntProperty(
    	  scml_property_registry::MODULE, mModule->name(), mName);
    }
  }
}

unsigned int scml_property<unsigned int>::getUIntValue() const
{
  return mValue;
}

void scml_property<unsigned int>::setUIntValue(unsigned int value)
{
  mValue = value;
}

string scml_property<unsigned int>::getType() const
{
  return "unsigned int";
}

/************************************************************************
 * scml_property<long long> IMPLEMENTATIONS
 */

scml_property<long long>::scml_property(const string& name) 
  : scml_property_base<long long>(name)
{
  if (mModule) {
    mValue = scml_property_registry::inst().getIntProperty(
    	scml_property_registry::MODULE, mModule->name(), mName);
  }
}

scml_property<long long>::scml_property(const string& name, long long default_value) 
  : scml_property_base<long long>(name)
{
  mValue = default_value;
  if (mModule) {
    if (scml_property_registry::inst().hasProperty(
    		scml_property_registry::MODULE, 
		scml_property_registry::SIGNED_INTEGER, 
		mModule->name(), mName)) {
      mValue = scml_property_registry::inst().getIntProperty(
    	  scml_property_registry::MODULE, mModule->name(), mName);
    }
  }
}

long long scml_property<long long>::getLongLongValue() const
{
  return mValue;
}

void scml_property<long long>::setLongLongValue(long long value)
{
  mValue = value;
}

string scml_property<long long>::getType() const
{
  return "long long";
}

/************************************************************************
 * scml_property<unsigned long long> IMPLEMENTATIONS
 */

scml_property<unsigned long long>::scml_property(const string& name) 
  : scml_property_base<unsigned long long>(name)
{
  if (mModule) {
    mValue = scml_property_registry::inst().getUIntProperty(
    	scml_property_registry::MODULE, mModule->name(), mName);
  }
}

scml_property<unsigned long long>::scml_property(const string& name, 
							 unsigned long long default_value) 
  : scml_property_base<unsigned long long>(name)
{
  mValue = default_value;
  if (mModule) {
    if (scml_property_registry::inst().hasProperty(
    		scml_property_registry::MODULE, 
		scml_property_registry::UNSIGNED_INTEGER, 
		mModule->name(), mName)) {
      mValue = scml_property_registry::inst().getUIntProperty(
    	  scml_property_registry::MODULE, mModule->name(), mName);
    }
  }
}

unsigned long long scml_property<unsigned long long>::getULongLongValue() const
{
  return mValue;
}

void scml_property<unsigned long long>::setULongLongValue(unsigned long long value)
{
  mValue = value;
}

string scml_property<unsigned long long>::getType() const
{
  return "unsigned long long";
}

/************************************************************************
 * scml_property<bool> IMPLEMENTATIONS
 */

scml_property<bool>::scml_property(const string& name) 
  : scml_property_base<bool>(name)
{
  if (mModule) {
    mValue = scml_property_registry::inst().getBoolProperty(
    	scml_property_registry::MODULE, mModule->name(), mName);
  }
}

scml_property<bool>::scml_property(const string& name, bool default_value) 
  : scml_property_base<bool>(name)
{
  mValue = default_value;
  if (mModule) {
    if (scml_property_registry::inst().hasProperty(
    		scml_property_registry::MODULE, 
		scml_property_registry::BOOL, 
		mModule->name(), mName)) {
      mValue = scml_property_registry::inst().getBoolProperty(
    	  scml_property_registry::MODULE, mModule->name(), mName);
    }
  }
}

bool scml_property<bool>::getBoolValue() const
{
  return mValue;
}

void scml_property<bool>::setBoolValue(bool value)
{
  mValue = value;
}

string scml_property<bool>::getType() const
{
  return "bool";
}

/************************************************************************
 * scml_property<string> IMPLEMENTATIONS
 */

scml_property<string>::scml_property(const string& name) 
  : scml_property_base<string>(name)
{
  if (mModule) {
    mValue = scml_property_registry::inst().getStringProperty(
    	scml_property_registry::MODULE, mModule->name(), mName);
  }
}

scml_property<string>::scml_property(const string& name, string default_value) 
  : scml_property_base<string>(name)
{
  mValue = default_value;
  if (mModule) {
    if (scml_property_registry::inst().hasProperty(
    		scml_property_registry::MODULE, 
		scml_property_registry::STRING, 
		mModule->name(), mName)) {
      mValue = scml_property_registry::inst().getStringProperty(
    	  scml_property_registry::MODULE, mModule->name(), mName);
    }
  }
}

string scml_property<string>::getStringValue() const
{
  return mValue;
}

void scml_property<string>::setStringValue(const string &value)

{
  mValue = value;
}

string scml_property<string>::getType() const
{
  return "string";
}

/************************************************************************
 * scml_property<double> IMPLEMENTATIONS
 */

scml_property<double>::scml_property(const string& name) 
  : scml_property_base<double>(name)
{
  if (mModule) {
    mValue = scml_property_registry::inst().getDoubleProperty(
    	scml_property_registry::MODULE, mModule->name(), mName);
  }
}

scml_property<double>::scml_property(const string& name, double default_value) 
  : scml_property_base<double>(name)
{
  mValue = default_value;
  if (mModule) {
    if (scml_property_registry::inst().hasProperty(
    		scml_property_registry::MODULE, 
		scml_property_registry::DOUBLE, 
		mModule->name(), mName)) {
      mValue = scml_property_registry::inst().getDoubleProperty(
    	  scml_property_registry::MODULE, mModule->name(), mName);
    }
  }
}

double scml_property<double>::getDoubleValue() const
{
  return mValue;
}

void scml_property<double>::setDoubleValue(double value)
{
  mValue = value;
}

string scml_property<double>::getType() const
{
  return "double";
}

/************************************************************************
 * ::std::string operators IMPLEMENTATION
 */


#define CNSC_STRING_OPERATOR_IMPLEMENTATIONS(otype)\
bool operator otype (const scml_property<string>& lhs, \
		     const scml_property<string>& rhs)\
{\
  return lhs.getValue() otype rhs.getValue();\
}\
\
bool operator otype (const string& lhs, const scml_property<string>& rhs)\
{\
  return lhs otype rhs.getValue();\
}\
\
bool operator otype (const scml_property<string>& lhs, const string& rhs)\
{\
  return lhs.getValue() otype rhs;\
}\

CNSC_STRING_OPERATOR_IMPLEMENTATIONS(==);
CNSC_STRING_OPERATOR_IMPLEMENTATIONS(!=);
CNSC_STRING_OPERATOR_IMPLEMENTATIONS(<);
CNSC_STRING_OPERATOR_IMPLEMENTATIONS(<=);
CNSC_STRING_OPERATOR_IMPLEMENTATIONS(>);
CNSC_STRING_OPERATOR_IMPLEMENTATIONS(>=);

#undef CNSC_STRING_OPERATOR_IMPLEMENTATIONS

ostream& operator<<(ostream& os, const scml_property<string>& str)
{
  os << str.getValue();
  return os;
}

istream& operator>>(istream& is, scml_property<string>& str)
{
  is >> str.getValue();
  return is;
}

string operator+ (const scml_property<string>& lhs, const scml_property<string>& rhs)
{
  return lhs.getValue() + rhs.getValue();
}

string operator+ (const scml_property<string>& lhs, const string& rhs)
{
  return lhs.getValue() + rhs;
}

string operator+ (const string& lhs, const scml_property<string>& rhs)
{
  return lhs + rhs.getValue();
}

/************************************************************************
 * scml_property IMPLEMENTATIONS
*/
 
#define SCML_PROPERTY_IMPLEMENTATIONS(ptype)\
\
scml_property< ptype >::~scml_property()\
{\
}\
\
scml_property< ptype >::this_reference_type \
scml_property< ptype >::operator=( const scml_property< ptype >& v)\
{\
  mValue = v.mValue;\
  return *this;\
}\
\
scml_property< ptype >::this_reference_type \
scml_property< ptype >::operator=( scml_property< ptype >::value_type v)\
{\
  mValue = v;\
  return *this;\
}\

SCML_PROPERTY_IMPLEMENTATIONS(int);
SCML_PROPERTY_IMPLEMENTATIONS(unsigned int);
SCML_PROPERTY_IMPLEMENTATIONS(long long);
SCML_PROPERTY_IMPLEMENTATIONS(unsigned long long);
SCML_PROPERTY_IMPLEMENTATIONS(double);
SCML_PROPERTY_IMPLEMENTATIONS(bool);
SCML_PROPERTY_IMPLEMENTATIONS(string);

#undef SCML_PROPERTY_IMPLEMENTATIONS

