/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/callback_observers.h>
#include <scml2/callback_observer_owner.h>
#include <tlm.h>
#include <cassert>

namespace {

scml2::access_type get_access_type(tlm::tlm_command command)
{
  switch (command) {
  case tlm::TLM_READ_COMMAND: return scml2::ACCESS_TYPE_READ;
  case tlm::TLM_WRITE_COMMAND: return scml2::ACCESS_TYPE_WRITE;
  case tlm::TLM_IGNORE_COMMAND: return scml2::ACCESS_TYPE_UNKNOWN;
  };
  assert(false);
  return scml2::ACCESS_TYPE_UNKNOWN;
}

}

namespace scml2 {

callback_observers::
callback_observers() :
  mObservingEnabled(false),
  mObservers(new Observers),
  mMutableObservers(0),
  mNotifyLevel(0)
{
}

callback_observers::
~callback_observers()
{
  delete mObservers;
  assert(!mMutableObservers);
}

callback_observers::Observers&
callback_observers::
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
callback_observers::
update_observers() const
{
  if (!--mNotifyLevel && mMutableObservers) {
    delete mObservers;
    mObservers = mMutableObservers;
    mMutableObservers = 0;
  }
}

unsigned int
callback_observers::
notify_begin(const tlm::tlm_generic_payload& trans, access_mode mode) const
{
  if (!mObservingEnabled) {
    return (unsigned int)-1;
  }

  static unsigned int nextId = 0;

  const unsigned int currentId = nextId;
  if (++nextId == (unsigned int)-1) {
    nextId = 0;
  }

  ++mNotifyLevel;

  ObserversConstIter it = mObservers->begin();
  ObserversConstIter end = mObservers->end();
  for (; it != end; ++it) {
    if (mMutableObservers == 0 ||
        mMutableObservers->find(*it) != mMutableObservers->end()) {
      if ((*it)->get_access_type() & get_access_type(trans.get_command()) &&
          (*it)->get_access_mode() & mode) {
        (*it)->get_owner()->handle_begin_callback(*it, trans, mode, currentId);
      }
    }
  }

  update_observers();
  return currentId;
}

void
callback_observers::
notify_end(const tlm::tlm_generic_payload& trans, unsigned int id) const
{
  if (!mObservingEnabled) {
    return;
  }

  ++mNotifyLevel;

  ObserversConstIter it = mObservers->begin();
  ObserversConstIter end = mObservers->end();
  for (; it != end; ++it) {
    if (mMutableObservers == 0 ||
        mMutableObservers->find(*it) != mMutableObservers->end()) {
      (*it)->get_owner()->handle_end_callback(*it, trans, id);
    }
  }

  update_observers();
}

void
callback_observers::
notify_callback_changed(access_type type, access_mode mode)
{
  if (!mObservingEnabled) {
    return;
  }

  ++mNotifyLevel;

  ObserversConstIter it = mObservers->begin();
  ObserversConstIter end = mObservers->end();
  for (; it != end; ++it) {
    if (mMutableObservers == 0 ||
        mMutableObservers->find(*it) != mMutableObservers->end()) {
      if ((*it)->get_access_type() & type &&
          (*it)->get_access_mode() & mode) {
        (*it)->get_owner()->handle_callback_changed(*it, type, mode);
      }
    }
  }

  update_observers();
}

bool
callback_observers::
register_observer(callback_observer* o)
{
  Observers& observers = get_mutable_observers();
  if (observers.find(o) != observers.end()) {
    return false;
  }
  mObservingEnabled = true;
  observers.insert(o);
  return true;
}

bool
callback_observers::
unregister_all_observers()
{
  Observers& observers = get_mutable_observers();
  observers.clear();
  mObservingEnabled = false;
  return true;
}

bool
callback_observers::
unregister_observer(callback_observer* o)
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

}
