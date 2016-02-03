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

#include "scml_bitfield_base.h"

/************************************************************************
 * 
 */
scml_bitfield_base::scml_bitfield_base()
{
}

scml_bitfield_base::~scml_bitfield_base()
{
}

/************************************************************************
 * 
 */

scml_bitfield_base::size_type
scml_bitfield_base::getBitfieldOffset() const
{
  return 0;
}

scml_bitfield_base::size_type
scml_bitfield_base::getBitfieldSize() const
{
  return 0;
}

const char * scml_bitfield_base::getBitfieldName() const
{
  return "anonymous";
}

const char * scml_bitfield_base::getName() const
{
  return "anonymous";
}

bool scml_bitfield_base::hasTransportCallBack() const
{
  return false;
}

bool scml_bitfield_base::hasReadCallBack() const
{
  return false;
}

bool scml_bitfield_base::hasWriteCallBack() const
{
  return false;
}

bool scml_bitfield_base::getTransportCallBackName(std::string&) const
{
   return false;
}

bool scml_bitfield_base::getReadCallBackName(std::string&) const
{
   return false;
}

bool scml_bitfield_base::getWriteCallBackName(std::string&) const
{
   return false;
}

bool
scml_bitfield_base::
registerCallbackObserver(scml_bitfield_callback_observer* o)
{
  return mCallbackObservers.register_observer(o);
}

bool
scml_bitfield_base::
unregisterCallbackObserver(scml_bitfield_callback_observer* o)
{
  return mCallbackObservers.unregister_observer(o);
}

