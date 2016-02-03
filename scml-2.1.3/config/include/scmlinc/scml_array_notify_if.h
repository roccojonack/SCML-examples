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
 * Purpose of file : 
 *
 */

#ifndef SCML_ARRAY_NOTIFY_IF_H
#define SCML_ARRAY_NOTIFY_IF_H

class scml_array_base;

class scml_array_notify_if {
public:
  typedef scml_array_base * array_base_pointer_type;

  virtual void claim_data_notification( array_base_pointer_type );
  virtual void claim_space_notification( array_base_pointer_type );

protected:
  scml_array_notify_if();
  virtual ~scml_array_notify_if();

private: 
  // disable
  scml_array_notify_if( const scml_array_notify_if & );
  scml_array_notify_if & operator= ( const scml_array_notify_if & );
};

#endif
