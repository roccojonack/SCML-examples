/******************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  **
 *       This software and the associated documentation are confidential     **
 *                  and proprietary to Synopsys, Inc.                        **
 *        Your use or disclosure of this software is subject                 **
 *      to the terms and conditions of a written license agreement           **
 *           between you, or your company, and Synopsys, Inc.                **
 *                                                                           **
 *****************************************************************************/
#ifndef SCML2_STATUS_REGISTRY_H
#define SCML2_STATUS_REGISTRY_H

#include <set>
#include <vector>
#include <string>

namespace scml2 {

class status;

class status_registry
{
public:
  static status_registry& get_instance();

  status* find_status_by_name(const std::string& name) const;
  unsigned int collect_statuses(std::vector<status*>& v) const;

private:
  friend class status;

  bool register_status(status* m);
  bool unregister_status(status* m);

private:
  status_registry();
  ~status_registry();

private:
  typedef std::set<status*> States;
  typedef States::iterator StatesIter;
  typedef States::const_iterator StatesConstIter;
  States mStates;
};

}

#endif
