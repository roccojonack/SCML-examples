/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ABSTRACTION_LEVEL_SWITCH_H
#define SCML2_ABSTRACTION_LEVEL_SWITCH_H

#include <set>

namespace scml2 {

class abstraction_level_switch_observer;

class abstraction_level_switch
{
public:
  static abstraction_level_switch& get_instance();

  bool is_dmi_allowed() const;
  void set_dmi_allowed(bool dmiAllowed);

  void register_observer(abstraction_level_switch_observer* o);
  void unregister_observer(abstraction_level_switch_observer* o);

private:
  abstraction_level_switch();

  void notify_observers();

private:
  bool mDmiAllowed;
  typedef std::set<abstraction_level_switch_observer*> Observers;
  Observers mObservers;
};

inline
bool
abstraction_level_switch::
is_dmi_allowed() const
{
  return mDmiAllowed;
}

}

#endif
