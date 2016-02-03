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
// Modifications : 
//
// Purpose of file : implementation of class scml_memory_user
//
*/

#include "scml_memory_user.h"

scml_memory_user & scml_memory_user::instance() 
{
  static scml_memory_user inst;
  return inst;  
}

scml_memory_user::scml_memory_user() :
  mLastTopLevelAddress( 0),
  mLastUserId( 0),
  mDebug( false)
{
}

scml_memory_user::~scml_memory_user()
{
}

