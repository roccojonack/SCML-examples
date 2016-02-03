/******************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  **
 *       This software and the associated documentation are confidential     **
 *                  and proprietary to Synopsys, Inc.                        **
 *        Your use or disclosure of this software is subject                 **
 *      to the terms and conditions of a written license agreement           **
 *           between you, or your company, and Synopsys, Inc.                **
 *                                                                           **
 *****************************************************************************/
#ifndef SCML2_STATUS_OBSERVER_H
#define SCML2_STATUS_OBSERVER_H

namespace scml2 {

class status_observer_owner;

class status_observer
{
public:
  status_observer(status_observer_owner* owner);
  virtual ~status_observer();

  status_observer_owner* get_owner() const;

private:
  status_observer_owner* mOwner;
};

inline
status_observer::
status_observer(status_observer_owner *owner) :
  mOwner(owner)
{
}

inline
status_observer::
~status_observer()
{
}

inline
status_observer_owner*
status_observer::
get_owner() const
{
  return mOwner;
}

}

#endif
