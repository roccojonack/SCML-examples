/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include "scml_callback_observers.h"
#include "scml_callback_observer_owner.h"
#include "scmlinc/scml_memory_pv_if.h"
#include <systemc>
#include <cassert>

scml_callback_observers::
scml_callback_observers() :
  mObservingEnabled(false),
  mObservers(new Observers),
  mMutableObservers(0),
  mNotifyLevel(0)
{
}

scml_callback_observers::
~scml_callback_observers()
{
  delete mObservers;
  assert(!mMutableObservers);
}

scml_callback_observers::Observers&
scml_callback_observers::
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
scml_callback_observers::
update_observers() const
{
  if (!--mNotifyLevel && mMutableObservers) {
    delete mObservers;
    mObservers = mMutableObservers;
    mMutableObservers = 0;
  }
}

template <typename DT, typename AT>
unsigned int
scml_callback_observers::
notify_begin(const PVReq<DT,AT>& req) const
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
      scml::AccessType type = req.getType() == pvRead ? scml::ACCESS_TYPE_READ : scml::ACCESS_TYPE_WRITE;
      scml::AccessMode mode = req.getMode() == pvDebug ? scml::ACCESS_MODE_DEBUG : scml::ACCESS_MODE_REGULAR;
      if ((*it)->get_access_type() & type &&
          (*it)->get_access_mode() & mode) {
        (*it)->get_owner()->handle_begin_callback(*it, req, currentId);
      }
    }
  }
  
  update_observers();
  return currentId;
}

template <typename DT, typename AT>
void
scml_callback_observers::
notify_end(const PVReq<DT,AT>& req, unsigned int id) const
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
      (*it)->get_owner()->handle_end_callback(*it, req, id);
    }
  }

  update_observers();
}

bool
scml_callback_observers::
register_observer(scml_callback_observer* o)
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
scml_callback_observers::
unregister_observer(scml_callback_observer* o)
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

#define EXPLICIT_INSTANTIATION(IF) \
  template unsigned int scml_callback_observers::notify_begin(const IF::request_type& req) const; \
  template void scml_callback_observers::notify_end(const IF::request_type& req, unsigned int id) const;
SCML_FOR_EACH_PV_INTERFACE_TYPE(EXPLICIT_INSTANTIATION)
#undef EXPLICIT_INSTANTIATION

