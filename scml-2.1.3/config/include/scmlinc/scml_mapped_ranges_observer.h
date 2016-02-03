/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML_MAPPED_RANGES_OBSERVER_H
#define SCML_MAPPED_RANGES_OBSERVER_H

class scml_mapped_ranges_observer_owner;

class scml_mapped_ranges_observer
{
public:
  scml_mapped_ranges_observer(scml_mapped_ranges_observer_owner* owner);
  virtual ~scml_mapped_ranges_observer();

  scml_mapped_ranges_observer_owner* get_owner() const;

private:
  scml_mapped_ranges_observer_owner* mOwner;
};

inline
scml_mapped_ranges_observer::
scml_mapped_ranges_observer(scml_mapped_ranges_observer_owner *owner) :
  mOwner(owner)
{
}

inline
scml_mapped_ranges_observer::
~scml_mapped_ranges_observer()
{
}

inline
scml_mapped_ranges_observer_owner*
scml_mapped_ranges_observer::
get_owner() const
{
  return mOwner;
}

#endif
