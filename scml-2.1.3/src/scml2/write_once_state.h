/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_WRITE_ONCE_STATE_H
#define SCML2_WRITE_ONCE_STATE_H

#include <scml2/resource.h>

namespace scml2 {

class write_once_state : public resource
{
public:
  write_once_state() : mWritable(true) {
  }

  virtual ~write_once_state() {
  }

  void set_writable(bool b) {
    mWritable = b;
  }

  bool is_writable() const {
    return mWritable;
  }

  virtual void reset() {
    set_writable(true);
  }

private:
  bool mWritable;
};

}

#endif
