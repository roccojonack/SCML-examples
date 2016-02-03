/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/abstraction_level_switch.h>
#include <scml2/abstraction_level_switch_observer.h>
#include <cassert>

namespace scml2 {

abstraction_level_switch&
abstraction_level_switch::
get_instance()
{
  static abstraction_level_switch instance;
  return instance;
}

abstraction_level_switch::
abstraction_level_switch() :
  mDmiAllowed(true)
{
}

void
abstraction_level_switch::
set_dmi_allowed(bool dmiAllowed)
{
  if (mDmiAllowed != dmiAllowed) {
    mDmiAllowed = dmiAllowed;
    notify_observers();
  }
}

void
abstraction_level_switch::
register_observer(abstraction_level_switch_observer* o)
{
  assert(o);
  mObservers.insert(o);
}

void
abstraction_level_switch::
unregister_observer(abstraction_level_switch_observer* o)
{
  mObservers.erase(o);
}

void
abstraction_level_switch::
notify_observers()
{
  Observers::iterator it = mObservers.begin();
  const Observers::const_iterator end = mObservers.end();

  for (; it != end; ++it) {
    (*it)->handle_abstraction_level_switched();
  }
}

}
