/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML_BITFIELD_CALLBACK_OBSERVERS_H
#define SCML_BITFIELD_CALLBACK_OBSERVERS_H

#include "scmlinc/scml_bitfield_callback_observer.h"
#include "scmlinc/scml_types.h"

#include <set>

namespace sc_core {
  class sc_time;
}

class scml_bitfield_callback_owner;

class scml_bitfield_callback_observers
{
public:
  scml_bitfield_callback_observers();
  ~scml_bitfield_callback_observers();

  bool has_observers() const;

  unsigned int notify_begin(const unsigned int* data,
                            scml::AccessType type,
                            scml::AccessMode mode) const;
  void notify_end(const unsigned int* data, unsigned int id) const;

  bool register_observer(scml_bitfield_callback_observer* o);
  bool unregister_observer(scml_bitfield_callback_observer* o);

private:
  typedef std::set<scml_bitfield_callback_observer*> Observers;
  typedef Observers::iterator ObserversIter;
  typedef Observers::const_iterator ObserversConstIter;
  
  Observers& get_mutable_observers();
  void update_observers() const;

private:
  bool mObservingEnabled;
  mutable Observers* mObservers;
  mutable Observers* mMutableObservers;
  mutable int mNotifyLevel;
};

inline
bool
scml_bitfield_callback_observers::
has_observers() const
{
  return mObservingEnabled;
}

#endif
