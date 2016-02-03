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
 * Purpose of file : Definition of scml_memory_base modeling object
 *
 */

#ifndef SCML_MEMORY_BASE_H
#define SCML_MEMORY_BASE_H

#include <string>
#include <vector>
#include <set>
#include "systemc.h"
#include "scmlinc/scml_bitfield_base.h"
#include "scmlinc/scml_types.h"
#include "scmlinc/scml_callback_observers.h"
#include <scml2_logging/stream.h>

class scml_bitfield_base;
class scml_callback_observer;

/************************************************************************
 * Abstract base class for scml_memory
 */
class scml_memory_base : public sc_object {
public:
  typedef scml_memory_base this_type;
  typedef scml_memory_base * this_pointer_type;
  typedef scml_memory_base & this_reference_type;

  typedef signed char      int8;
  typedef signed short     int16;
  typedef signed int       int32;
  typedef signed long long int64;

  typedef unsigned char      uint8;
  typedef unsigned short     uint16;
  typedef unsigned int       uint32;
  typedef unsigned long long uint64;

  typedef unsigned long long size_type;


  typedef scml::PVInterfaceType PVInterfaceType;

  enum TypeID { MEM_TYPE_UNKNOWN,
                MEM_TYPE_BOOL1,
                MEM_TYPE_UINT8,
                MEM_TYPE_UINT16,
                MEM_TYPE_UINT32,
                MEM_TYPE_UINT64,
                MEM_TYPE_BIGUINT,
                MEM_TYPE_INT8,
                MEM_TYPE_INT16,
                MEM_TYPE_INT32,
                MEM_TYPE_INT64,
                MEM_TYPE_BIGINT,
                MEM_TYPE_FLOAT32,
                MEM_TYPE_FLOAT64,
                MEM_TYPE_BYTESTREAM };

  enum ErrorCode { noError = 0,
                   errorInvalidType,
                   errorInvalidIndex };

  enum CallBackType { CB_TYPE_NONE,
                      CB_TYPE_TRANSPORT,
                      CB_TYPE_READ,
                      CB_TYPE_WRITE,
                      CB_TYPE_READWRITE };

  static const unsigned int OPERATIONS_ALLOW_READ  = 1;
  static const unsigned int OPERATIONS_ALLOW_WRITE = 2;
  static const unsigned int OPERATIONS_ERROR_DISALLOWED_READ  = 4;
  static const unsigned int OPERATIONS_ERROR_DISALLOWED_WRITE = 8;

  // general queries
  const char * getName() const ;
  virtual bool isWriteable() const ;
  virtual const char * getDocumentation() const ;
  virtual TypeID getType() const ;
  virtual bool isBoundToPort() const ;
  virtual scml_endian get_endianness() const;
  virtual unsigned int get_addressing_mode() const;
  
  // query memory regions
  typedef ::scml_memory_base * memory_pointer_type;

  // queries for alias relations
  virtual bool isAlias() const = 0;
  virtual size_type getTotalOffset() const = 0;
  virtual size_type getSize() const = 0;
  virtual this_pointer_type getParent() const = 0;
  virtual unsigned int getWordSize() const = 0;

  // queries for routers
  virtual bool isRouter() const = 0;

  // getters for signed
  virtual ErrorCode getRegisterValueInt8(int8 & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueInt16(int16 & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueInt32(int32 & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueInt64(int64 & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValue_sc_signed(sc_dt::sc_signed & result,
                                               uint64 elementIndex = 0);

  virtual ErrorCode getRegisterValueVecInt8 (::std::vector<  int8 > & result,
                                             uint64 elementIndex = 0,
                                             uint32 elementCount = 1);
  virtual ErrorCode getRegisterValueVecInt16(::std::vector< int16 > & result,
                                             uint64 elementIndex = 0,
                                             uint32 elementCount = 1);

  virtual ErrorCode getRegisterValueVecInt32(::std::vector< int32 > & result,
                                             uint64 elementIndex = 0,
                                             uint32 elementCount = 1);

  virtual ErrorCode getRegisterValueVecInt64(::std::vector< int64 > & result,
                                             uint64 elementIndex = 0,
                                             uint32 elementCount = 1);

  virtual ErrorCode getRegisterValueVec_sc_signed(::std::vector< sc_dt::sc_signed> & result,
                                                  uint64 elementIndex,
                                                  uint32 elementCount);
  // getters for unsigned
  virtual ErrorCode getRegisterValueUint8 (uint8 & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueUint16(uint16 & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueUint32(uint32 & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueUint64(uint64 & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValue_sc_unsigned(sc_dt::sc_unsigned & result,
                                                 uint64 elementIndex = 0);

  // getters for unsigned
  virtual ErrorCode getRegisterValueVecUint8 (::std::vector<  uint8 > & result,
                                              uint64 elementIndex = 0,
                                              uint32 elementCount = 1);
  virtual ErrorCode getRegisterValueVecUint16(::std::vector< uint16 > & result,
                                              uint64 elementIndex = 0,
                                              uint32 elementCount = 1);
  virtual ErrorCode getRegisterValueVecUint32(::std::vector< uint32 > & result,
                                              uint64 elementIndex = 0,
                                              uint32 elementCount = 1);
  virtual ErrorCode getRegisterValueVecUint64(::std::vector< uint64 > & result,
                                              uint64 elementIndex = 0,
                                              uint32 elementCount = 1);
  virtual ErrorCode getRegisterValueVec_sc_unsigned(::std::vector< sc_dt::sc_unsigned> & result,
                                                    uint64 elementIndex,
                                                    uint32 elementCount);
  
  // getters for floating point
  virtual ErrorCode getRegisterValueFloat(float & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueDouble(double & result, uint64 elementIndex = 0);

  // setters for signed
  virtual ErrorCode setRegisterValueInt8(int8 result, uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueInt16(int16 result, uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueInt32(int32 result, uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueInt64(int64 result, uint64 elementIndex = 0);

  // setters for unsigned
  virtual ErrorCode setRegisterValueUint8(uint8 result, uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueUint16(uint16 result, uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueUint32(uint32 result, uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueUint64(uint64 result, uint64 elementIndex = 0);

  // setters for floating point
  virtual ErrorCode setRegisterValueFloat(float result, uint64 elementIndex = 0);
  virtual ErrorCode setRegisterValueDouble(double result, uint64 elementIndex = 0);

  // serialized getter/setter
  virtual ErrorCode getRegisterValueVec(::std::vector< uint8 >& result,
                                        uint64 elementIndex = 0,
                                        uint32 elementCount = 1);
  virtual ErrorCode setRegisterValue(const ::std::vector<  uint8 >& result,
                                     uint64 elementIndex = 0);

  // The following methods should be avoided since they are not portable
  // between 32 bit and 64 bit hosts.
#if __WORDSIZE == 64
  virtual ErrorCode getRegisterValueInt64(long & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueUint64(unsigned long & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueVecInt64(::std::vector< long > & result,
                                             uint64 elementIndex = 0,
                                             uint32 elementCount = 1);
  virtual ErrorCode getRegisterValueVecUint64(::std::vector< unsigned long > & result,
                                              uint64 elementIndex = 0,
                                              uint32 elementCount = 1);
#else
  virtual ErrorCode getRegisterValueInt32(long & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueUint32(unsigned long & result, uint64 elementIndex = 0);
  virtual ErrorCode getRegisterValueVecInt32(::std::vector< long > & result,
                                             uint64 elementIndex = 0,
                                             uint32 elementCount = 1);
  virtual ErrorCode getRegisterValueVecUint32(::std::vector< unsigned long > & result,
                                              uint64 elementIndex = 0,
                                              uint32 elementCount = 1);
#endif  

  
  static ::std::string defaultName();

  // see sc_object
  virtual const char* kind() const ;
  virtual void print(::std::ostream& os) const;


  // additional queries on memories
  virtual bool hasReadCallBack() const;
  virtual bool hasWriteCallBack() const;
  virtual bool hasTransportCallBack() const;
  virtual bool hasBitfieldsAttached() const;

  typedef scml_bitfield_base::bitfield_pointer_container bitfield_pointer_container;
  virtual bool getBitfieldPointers( bitfield_pointer_container & ) const;

  // allowed operations controls
  unsigned int get_allowed_operations() const;
  void set_allowed_operations( unsigned int);
  void set_read_only( bool signal_error = true);
  void set_write_only( bool signal_error = true);
  bool is_reading_allowed() const;
  bool is_writing_allowed() const;
  bool signal_error_on_disallowed_read() const;
  bool signal_error_on_disallowed_write() const;


  // query callbacks
  virtual CallBackType getCallBackType() const;
  virtual bool getTransportCallBackName(std::string& name) const;
  virtual bool getReadCallBackName(std::string& name) const;
  virtual bool getWriteCallBackName(std::string& name) const;

  typedef std::vector<this_pointer_type> memory_pointer_container;
  virtual unsigned int getAliasPointers(memory_pointer_container&) const;

  bool registerCallbackObserver(scml_callback_observer* o);
  bool unregisterCallbackObserver(scml_callback_observer* o);
  bool hasCallbackObservers() const { return mCallbackObservers.has_observers(); }

protected:
  PVInterfaceType determinePVInterfaceType(const char* if_typename_);

protected:
  explicit scml_memory_base( const char * name );
  explicit scml_memory_base( const ::std::string& name );
public:
  virtual ~scml_memory_base();

private:
  void initialise( const ::std::string& name );

  // disable
  scml_memory_base();
  scml_memory_base( const scml_memory_base & );
  scml_memory_base & operator= ( const scml_memory_base & );

private:
  static unsigned int memIdCount;
  unsigned int m_AllowedOperationsType;

protected:
  scml_callback_observers mCallbackObservers;
};

#endif
