/******************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  **
 *       This software and the associated documentation are confidential     **
 *                  and proprietary to Synopsys, Inc.                        **
 *        Your use or disclosure of this software is subject                 **
 *      to the terms and conditions of a written license agreement           **
 *           between you, or your company, and Synopsys, Inc.                **
 *                                                                           **
 *****************************************************************************/
#include <scml2/status.h>
#include <scml2/status_observer.h>
#include <scml2/status_observer_owner.h>
#include <scml2/status_registry.h>

namespace scml2 {

status::
status(const std::string& name) :
  sc_core::sc_object(name.c_str())
{
  bool result = status_registry::get_instance().register_status(this);
  assert(result); (void)result;
}

status::
~status()
{
  bool result = status_registry::get_instance().unregister_status(this);
  assert(result); (void)result;
}

void
status::
set_status(const std::string& status)
{
  if (mStatus != status) {
    mStatus = status;
    notify_observers();
  }
}

void
status::
notify_observers() const
{
  ObserversConstIter it = mObservers.begin();
  ObserversConstIter end = mObservers.end();
  for (; it != end; ++it) {
    (*it)->get_owner()->handle_status_changed(*it);
  }
}

bool
status::
register_observer(status_observer* o)
{
  if (mObservers.find(o) != mObservers.end()) {
    return false;
  }
  mObservers.insert(o);
  return true;
}

bool
status::
unregister_all_observers()
{
  mObservers.clear();
  return true;
}

bool
status::
unregister_observer(status_observer* o)
{
  ObserversIter it = mObservers.find(o);
  if (it == mObservers.end()) {
    return false;
  }
  mObservers.erase(it);
  return true;
}

}
