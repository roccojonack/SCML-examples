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
 * Purpose of file : definition of interface for a memory callback observer
 *
 */

#ifndef SCML_MEMORY_CALLBACK_OBSERVER_IF_H
#define SCML_MEMORY_CALLBACK_OBSERVER_IF_H

class scml_memory_base;

class scml_memory_callback_observer_if  {
public:
   virtual void memory_callback_changed(const scml_memory_base* /*m*/) {}

protected:
  scml_memory_callback_observer_if() {}
  virtual ~scml_memory_callback_observer_if() {}

private:
  // disable
  scml_memory_callback_observer_if( const scml_memory_callback_observer_if & );
  scml_memory_callback_observer_if & operator= ( const scml_memory_callback_observer_if & );
};

#endif
