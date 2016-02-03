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
 * Purpose of file : Header file for Properties
 *
 */

#ifndef CNSC_SCML_PROPERTY_H
#define CNSC_SCML_PROPERTY_H

#include <string>
#include <iostream>
#include <systemc.h>

/************************************************************************
 * scml_property_b non-templatized base-class
 */
class scml_property_b
{
public:
  virtual ~scml_property_b();

  virtual int getIntValue() const;
  virtual unsigned int getUIntValue() const;
  virtual bool getBoolValue() const;
  virtual double getDoubleValue() const;
  virtual ::std::string getStringValue() const;
  
  virtual ::std::string getType() const;

  virtual void setIntValue(int value);
  virtual void setBoolValue(bool value);
  virtual void setDoubleValue(double value);
  virtual void setStringValue(const ::std::string &value);
  virtual void setUIntValue(unsigned int value);
  virtual void setLongLongValue(long long value);
  virtual void setULongLongValue(unsigned long long value);

  ::std::string getName() const;
  
  class WrongTypeException {
  public:
    WrongTypeException(const ::std::string &badType,
                       const ::std::string &goodType);
    ::std::string getGoodType() const;
    ::std::string getBadType() const;
    ::std::string getDescription() const;
  private:
    ::std::string mBadType;
    ::std::string mGoodType;
    
  };

protected:
  explicit scml_property_b(const ::std::string& name);
  
protected:
  ::std::string mName;
  sc_module *mModule;
};


/************************************************************************
 * scml_property_base class
 */

template<typename T>
class scml_property_base : public scml_property_b
{
public:
  typedef T value_type;
  typedef scml_property_base<value_type> this_type;
  typedef this_type* this_pointer_type;
  typedef this_type& this_reference_type;
  typedef scml_property_b::WrongTypeException WrongTypeException;
  
  // T variable behaviour
  this_reference_type operator += ( value_type );
  this_reference_type operator -= ( value_type );
  this_reference_type operator /= ( value_type );
  this_reference_type operator *= ( value_type );
  this_reference_type operator %= ( value_type );
  this_reference_type operator ^= ( value_type );
  this_reference_type operator &= ( value_type );
  this_reference_type operator |= ( value_type );
  this_reference_type operator <<= ( value_type );
  this_reference_type operator >>= ( value_type );

  // decrement & increment
  this_reference_type operator -- ();     // prefix
  value_type operator -- ( int); // postfix
  this_reference_type operator ++ ();     // prefix
  value_type operator ++ ( int); // postfix  
  
  // T behavior
  operator T() const;
  const T& getValue() const;
  T& getValue();
    
protected:
  explicit scml_property_base(const ::std::string& name);
  virtual ~scml_property_base();

protected:
  value_type mValue;
  
  friend class PropertyTest;
};


/************************************************************************
 * scml_property class
 */
 
template<typename T> class scml_property;

/************************************************************************
 * specializations for supported types:
 */

/************************************************************************
 * int
 */

template<>
class scml_property<int> : public scml_property_base<int>
{
public:

  typedef int value_type;
  typedef scml_property<int> this_type;
  typedef this_type& this_reference_type;
  typedef this_type::WrongTypeException WrongTypeException;

  this_reference_type operator=( const scml_property<int>& );
  this_reference_type operator=( value_type );

  explicit scml_property(const ::std::string& name);
  scml_property(const ::std::string& name, value_type default_value);
  virtual ~scml_property();
  
  int getIntValue() const;
  void setIntValue(int value);
  ::std::string getType() const; 
};


/************************************************************************
 * unsigned int
 */

template<>
class scml_property<unsigned int> : public scml_property_base<unsigned int>
{
public:

  typedef unsigned int value_type;
  typedef scml_property<unsigned int> this_type;
  typedef this_type& this_reference_type;
  typedef this_type::WrongTypeException WrongTypeException;

  this_reference_type operator=( const scml_property<unsigned int>& );
  this_reference_type operator=( value_type );

  explicit scml_property(const ::std::string& name);
  scml_property(const ::std::string& name, value_type default_value);  
  virtual ~scml_property();
  
  unsigned int getUIntValue() const;
  void setUIntValue(unsigned int value);
  ::std::string getType() const; 
};

/************************************************************************
 * long long
 */

template<>
class scml_property<long long> : public scml_property_base<long long>
{
public:

  typedef long long value_type;
  typedef scml_property<long long> this_type;
  typedef this_type& this_reference_type;
  typedef this_type::WrongTypeException WrongTypeException;

  this_reference_type operator=( const scml_property<long long>& );
  this_reference_type operator=( value_type );

  explicit scml_property(const ::std::string& name);
  scml_property(const ::std::string& name, value_type default_value);
  virtual ~scml_property();
  
  long long getLongLongValue() const;
  void setLongLongValue(long long value);
  ::std::string getType() const; 
};


/************************************************************************
 * unsigned long long
 */

template<>
class scml_property<unsigned long long> : public scml_property_base<unsigned long long>
{
public:

  typedef unsigned long long value_type;
  typedef scml_property<unsigned long long> this_type;
  typedef this_type& this_reference_type;
  typedef this_type::WrongTypeException WrongTypeException;

  this_reference_type operator=( const scml_property<unsigned long long>& );
  this_reference_type operator=( value_type );

  explicit scml_property(const ::std::string& name);
  scml_property(const ::std::string& name, value_type default_value);  
  virtual ~scml_property();
  
  unsigned long long getULongLongValue() const;
  void setULongLongValue(unsigned long long value);
  ::std::string getType() const; 
};


/************************************************************************
 * bool
 */

template<>
class scml_property<bool> : public scml_property_base<bool>
{
public:

  typedef bool value_type;
  typedef scml_property<bool> this_type;
  typedef this_type& this_reference_type;
  typedef this_type::WrongTypeException WrongTypeException;
  
  this_reference_type operator=( const scml_property<bool>& );
  this_reference_type operator=( value_type );

  explicit scml_property(const ::std::string& name);
  scml_property(const ::std::string& name, value_type default_value);  
  virtual ~scml_property();

  bool getBoolValue() const;
  void setBoolValue(bool value);
  ::std::string getType() const; 
};

/************************************************************************
 * double
 */

template<>
class scml_property<double> : public scml_property_base<double>
{
public:

  typedef double value_type;
  typedef scml_property<double> this_type;
  typedef this_type& this_reference_type;
  typedef this_type::WrongTypeException WrongTypeException; 
  
  this_reference_type operator=( const scml_property<double>& );
  this_reference_type operator=( value_type );

  explicit scml_property(const ::std::string& name);
  scml_property(const ::std::string& name, value_type default_value);
  virtual ~scml_property();

  double getDoubleValue() const;
  void setDoubleValue(double value);
  ::std::string getType() const;
};

/************************************************************************
 * ::std::string
 */

template<>
class scml_property< ::std::string> : public scml_property_base< ::std::string>
{
public:

  typedef ::std::string value_type;
  typedef scml_property< ::std::string> this_type;
  typedef this_type& this_reference_type;
  typedef this_type::WrongTypeException WrongTypeException;
  
  this_reference_type operator=( const scml_property< ::std::string>& );
  this_reference_type operator=( value_type );
  
  explicit scml_property(const ::std::string& name);
  scml_property(const ::std::string& name, value_type default_value);  
  virtual ~scml_property();
  
  ::std::string getStringValue() const;
  void setStringValue(const ::std::string &value);
  ::std::string getType() const;  
};

/************************************************************************
 * ::std::string operators
 */

#define CNSC_STRING_OPERATOR_DECLARATION(otype)\
bool operator otype (const scml_property< ::std::string>& lhs, \
	   	     const scml_property< ::std::string>& rhs);\
bool operator otype (const ::std::string& lhs, \
		     const scml_property< ::std::string>& rhs);\
bool operator otype (const scml_property< ::std::string>& lhs, \
		     const ::std::string& rhs);\

CNSC_STRING_OPERATOR_DECLARATION(==);
CNSC_STRING_OPERATOR_DECLARATION(!=);
CNSC_STRING_OPERATOR_DECLARATION(<);
CNSC_STRING_OPERATOR_DECLARATION(<=);
CNSC_STRING_OPERATOR_DECLARATION(>);
CNSC_STRING_OPERATOR_DECLARATION(>=);

#undef CNSC_STRING_OPERATOR_DECLARATION

::std::ostream& operator<<(::std::ostream& os, 
			   const scml_property< ::std::string>& str);
::std::istream& operator>>(::std::istream& os, 
			   scml_property< ::std::string>& str);
::std::string operator+ (const scml_property< ::std::string>& lhs, 
			 const scml_property< ::std::string>& rhs);
::std::string operator+ (const scml_property< ::std::string>& lhs, 
			 const ::std::string& rhs);
::std::string operator+ (const ::std::string& lhs, 
			 const scml_property< ::std::string>& rhs);

/************************************************************************
 * scml_property_base INLINE IMPLEMENTATIONS
 */

template<typename T>
inline scml_property_base<T>::scml_property_base(const ::std::string& name) 
  : scml_property_b(name)
{
}

template<typename T>
inline scml_property_base<T>::~scml_property_base()
{
}

#define scml_property_ASSIGNMENT_IMPLEMENTATION(otype)\
template<typename T>\
inline typename scml_property_base<T>::this_reference_type \
scml_property_base<T>::operator otype (value_type v)\
{\
  mValue otype v;\
  return *this;\
}\

scml_property_ASSIGNMENT_IMPLEMENTATION(+=);
scml_property_ASSIGNMENT_IMPLEMENTATION(-=);
scml_property_ASSIGNMENT_IMPLEMENTATION(/=);
scml_property_ASSIGNMENT_IMPLEMENTATION(*=);
scml_property_ASSIGNMENT_IMPLEMENTATION(%=);
scml_property_ASSIGNMENT_IMPLEMENTATION(^=);
scml_property_ASSIGNMENT_IMPLEMENTATION(|=);
scml_property_ASSIGNMENT_IMPLEMENTATION(&=);
scml_property_ASSIGNMENT_IMPLEMENTATION(<<=);
scml_property_ASSIGNMENT_IMPLEMENTATION(>>=);

#undef scml_property_ASSIGNMENT_IMPLEMENTATION

// decrement & increment
template<typename T>
inline typename scml_property_base<T>::this_reference_type 
scml_property_base<T>::operator -- ()     // prefix
{
  --mValue;
  return *this;
}

template<typename T>
inline typename scml_property_base<T>::value_type 
scml_property_base<T>::operator -- ( int) // postfix
{
  value_type oldVal = mValue;
  mValue--;
  return oldVal;
}

template<typename T>
inline typename scml_property_base<T>::this_reference_type 
scml_property_base<T>::operator ++ ()     // prefix
{
  ++mValue;
  return *this;
}

template<typename T>
inline typename scml_property_base<T>::value_type 
scml_property_base<T>::operator ++ ( int) // postfix
{
  value_type oldVal = mValue;
  mValue++;
  return oldVal;
}

template<typename T>
inline scml_property_base<T>::operator T() const
{
  return mValue;
}

template<typename T>
inline const T& scml_property_base<T>::getValue() const
{
  return mValue;
}

template<typename T>
inline T& scml_property_base<T>::getValue()
{
  return mValue;
}

#endif //SCML_PROPERTY_H
