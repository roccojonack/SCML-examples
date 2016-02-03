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
 * Purpose of file : Definition of scml_bitfield modeling object
 *
 */

#ifndef SCML_BITFIELD_H
#define SCML_BITFIELD_H

#include <string>
#include "systemc.h"
#include "scmlinc/scml_bitfield_container_if.h"
#include "scmlinc/scml_memory_user.h"

/************************************************************************
 * macro for registration of read and write like call back 
 */
#define BITFIELD_REGISTER_READ( mem, func ) \
    do { (mem).registerReadCB( this, &SC_CURRENT_USER_MODULE::func, true, 0, #func ); } while(0)

#define BITFIELD_REGISTER_READ_USER( mem, func, id ) \
    do { (mem).registerReadCB( this, &SC_CURRENT_USER_MODULE::func, true, id, #func ); } while(0)

#define BITFIELD_REGISTER_NB_READ( mem, func ) \
    do { (mem).registerReadCB( this, &SC_CURRENT_USER_MODULE::func, false, 0, #func ); } while(0)

#define BITFIELD_REGISTER_NB_READ_USER( mem, func, id ) \
    do { (mem).registerReadCB( this, &SC_CURRENT_USER_MODULE::func, false, id, #func ); } while(0)

#define BITFIELD_REGISTER_WRITE( mem, func ) \
    do { (mem).registerWriteCB( this, &SC_CURRENT_USER_MODULE::func, true, 0, #func ); } while(0)

#define BITFIELD_REGISTER_WRITE_USER( mem, func, id ) \
    do { (mem).registerWriteCB( this, &SC_CURRENT_USER_MODULE::func, true, id, #func ); } while(0)

#define BITFIELD_REGISTER_NB_WRITE( mem, func ) \
    do { (mem).registerWriteCB( this, &SC_CURRENT_USER_MODULE::func, false, 0, #func ); } while(0)

#define BITFIELD_REGISTER_NB_WRITE_USER( mem, func, id ) \
    do { (mem).registerWriteCB( this, &SC_CURRENT_USER_MODULE::func, false, id, #func ); } while(0)

/************************************************************************
 * 
 */
class scml_bitfield : public scml_bitfield_base {
  friend class scml_bitfield_container;
public:
  typedef scml_bitfield_container_if::size_type size_type;
  typedef scml_bitfield_container_if::value_type value_type;
  typedef scml_bitfield this_type;
  typedef this_type * this_pointer_type;
  typedef this_type & this_reference_type;
  typedef scml_memory_user::user_id_data_type user_id_data_type;

  static const unsigned int OPERATIONS_ALLOW_READ  = 1;
  static const unsigned int OPERATIONS_ALLOW_WRITE = 2;

public:
  scml_bitfield( const char * n,
		 scml_bitfield_container_if & c,
		 size_type offset,
		 size_type size );

  virtual ~scml_bitfield();

  // value_type variable behaviour
  this_reference_type operator=( value_type );
  operator value_type() const ;
  value_type get() const ;
  void put( value_type);

  // read & write trigger attached call backs
  value_type read() const;
  void write( value_type);
  
  // data member access
  const char * getName() const { return bitFieldName.c_str(); }
  size_type getOffset() const { return offset; }
  size_type getSize() const { return size; }

  // read and write like call back registration
  template< typename MOD >
  void registerReadCB( MOD * mod, 
		       value_type (MOD::*f) ( void ),
		       bool isBlocking = true,
		       user_id_data_type id = 0,
		       const std::string &cbName="");

  template< typename MOD >
  void registerWriteCB( MOD * mod,
			void (MOD::*f) ( value_type ),
			bool isBlocking = true,
			user_id_data_type id = 0,
			const std::string &cbName="");

  void unregisterReadCB();
  void unregisterWriteCB();

  // arithmetic assignments
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
  this_reference_type operator -- (); // prefix
  value_type operator -- ( int);      // postfix
  this_reference_type operator ++ (); // prefix
  value_type operator ++ ( int);      // postfix

  // allowed operations controls
  unsigned int get_allowed_operations() const;
  void set_allowed_operations(unsigned int);
  void set_read_only();
  void set_write_only();
  bool is_reading_allowed() const;
  bool is_writing_allowed() const;

public:
  // queries
  virtual size_type getBitfieldOffset() const;
  virtual size_type getBitfieldSize() const;
  virtual const char * getBitfieldName() const;
  virtual bool hasReadCallBack() const;
  virtual bool hasWriteCallBack() const;
  virtual bool getReadCallBackName(std::string&) const;
  virtual bool getWriteCallBackName(std::string&) const;

  user_id_data_type getReadUserID() const;
  user_id_data_type getWriteUserID() const;

private:
  // helper functions
  bool hasRegisteredReadCallBack() const ;
  bool hasRegisteredWriteCallBack() const ;

  bool hasReadBehaviourAttached() const;
  bool hasWriteBehaviourAttached() const;
  
private:
  // disable
  scml_bitfield(); 
  scml_bitfield( const scml_bitfield & );
  scml_bitfield & operator= ( const scml_bitfield & );

private:
  // data members
  ::std::string bitFieldName;
  scml_bitfield_container_if & container;
  size_type offset;
  size_type size;

  // read and write like call back functionality
  sc_module * readModule;
  value_type (sc_module::*rcb) ( void );
  bool readIsBlocking;
  user_id_data_type readUid;
  std::string mReadCallBackName;
  std::string mReadCallBackModuleName;

  sc_module * writeModule;
  void (sc_module::*wcb) ( value_type );
  bool writeIsBlocking;  
  user_id_data_type writeUid;
  std::string mWriteCallBackName;
  std::string mWriteCallBackModuleName;

  unsigned int m_AllowedOperationsType;
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */
/************************************************************************
 * read and write like call back registration
 */
template< typename MOD >
inline void scml_bitfield::registerReadCB( MOD * mod,
					   value_type (MOD::*f) ( void ),
					   bool isBlocking,
					   user_id_data_type id,
					   const std::string &cbName)
{
  readModule = mod;
  rcb = static_cast < value_type (sc_module::*) ( void ) > ( f);
  readIsBlocking = isBlocking;
  readUid = id;
  mReadCallBackName = cbName;
  mReadCallBackModuleName = mod->name();
  container.updateReadBlockingProperty( isBlocking );
}

template< typename MOD >
inline void scml_bitfield::registerWriteCB( MOD * mod,
					    void (MOD::*f) ( value_type ),
					    bool isBlocking,
					    user_id_data_type id,
					    const std::string &cbName)
{
  writeModule = mod;
  wcb = static_cast < void (sc_module::*) ( value_type ) > ( f);
  writeIsBlocking = isBlocking;
  writeUid = id;
  mWriteCallBackName = cbName;
  mWriteCallBackModuleName = mod->name();
  container.updateWriteBlockingProperty( isBlocking );
}


/* More inline implementations */

inline scml_bitfield::size_type 
scml_bitfield::getBitfieldOffset() const
{
  return getOffset();
}

inline scml_bitfield::size_type 
scml_bitfield::getBitfieldSize() const
{
  return getSize();  
}

inline const char *
scml_bitfield::getBitfieldName() const
{
  return getName();
}

inline bool
scml_bitfield::hasReadCallBack() const
{
  return hasRegisteredReadCallBack();
}

inline bool
scml_bitfield::hasWriteCallBack() const
{
  return hasRegisteredWriteCallBack();
}

inline bool
scml_bitfield::getReadCallBackName(std::string& name) const
{
  if (hasReadCallBack()) {
    name = mReadCallBackName;
    return true;
  }
  return false;
}

inline bool
scml_bitfield::getWriteCallBackName(std::string& name) const
{
  if (hasWriteCallBack()) {
    name = mWriteCallBackName;
    return true;
  }
  return false;
}

inline bool
scml_bitfield::hasRegisteredReadCallBack() const
{  
  return (( 0 != readModule) && (0 != rcb));
}

inline bool
scml_bitfield::hasRegisteredWriteCallBack() const
{  
  return (( 0 != writeModule) && (0 != wcb));
}

inline bool
scml_bitfield::hasReadBehaviourAttached() const
{
  return hasRegisteredReadCallBack() || !is_reading_allowed();
}

inline bool
scml_bitfield::hasWriteBehaviourAttached() const
{
  return hasRegisteredWriteCallBack() || !is_writing_allowed();
}


/************************************************************************
 * value_type variable behaviour
 */
inline scml_bitfield::this_reference_type
scml_bitfield::operator=( value_type a )
{
  put( a);
  return *this;
}

inline void
scml_bitfield::put( value_type a)
{
  container.setBitfieldValue( a, offset, size); 
}

inline scml_bitfield::operator
scml_bitfield::value_type() const
{
  return get();
}

inline scml_bitfield::value_type
scml_bitfield::get() const
{
  return container.getBitfieldValue( offset, size); 
}


/************************************************************************
 * arithmetic assignments
 */
inline scml_bitfield::this_reference_type
scml_bitfield::operator += ( value_type a)
{
  value_type tmp( *this);
  tmp += a;
  *this = tmp;
  return *this;
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator -= ( value_type a)
{ 
  value_type tmp( *this);
  tmp -= a;
  *this = tmp;
  return *this;
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator /= ( value_type a)
{ 
  value_type tmp( *this);
  tmp /= a;
  *this = tmp;
  return *this;
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator *= ( value_type a)
{ 
  value_type tmp( *this);
  tmp *= a;
  *this = tmp;
  return *this;
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator %= ( value_type a)
{ 
  value_type tmp( *this);
  tmp %= a;
  *this = tmp;
  return *this; 
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator ^= ( value_type a)
{
  value_type tmp( *this);
  tmp ^= a;
  *this = tmp;
  return *this; 
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator &= ( value_type a)
{
  value_type tmp( *this);
  tmp &= a;
  *this = tmp;
  return *this; 
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator |= ( value_type a)
{ 
  value_type tmp( *this);
  tmp |= a;
  *this = tmp;
  return *this;
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator <<= ( value_type a)
{ 
  value_type tmp( *this);
  tmp <<= a;
  *this = tmp;
  return *this;
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator >>= ( value_type a)
{
  value_type tmp( *this);
  tmp >>= a;
  *this = tmp;
  return *this;
}

/************************************************************************
 * decrement & increment
 */
inline scml_bitfield::this_reference_type
scml_bitfield::operator -- ()
{ 
  value_type tmp( *this);
  --tmp;
  *this = tmp;
  return *this; // prefix
}

inline scml_bitfield::value_type
scml_bitfield::operator -- ( int)
{ 
  value_type tmp( *this);
  value_type oldVal( tmp);
  tmp-- ;
  *this = tmp;
  return oldVal; // postfix
}

inline scml_bitfield::this_reference_type
scml_bitfield::operator ++ ()
{
  value_type tmp( *this);
  ++tmp;
  *this = tmp;
  return *this; // prefix
}

inline scml_bitfield::value_type
scml_bitfield::operator ++ ( int)
{ 
  value_type tmp( *this);
  value_type oldVal( tmp);
  tmp++ ;
  *this = tmp;
  return oldVal; // postfix
}
#endif
