/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_CONTENT_OBSERVER_H
#define SCML2_MEMORY_CONTENT_OBSERVER_H

#include <scml2/types.h>

namespace scml2 {

class memory_content_observer_owner;

class memory_content_observer
{
public:
  memory_content_observer(memory_content_observer_owner* owner,
                          access_type t,
                          access_mode m,
                          unsigned long long startIndex,
                          unsigned long long endIndex);
  virtual ~memory_content_observer();

  access_type get_access_type() const;
  void set_access_type(access_type t);
  access_mode get_access_mode() const;
  void set_access_mode(access_mode t);
  memory_content_observer_owner* get_owner() const;
  unsigned long long get_start_index() const;
  unsigned long long get_end_index() const;

private:
  memory_content_observer_owner* mOwner;
  access_type mAccessType;
  access_mode mAccessMode;
  unsigned long long mStartIndex;
  unsigned long long mEndIndex;
};

inline
memory_content_observer::
memory_content_observer(memory_content_observer_owner *owner,
                        access_type t,
                        access_mode m,
                        unsigned long long startIndex,
                        unsigned long long endIndex) :
  mOwner(owner),
  mAccessType(t),
  mAccessMode(m),
  mStartIndex(startIndex),
  mEndIndex(endIndex)
{
}

inline
memory_content_observer::
~memory_content_observer()
{
}

inline
access_type
memory_content_observer::
get_access_type() const
{
  return mAccessType;
}

inline
void
memory_content_observer::
set_access_type(access_type t)
{
  mAccessType = t;
}

inline
access_mode
memory_content_observer::
get_access_mode() const
{
  return mAccessMode;
}

inline
void
memory_content_observer::
set_access_mode(access_mode t)
{
  mAccessMode = t;
}

inline
memory_content_observer_owner*
memory_content_observer::
get_owner() const
{
  return mOwner;
}

inline
unsigned long long
memory_content_observer::
get_start_index() const
{
  return mStartIndex;
}

inline
unsigned long long
memory_content_observer::
get_end_index() const
{
  return mEndIndex;
}

}

#endif
