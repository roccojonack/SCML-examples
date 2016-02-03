/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML_MAPPED_RANGES_OBSERVER_OWNER_H
#define SCML_MAPPED_RANGES_OBSERVER_OWNER_H

#include "scml_mapped_ranges_observer.h"

class scml_mapped_ranges_observer_owner {
public:
  virtual ~scml_mapped_ranges_observer_owner();
  virtual void handle_mapped_ranges_changed(scml_mapped_ranges_observer* o) = 0;
};

inline
scml_mapped_ranges_observer_owner::
~scml_mapped_ranges_observer_owner()
{
}

#endif
