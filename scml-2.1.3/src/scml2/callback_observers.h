/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_CALLBACK_OBSERVERS_H
#define SCML2_CALLBACK_OBSERVERS_H

#include <scml2/callback_observer.h>
#include <scml2/types.h>

#include <set>

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

class callback_observer_owner;

class callback_observers
{
public:
  callback_observers();
  ~callback_observers();

  bool has_observers() const;

  unsigned int notify_begin(const tlm::tlm_generic_payload& trans,
                            access_mode mode) const;
  void notify_end(const tlm::tlm_generic_payload& trans,
                  unsigned int id) const;
  void notify_callback_changed(access_type type, access_mode mode);

  bool register_observer(callback_observer* o);
  bool unregister_all_observers();
  bool unregister_observer(callback_observer* o);

private:
  typedef std::set<callback_observer*> Observers;
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
callback_observers::
has_observers() const
{
  return mObservingEnabled;
}

}

#endif
