/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/bitfield_callback_observers.h>
#include <scml2/bitfield_callback_observer_owner.h>
#include <scml2/utils.h>
#include <cassert>

namespace scml2 {

template <typename DT>
bitfield_callback_observers<DT>::
bitfield_callback_observers() :
  mObservingEnabled(false),
  mObservers(new Observers),
  mMutableObservers(0),
  mNotifyLevel(0)
{
}

template <typename DT>
bitfield_callback_observers<DT>::
~bitfield_callback_observers()
{
  delete mObservers;
  assert(!mMutableObservers);
}

template <typename DT>
typename bitfield_callback_observers<DT>::Observers&
bitfield_callback_observers<DT>::
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

template <typename DT>
void
bitfield_callback_observers<DT>::
update_observers() const
{
  if (!--mNotifyLevel && mMutableObservers) {
    delete mObservers;
    mObservers = mMutableObservers;
    mMutableObservers = 0;
  }
}

template <typename DT>
unsigned int
bitfield_callback_observers<DT>::
notify_begin(const DT* data,
             const DT* bitMask,
             access_type type,
             access_mode mode) const
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
      if ((*it)->get_access_type() & type &&
          (*it)->get_access_mode() & mode) {
        (*it)->get_owner()->handle_begin_callback(*it,
                                                  data,
                                                  bitMask,
                                                  type,
                                                  mode,
                                                  currentId);
      }
    }
  }

  update_observers();
  return currentId;
}

template <typename DT>
void
bitfield_callback_observers<DT>::
notify_end(const DT* data, unsigned int id) const
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
      (*it)->get_owner()->handle_end_callback(*it, data, id);
    }
  }

  update_observers();
}

template <typename DT>
void
bitfield_callback_observers<DT>::
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

template <typename DT>
bool
bitfield_callback_observers<DT>::
register_observer(bitfield_callback_observer<DT>* o)
{
  Observers& observers = get_mutable_observers();
  if (observers.find(o) != observers.end()) {
    return false;
  }
  mObservingEnabled = true;
  observers.insert(o);
  return true;
}

template <typename DT>
bool
bitfield_callback_observers<DT>::
unregister_all_observers()
{
  Observers& observers = get_mutable_observers();
  observers.clear();
  mObservingEnabled = false;
  return true;
}

template <typename DT>
bool
bitfield_callback_observers<DT>::
unregister_observer(bitfield_callback_observer<DT>* o)
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

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class bitfield_callback_observers<type >;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}
