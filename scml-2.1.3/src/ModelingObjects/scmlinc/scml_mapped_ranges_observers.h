/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML_MAPPED_RANGES_OBSERVERS_H
#define SCML_MAPPED_RANGES_OBSERVERS_H

#include "scml_mapped_ranges_observer.h"

#include <set>

class scml_mapped_ranges_owner;

class scml_mapped_ranges_observers
{
public:
  scml_mapped_ranges_observers();
  ~scml_mapped_ranges_observers();

  bool has_observers() const;

  void notify_mapped_ranges_changed();

  bool register_observer(scml_mapped_ranges_observer* o);
  bool unregister_all_observers();
  bool unregister_observer(scml_mapped_ranges_observer* o);

private:
  typedef std::set<scml_mapped_ranges_observer*> Observers;
  typedef Observers::iterator ObserversIter;
  typedef Observers::const_iterator ObserversConstIter;
  
  Observers& get_mutable_observers();

private:
  bool mObservingEnabled;
  mutable Observers* mObservers;
  mutable Observers* mMutableObservers;
  mutable int mNotifyLevel;
};

inline
bool
scml_mapped_ranges_observers::
has_observers() const
{
  return mObservingEnabled;
}

#endif
