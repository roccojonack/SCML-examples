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
 * Purpose of file : Implementation of scml_memory_base modeling object
 *
 */

#include "scml_memory_base.h"
#include "scml_memory_registration.h"
#include "scml_memory_pv_if.h"
#include "scml_mapable_if.h"
#include <sstream>
#include <string>
#include <scml2_logging/severity.h>

/************************************************************************
 * 
 */
void scml_memory_base::initialise( const ::std::string& )
{
  bool result = scml_memory_registration::instance().registerMemory( this );
  assert(result); (void)result;

  set_allowed_operations( OPERATIONS_ALLOW_READ |
			  OPERATIONS_ALLOW_WRITE |
			  OPERATIONS_ERROR_DISALLOWED_READ |
			  OPERATIONS_ERROR_DISALLOWED_WRITE );
}

scml_memory_base::scml_memory_base( const char * n ) :
  sc_object( n)
{
  initialise( n);
}

scml_memory_base::scml_memory_base( const ::std::string& n ) :
  sc_object( n.c_str())
{
  initialise( n);
}

scml_memory_base::~scml_memory_base()
{
  scml_memory_registration::instance().unRegisterMemory( this );  
}


/************************************************************************
 * 
 */
 const char * scml_memory_base::getName() const
{
  return this->name();
}

::std::string scml_memory_base::defaultName()
{
  static unsigned int defaultNameCount = 0;
  ::std::ostringstream s;
  s << "scml_mem_" << defaultNameCount++ ;
  return s.str();
}

/************************************************************************
 * 
 */

bool scml_memory_base::isWriteable() const
{
  return false;
}

const char * scml_memory_base::getDocumentation() const
{
  return "";
}

scml_memory_base::TypeID scml_memory_base::getType() const
{
  return MEM_TYPE_UNKNOWN;
}

bool scml_memory_base::isBoundToPort() const
{
  return false;
}

scml_endian scml_memory_base::get_endianness() const
{
  return scml_little_endian;
}

unsigned int scml_memory_base::get_addressing_mode() const
{
  return 8;
}

/************************************************************************
 * see sc_object
 */
const char * scml_memory_base::kind() const 
{ 
  if (!getParent()) {
    return "scml_memory"; 
  } else {
    return "scml_memory_alias";
  }
}

/************************************************************************
 * getters for signed
 * default (stubbed) implementation
 */
scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueInt8( int8&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueInt16( int16&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueInt32( int32&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueInt64( int64&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValue_sc_signed( sc_dt::sc_signed&, uint64)
{
  return scml_memory_base::errorInvalidType;  
}

/************************************************************************
 * getters for signed
 * vector versions
 * default (stubbed) implementation
 */
scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecInt8 ( ::std::vector< int8 >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode 
scml_memory_base::getRegisterValueVecInt16( ::std::vector< int16 >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecInt32( ::std::vector< int32 >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecInt64( ::std::vector< int64 >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVec_sc_signed( ::std::vector< sc_dt::sc_signed>&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

/************************************************************************
 * getters for unsigned
 * default (stubbed) implementation
 */
scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueUint8( uint8&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueUint16( uint16&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueUint32( uint32&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueUint64( uint64&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValue_sc_unsigned( sc_dt::sc_unsigned&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

/************************************************************************
 * getters for unsigned
 * vector versions
 * default (stubbed) implementation
 */

scml_memory_base::ErrorCode 
scml_memory_base::getRegisterValueVecUint8 ( ::std::vector< uint8 >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecUint16( ::std::vector< uint16 >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecUint32( ::std::vector< uint32 >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecUint64( ::std::vector< uint64 >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVec_sc_unsigned( ::std::vector< sc_dt::sc_unsigned>&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

/************************************************************************
 * getters for floating point
 * default (stubbed) implementation
 */

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueFloat(  float&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueDouble( double&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

/************************************************************************
 * setters for signed
 * default (stubbed) implementation
 */
scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueInt8( int8, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueInt16( int16, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueInt32( int32, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueInt64( int64, uint64)
{
  return scml_memory_base::errorInvalidType;
}

/************************************************************************
 * setters for unsigned
 * default (stubbed) implementation
 */
scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueUint8( uint8, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueUint16( uint16, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueUint32( uint32, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueUint64( uint64, uint64)
{
  return scml_memory_base::errorInvalidType;
}

/************************************************************************
 * setters for floating point
 * default (stubbed) implementation
 */

scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueFloat( float, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::setRegisterValueDouble( double, uint64)
{
  return scml_memory_base::errorInvalidType;
}

/************************************************************************
 * Serialized getter/setter
 * default (stubbed) implementation
 */
scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVec(::std::vector< uint8 >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::setRegisterValue(const ::std::vector< uint8 >&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

/************************************************************************
 * handling the long data type
 * The following methods should be avoided since they are not portable
 * between 32 bit and 64 bit hosts.
 */
#if __WORDSIZE == 64
scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueInt64(long&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueUint64(unsigned long&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecInt64(::std::vector< long >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecUint64(::std::vector< unsigned long >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}


#else

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueInt32(long&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueUint32(unsigned long&, uint64)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecInt32(::std::vector< long >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

scml_memory_base::ErrorCode
scml_memory_base::getRegisterValueVecUint32(::std::vector< unsigned long >&, uint64, uint32)
{
  return scml_memory_base::errorInvalidType;
}

#endif  


/************************************************************************
 *
 */

bool
scml_memory_base::hasReadCallBack() const
{
  return false;
}

bool
scml_memory_base::hasWriteCallBack() const
{
  return false;
}

bool
scml_memory_base::hasTransportCallBack() const
{
  return false;
}

bool
scml_memory_base::hasBitfieldsAttached() const
{
  return false;
}

bool
scml_memory_base::getBitfieldPointers( bitfield_pointer_container& ) const
{
  return false;
}

/************************************************************************
 * allowed operations controls
 */
unsigned int
scml_memory_base::get_allowed_operations() const
{
  return m_AllowedOperationsType;
}

void 
scml_memory_base::set_allowed_operations( unsigned int a)
{
  m_AllowedOperationsType = a;
}

void scml_memory_base::set_read_only( bool signal_error)
{
  unsigned int oper( get_allowed_operations() & ~OPERATIONS_ALLOW_WRITE);
  if( signal_error) {
    oper |= OPERATIONS_ERROR_DISALLOWED_WRITE;
  } else {
    oper &= ~OPERATIONS_ERROR_DISALLOWED_WRITE;
  }
  set_allowed_operations( oper);
}

void scml_memory_base::set_write_only( bool signal_error)
{
  unsigned int oper( get_allowed_operations() & ~OPERATIONS_ALLOW_READ);
  if( signal_error) {
    oper |= OPERATIONS_ERROR_DISALLOWED_READ;
  } else {
    oper &= ~OPERATIONS_ERROR_DISALLOWED_READ;
  }
  set_allowed_operations( oper);
}

bool scml_memory_base::is_reading_allowed() const
{
  return ( get_allowed_operations() & OPERATIONS_ALLOW_READ);
}

bool scml_memory_base::is_writing_allowed() const
{
  return ( get_allowed_operations() & OPERATIONS_ALLOW_WRITE);
}

bool scml_memory_base::signal_error_on_disallowed_read() const
{
  return ( get_allowed_operations() & OPERATIONS_ERROR_DISALLOWED_READ);
}

bool scml_memory_base::signal_error_on_disallowed_write() const
{
  return ( get_allowed_operations() & OPERATIONS_ERROR_DISALLOWED_WRITE);
}


/************************************************************************
 * PVInterfaceType
 */

scml_memory_base::PVInterfaceType
scml_memory_base::determinePVInterfaceType(const char* if_typename_)
{
  if (std::string(if_typename_) == typeid(scml_memory_pv_32_32_if).name() ||
      std::string(if_typename_) == typeid(PV_if<unsigned int, unsigned int>).name()) {
    return scml::PV_INTERFACE_32_32;

  } else if (std::string(if_typename_) == typeid(scml_memory_pv_32_64_if).name() ||
             std::string(if_typename_) == typeid(PV_if<unsigned long long, unsigned int>).name()) {
    return scml::PV_INTERFACE_32_64;

  } else if (std::string(if_typename_) == typeid(scml_memory_pv_32_128_if).name() ||
             std::string(if_typename_) == typeid(PV_if<sc_biguint<128>, unsigned int>).name()) {
    return scml::PV_INTERFACE_32_128;

  } else if (std::string(if_typename_) == typeid(scml_memory_pv_32_256_if).name() ||
             std::string(if_typename_) == typeid(PV_if<sc_biguint<256>, unsigned int>).name()) {
    return scml::PV_INTERFACE_32_256;

  } else if (std::string(if_typename_) == typeid(scml_memory_pv_32_512_if).name() ||
             std::string(if_typename_) == typeid(PV_if<sc_biguint<512>, unsigned int>).name()) {
    return scml::PV_INTERFACE_32_512;

  } else if (std::string(if_typename_) == typeid(scml_memory_pv_64_32_if).name() ||
      std::string(if_typename_) == typeid(PV_if<unsigned int, unsigned long long>).name()) {
    return scml::PV_INTERFACE_64_32;

  } else if (std::string(if_typename_) == typeid(scml_memory_pv_64_64_if).name() ||
             std::string(if_typename_) == typeid(PV_if<unsigned long long, unsigned long long>).name()) {
    return scml::PV_INTERFACE_64_64;

  } else if (std::string(if_typename_) == typeid(scml_memory_pv_64_128_if).name() ||
             std::string(if_typename_) == typeid(PV_if<sc_biguint<128>, unsigned long long>).name()) {
    return scml::PV_INTERFACE_64_128;

  } else if (std::string(if_typename_) == typeid(scml_memory_pv_64_256_if).name() ||
             std::string(if_typename_) == typeid(PV_if<sc_biguint<256>, unsigned long long>).name()) {
    return scml::PV_INTERFACE_64_256;

  } else if (std::string(if_typename_) == typeid(scml_memory_pv_64_512_if).name() ||
             std::string(if_typename_) == typeid(PV_if<sc_biguint<512>, unsigned long long>).name()) {
    return scml::PV_INTERFACE_64_512;

  } else if (std::string(if_typename_) == typeid(scml_mapable_if).name()) {
    // bound to (TLM2) adaptor
    return scml::PV_INTERFACE_UNKNOWN;

  } else {
    static scml2::logging::stream s("scml_memory_base::determinePVInterfaceType", scml2::logging::severity::error());
    SCML2_LOG(s) << "Unknown pv interface type" << std::endl;
    return scml::PV_INTERFACE_UNKNOWN;
  }
}

/************************************************************************
 * Queries for callbacks
 */

scml_memory_base::CallBackType scml_memory_base::getCallBackType() const
{
  return CB_TYPE_NONE;
}

bool scml_memory_base::getTransportCallBackName(std::string&) const
{
  return false;
}

bool scml_memory_base::getReadCallBackName(std::string&) const
{
  return false;
}

bool scml_memory_base::getWriteCallBackName(std::string&) const
{
  return false;
}

/************************************************************************
 * debug
 */

void scml_memory_base::print(::std::ostream& os) const {
	scml_memory_base *cc = const_cast<scml_memory_base *>(this);
	switch (getType()) {
	    case MEM_TYPE_BOOL1:
		case MEM_TYPE_UINT8:
		{
		  uint8 v;
		  cc->getRegisterValueUint8(v);
		  os << v;
		}
		break;
	case MEM_TYPE_UINT16:
	case MEM_TYPE_UINT32:
		{
		  uint32 v;
		  cc->getRegisterValueUint32(v);
		  os << v;
		}
		break;
	case MEM_TYPE_UINT64:
	  {
	    uint64 v;
	    cc->getRegisterValueUint64(v);
	    os << v;
	  }
	  
	  break;
	case MEM_TYPE_BIGUINT:
	  break;
	case MEM_TYPE_INT8:
	  {
	    int8 v;
	    cc->getRegisterValueInt8(v);
	    os << v;
	  }
	  break;
	case MEM_TYPE_INT16:
	case MEM_TYPE_INT32:
	  {
	    int32 v;
	    cc->getRegisterValueInt32(v);
	    os << v;
	  }
	  break;
	case MEM_TYPE_INT64:
	  {
	    int64 v;
	    cc->getRegisterValueInt64(v);
	    os << v;
	  }
	  break;
	case MEM_TYPE_BIGINT:
	  break;
	case MEM_TYPE_FLOAT32:
	  break;
	case MEM_TYPE_FLOAT64:
	  break;
	case MEM_TYPE_BYTESTREAM:
	  break;
	case MEM_TYPE_UNKNOWN:
	  break;
	default:
	  break;
	}
	if( 1 < getSize()) {
	  os << " ...";
	} 
}

unsigned int
scml_memory_base::
getAliasPointers(memory_pointer_container&) const
{
  return 0;
}

bool
scml_memory_base::
registerCallbackObserver(scml_callback_observer* o)
{
  return mCallbackObservers.register_observer(o);
}

bool
scml_memory_base::
unregisterCallbackObserver(scml_callback_observer* o)
{
  return mCallbackObservers.unregister_observer(o);
}


