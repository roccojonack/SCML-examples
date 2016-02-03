/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ABSTRACTION_LEVEL_SWITCH_OBSERVER_H
#define SCML2_ABSTRACTION_LEVEL_SWITCH_OBSERVER_H

namespace scml2 {

class abstraction_level_switch_observer
{
public:
  virtual ~abstraction_level_switch_observer() {}
  virtual void handle_abstraction_level_switched() = 0;
};

}

#endif
