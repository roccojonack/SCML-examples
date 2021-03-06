/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#pragma once

namespace scml2 { namespace testing {

template<typename T>
class proxy {
  public:
    void set_target(T* target) {
      this->target = target;
      handle_target_changed();
    }

  private:
    virtual void handle_target_changed() {
    }

  protected:
    T* target;
};

}}
