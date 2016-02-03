/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_RESET_TRIGGER_H
#define SCML2_RESET_TRIGGER_H

#include <systemc.h>

namespace scml2 {

  class reset_trigger_base {
  public:
    reset_trigger_base(const std::string& name, const std::string& description="");
    virtual ~reset_trigger_base();

    std::string get_name() const { return mName; }
    std::string get_description() const { return mDescription; }
    virtual int invoke(const std::string& arg) = 0;
  private:
    std::string mName;
    std::string mDescription;
  };


  template<class MODULE_TYPE, class FUNCPTR_TYPE>
  class reset_trigger : public reset_trigger_base {
  public:
    reset_trigger(const std::string& n, MODULE_TYPE* m, FUNCPTR_TYPE f, const std::string& d) : reset_trigger_base(n, d), mModule(m), mFunc(f) {}
    virtual int invoke(const std::string& arg) { return (mModule->*mFunc)(arg); }
  private:
    MODULE_TYPE* mModule;
    FUNCPTR_TYPE mFunc;
  };


  template<class MODULE_TYPE, class FUNCPTR_TYPE>
  inline
  void register_reset_trigger(const std::string& name,
			      MODULE_TYPE* mod, FUNCPTR_TYPE func, const std::string& /*cbName*/,
			      const std::string& description="")
  {
    (void)new reset_trigger<MODULE_TYPE, FUNCPTR_TYPE>(name, mod, func, description);
  }

}
  
#endif
