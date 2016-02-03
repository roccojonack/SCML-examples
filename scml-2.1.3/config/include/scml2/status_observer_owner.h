/******************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  **
 *       This software and the associated documentation are confidential     **
 *                  and proprietary to Synopsys, Inc.                        **
 *        Your use or disclosure of this software is subject                 **
 *      to the terms and conditions of a written license agreement           **
 *           between you, or your company, and Synopsys, Inc.                **
 *                                                                           **
 *****************************************************************************/
#ifndef SCML2_STATUS_OBSERVER_OWNER_H
#define SCML2_STATUS_OBSERVER_OWNER_H

#include <scml2/status_observer.h>

namespace scml2 {

class status_observer_owner {
public:
  virtual ~status_observer_owner();
  virtual void handle_status_changed(status_observer* o) = 0;
};

inline
status_observer_owner::
~status_observer_owner()
{
}

}

#endif
