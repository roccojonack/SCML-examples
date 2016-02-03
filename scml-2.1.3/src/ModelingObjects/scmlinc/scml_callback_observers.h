/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML_CALLBACK_OBSERVERS_H
#define SCML_CALLBACK_OBSERVERS_H

#include "scmlinc/scml_callback_observer.h"
#include "scmlinc/scml_types.h"
#include <PV/PV.h>
#include <set>

namespace sc_core {
  class sc_time;
}

class scml_callback_owner;

class scml_callback_observers
{
public:
  scml_callback_observers();
  ~scml_callback_observers();

  bool has_observers() const;

  template <typename DT, typename AT>
  unsigned int notify_begin(const PVReq<DT, AT>& req) const;
  template <typename DT, typename AT>
  void notify_end(const PVReq<DT, AT>& req, unsigned int id) const;

  bool register_observer(scml_callback_observer* o);
  bool unregister_observer(scml_callback_observer* o);

private:
  typedef std::set<scml_callback_observer*> Observers;
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
scml_callback_observers::
has_observers() const
{
  return mObservingEnabled;
}

#endif
