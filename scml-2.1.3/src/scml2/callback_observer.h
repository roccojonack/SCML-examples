/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_CALLBACK_OBSERVER_H
#define SCML2_CALLBACK_OBSERVER_H

#include <scml2/types.h>

namespace scml2 {

class callback_observer_owner;

class callback_observer
{
public:
  callback_observer(callback_observer_owner* owner,
                    access_type t,
                    access_mode m);
  virtual ~callback_observer();

  access_type get_access_type() const;
  void set_access_type(access_type t);
  access_mode get_access_mode() const;
  void set_access_mode(access_mode t);
  callback_observer_owner* get_owner() const;

private:
  access_type mAccessType;
  access_mode mAccessMode;
  callback_observer_owner* mOwner;
};

inline
callback_observer::
callback_observer(callback_observer_owner *owner,
                  access_type t,
                  access_mode m) :
  mAccessType(t),
  mAccessMode(m),
  mOwner(owner)
{
}

inline
callback_observer::
~callback_observer()
{
}
inline
access_type
callback_observer::
get_access_type() const
{
  return mAccessType;
}

inline
void
callback_observer::
set_access_type(access_type t)
{
  mAccessType = t;
}

inline
access_mode
callback_observer::
get_access_mode() const
{
  return mAccessMode;
}

inline
void
callback_observer::
set_access_mode(access_mode t)
{
  mAccessMode = t;
}

inline
callback_observer_owner*
callback_observer::
get_owner() const
{
  return mOwner;
}

}

#endif
