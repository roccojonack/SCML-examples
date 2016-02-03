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
 * Purpose of file : Definition of operations for scml_memory
 *
 */

#ifndef SCML_MEMORY_OPERATIONS_H
#define SCML_MEMORY_OPERATIONS_H

#include <string>
#include <vector>
#include <map>
#include <limits.h>

#include "scmlinc/scml_memory_operations_podt_common.h"

/************************************************************************
 * operations for scml_memory defined here
 */

template< typename DT > class scml_memory_operations;

/************************************************************************
 * macro for registration of call back function
 */
#define MEMORY_REGISTER_TRANSPORT( mem, func ) \
do { (mem).registerTransportCB( this, &SC_CURRENT_USER_MODULE::func, true, 0, #func ); } while(0)

#define MEMORY_REGISTER_TRANSPORT_USER( mem, func, id ) \
do { (mem).registerTransportCB( this, &SC_CURRENT_USER_MODULE::func, true, (id), #func ); } while(0)

#define MEMORY_REGISTER_READ( mem, func ) \
do { (mem).registerReadCB( this, &SC_CURRENT_USER_MODULE::func, true, 0, #func ); } while(0)

#define MEMORY_REGISTER_READ_USER( mem, func, id ) \
do { (mem).registerReadCB( this, &SC_CURRENT_USER_MODULE::func, true, (id), #func ); } while(0)

#define MEMORY_REGISTER_WRITE( mem, func ) \
do { (mem).registerWriteCB( this, &SC_CURRENT_USER_MODULE::func, true, 0, #func ); } while(0)

#define MEMORY_REGISTER_WRITE_USER( mem, func, id ) \
do { (mem).registerWriteCB( this, &SC_CURRENT_USER_MODULE::func, true, (id), #func ); } while(0)

#define MEMORY_REGISTER_NB_TRANSPORT( mem, func ) \
do { (mem).registerTransportCB( this, &SC_CURRENT_USER_MODULE::func, false, 0, #func ); } while(0)

#define MEMORY_REGISTER_NB_TRANSPORT_USER( mem, func, id ) \
do { (mem).registerTransportCB( this, &SC_CURRENT_USER_MODULE::func, false, (id), #func ); } while(0)

#define MEMORY_REGISTER_NB_READ( mem, func ) \
do { (mem).registerReadCB( this, &SC_CURRENT_USER_MODULE::func, false, 0, #func ); } while(0)

#define MEMORY_REGISTER_NB_READ_USER( mem, func, id ) \
do { (mem).registerReadCB( this, &SC_CURRENT_USER_MODULE::func, false, (id), #func ); } while(0)

#define MEMORY_REGISTER_NB_WRITE( mem, func ) \
do { (mem).registerWriteCB( this, &SC_CURRENT_USER_MODULE::func, false, 0, #func ); } while(0)

#define MEMORY_REGISTER_NB_WRITE_USER( mem, func, id ) \
do { (mem).registerWriteCB( this, &SC_CURRENT_USER_MODULE::func, false, (id), #func ); } while(0)

/************************************************************************
 * partial template specialisation
 */

#include "scmlinc/scml_memory_operations_pts_bool.h"
#include "scmlinc/scml_memory_operations_pts_char.h"

// disabling float and double
// #include "scmlinc/scml_memory_operations_pts_float.h"
// #include "scmlinc/scml_memory_operations_pts_double.h"
// omitting long double (different sizes)

#include "scmlinc/scml_memory_operations_pts_signed_char.h"
#include "scmlinc/scml_memory_operations_pts_signed_short_int.h"
#include "scmlinc/scml_memory_operations_pts_signed_int.h"
#include "scmlinc/scml_memory_operations_pts_signed_long_int.h"
#include "scmlinc/scml_memory_operations_pts_signed_long_long.h"

#include "scmlinc/scml_memory_operations_pts_unsigned_char.h"
#include "scmlinc/scml_memory_operations_pts_unsigned_short_int.h"
#include "scmlinc/scml_memory_operations_pts_unsigned_int.h"
#include "scmlinc/scml_memory_operations_pts_unsigned_long_int.h"
#include "scmlinc/scml_memory_operations_pts_unsigned_long_long.h"

#include "scmlinc/scml_memory_operations_pts_sc_biguint_n.h"

/************************************************************************
 * Generic Template
 */
// template< typename DT > 
// class scml_memory_operations : public scml_memory_base {
// public:
//   scml_memory_operations() {}  
//   virtual ~scml_memory_operations() {}

// private:
//   // disable
//   scml_memory_operations( const scml_memory_operations & );
//   scml_memory_operations & operator= ( const scml_memory_operations & );
// };

#endif
