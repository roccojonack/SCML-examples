/*****************************************************************************
 *                   Copyright (C) 2007-2010 Synopsys, Inc.                  *
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
 * Purpose of file : Definition of the scml_mapable_if
 *
 */

#ifndef SCML_MAPABLE_IF
#define SCML_MAPABLE_IF

#include "scmlinc/scml_transport_if.h"
#include "scmlinc/scml_types.h"

class scml_mapable_if : public scml_transport_if
{
public:

public:
  virtual const char* getName() const = 0;


  // FIXME
  virtual void setPVInterfaceType(scml::PVInterfaceType pvInterfaceType) = 0;
  virtual scml::PVInterfaceType getPVInterfaceType() const = 0;

public:
  virtual sc_object* get_interface_as_sc_object() { return 0; }
};

#endif
