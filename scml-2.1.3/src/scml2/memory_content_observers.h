/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#ifndef SCML2_MEMORY_CONTENT_OBSERVERS_H
#define SCML2_MEMORY_CONTENT_OBSERVERS_H

#include <scml2/memory_content_observer.h>
#include <scml2/types.h>

#include <map>

namespace scml2 {

class memory_content_observer_owner;
class memory_dmi;

class memory_content_observers
{
public:
  memory_content_observers();
  ~memory_content_observers();

  bool has_observers() const;

  void notify_observers(unsigned long long lowIndex,
                        unsigned long long highIndex,
                        access_type t,
                        access_mode m,
                        bool preNotPost) const;

  bool register_observer(memory_content_observer* o,
                         unsigned long long offset);
  bool unregister_all_observers();
  bool unregister_observer(memory_content_observer* o);

  void disable_dmi(memory_dmi& readDmiData, memory_dmi& writeDmiData);

private:
  typedef std::map<memory_content_observer*, unsigned long long> Observers;
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
memory_content_observers::
has_observers() const
{
  return mObservingEnabled;
}

}

#endif
