/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MAPPED_RANGES_OBSERVER_H
#define SCML2_MAPPED_RANGES_OBSERVER_H

namespace scml2 {

class mapped_ranges_observer_owner;

class mapped_ranges_observer
{
public:
  mapped_ranges_observer(mapped_ranges_observer_owner* owner);
  virtual ~mapped_ranges_observer();

  mapped_ranges_observer_owner* get_owner() const;

private:
  mapped_ranges_observer_owner* mOwner;
};

inline
mapped_ranges_observer::
mapped_ranges_observer(mapped_ranges_observer_owner *owner) :
  mOwner(owner)
{
}

inline
mapped_ranges_observer::
~mapped_ranges_observer()
{
}

inline
mapped_ranges_observer_owner*
mapped_ranges_observer::
get_owner() const
{
  return mOwner;
}

}

#endif
