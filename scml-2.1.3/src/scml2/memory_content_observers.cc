/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_content_observers.h>
#include <scml2/memory_content_observer_owner.h>
#include <scml2/memory_dmi.h>
#include <cassert>

namespace scml2 {

memory_content_observers::
memory_content_observers() :
  mObservingEnabled(false),
  mObservers(new Observers),
  mMutableObservers(0),
  mNotifyLevel(0)
{
}

memory_content_observers::
~memory_content_observers()
{
  delete mObservers;
  assert(!mMutableObservers);
}

memory_content_observers::Observers&
memory_content_observers::
get_mutable_observers()
{
  Observers* observers = mObservers;
  if (mNotifyLevel) {
    if (!mMutableObservers) {
      // lazy creation of copy (aka copy-on-write)
      mMutableObservers = new Observers(*observers);
    }
    observers = mMutableObservers;
  }
  return *observers;
}

void
memory_content_observers::
notify_observers(unsigned long long lowIndex,
                 unsigned long long highIndex,
                 access_type t,
                 access_mode m,
                 bool preNotPost) const
{
  if (!mObservingEnabled) {
    return;
  }

  ++mNotifyLevel;

  for (unsigned long long index = lowIndex; index <= highIndex; ++index) {
    ObserversConstIter it = mObservers->begin();
    ObserversConstIter end = mObservers->end();
    for (; it != end; ++it) {
      if (mMutableObservers == 0 ||
          mMutableObservers->find(it->first) != mMutableObservers->end()) {
        const unsigned long long toplevelStartIndex = it->second + it->first->get_start_index();
        const unsigned long long toplevelEndIndex = it->second + it->first->get_end_index();
        if (toplevelStartIndex <= index && index <= toplevelEndIndex) {
          if (it->first->get_access_type() & t && it->first->get_access_mode() & m) {
            if (preNotPost) {
              it->first->get_owner()->handle_pre_content_access(it->first,
                                                                t,
                                                                m,
                                                                index - it->second);
            } else {
              it->first->get_owner()->handle_post_content_access(it->first,
                                                                 t,
                                                                 m,
                                                                 index - it->second);
            }
          }
        }
      }
    }
  }

  if (!--mNotifyLevel && mMutableObservers) {
    delete mObservers;
    mObservers = mMutableObservers;
    mMutableObservers = 0;
  }
}

bool
memory_content_observers::
register_observer(memory_content_observer* o,
                  unsigned long long offset)
{
  Observers& observers = get_mutable_observers();
  if (observers.find(o) != observers.end()) {
    return false;
  }
  mObservingEnabled = true;
  observers[o] = offset;
  return true;
}

bool
memory_content_observers::
unregister_all_observers()
{
  Observers& observers = get_mutable_observers();
  observers.clear();
  mObservingEnabled = false;
  return true;
}

bool
memory_content_observers::
unregister_observer(memory_content_observer* o)
{
  Observers& observers = get_mutable_observers();
  ObserversIter it = observers.find(o);
  if (it == observers.end()) {
    return false;
  }
  observers.erase(it);
  if (observers.empty()) {
    mObservingEnabled = false;
  }
  return true;
}

void
memory_content_observers::
disable_dmi(memory_dmi& readDmiData, memory_dmi& writeDmiData)
{
  if (!mObservingEnabled) {
    return;
  }

  ObserversConstIter it = mObservers->begin();
  ObserversConstIter end = mObservers->end();
  for (; it != end; ++it) {
    const unsigned long long toplevelStartIndex = it->second + it->first->get_start_index();
    const unsigned long long toplevelEndIndex = it->second + it->first->get_end_index();
    if (it->first->get_access_type() & ACCESS_TYPE_READ) {
      readDmiData.disable(toplevelStartIndex, toplevelEndIndex);
    }
    if (it->first->get_access_type() & ACCESS_TYPE_WRITE) {
      writeDmiData.disable(toplevelStartIndex, toplevelEndIndex);
    }
  }
}

}
