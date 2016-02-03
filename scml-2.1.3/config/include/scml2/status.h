/******************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  **
 *       This software and the associated documentation are confidential     **
 *                  and proprietary to Synopsys, Inc.                        **
 *        Your use or disclosure of this software is subject                 **
 *      to the terms and conditions of a written license agreement           **
 *           between you, or your company, and Synopsys, Inc.                **
 *                                                                           **
 *****************************************************************************/
#ifndef SCML2_STATUS_H
#define SCML2_STATUS_H

#include <systemc>
#include <set>
#include <string>

namespace scml2 {

class status_observer;

class status : public sc_core::sc_object
{
public:
  explicit status(const std::string& name);
  virtual ~status();

  std::string get_name() const;

  void set_status(const std::string& status);
  const std::string& get_status() const;

  bool register_observer(status_observer* o);
  bool unregister_all_observers();
  bool unregister_observer(status_observer* o);

  bool has_observers() const;

private:
  void notify_observers() const;

private:
  std::string mStatus;
  typedef std::set<status_observer*> Observers;
  typedef Observers::iterator ObserversIter;
  typedef Observers::const_iterator ObserversConstIter;
  Observers mObservers;
};

inline
std::string
status::
get_name() const
{
  return name();
}

inline
const std::string&
status::
get_status() const
{
  return mStatus;
}
 
inline
bool
status::
has_observers() const
{
  return !mObservers.empty();
}

}

#endif
