/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#ifndef SCML2_TAGGED_PIN_CALLBACK_TAGGED_H
#define SCML2_TAGGED_PIN_CALLBACK_TAGGED_H

#include <scml2/pin_callback_base.h>

namespace scml2 {
  template <typename C, typename T>
  class pin_callback_tagged : public pin_callback_base<T> {
    public:
      typedef void (C::*CallbackType)(int);

      pin_callback_tagged(sc_core::sc_in<T>& p, sc_core::sc_event_finder* e, C& c, CallbackType cb, int tag) : pin_callback_base<T>(p, e), mClass(c), mCallback(cb), mTag(tag) {
      }

      virtual void execute() {
        assert(mCallback);
        (mClass.*mCallback)(mTag);
      }

    private:
      C& mClass;
      CallbackType mCallback;
      int mTag;
  };
}

#endif
