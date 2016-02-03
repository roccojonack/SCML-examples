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
 * Purpose of file : Definition of cnsc pv mulit port modeling object
 *
 */

#ifndef SCML_PV_MULTI_PORT_H
#define SCML_PV_MULTI_PORT_H

#include <PV/PV.h>
#include <systemc.h>

template< typename DT, typename AT >
class scml_pv_multi_port : public sc_port< PV_if< DT, AT >, 0 >
{
public:
  typedef AT data_type;
  typedef DT address_type;
  typedef PVReq< DT, AT > request_type;
  typedef PVResp< DT> response_type;

public:
  explicit scml_pv_multi_port( const char* name);
  scml_pv_multi_port();
  
private:
  // disable
  scml_pv_multi_port( const scml_pv_multi_port & );
  scml_pv_multi_port & operator= ( const scml_pv_multi_port & );
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */

template< typename DT, typename AT>
inline
scml_pv_multi_port< DT, AT>::
scml_pv_multi_port( const char * name) : 
  sc_port< PV_if< DT, AT>, 0 >( name)
{
}

template< typename DT, typename AT>
inline
scml_pv_multi_port< DT, AT>::
scml_pv_multi_port() :
  sc_port< PV_if< DT, AT>, 0 >( sc_gen_unique_name(  "scml_pv_multi_port" ))
{
}

#endif

