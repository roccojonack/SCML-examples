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

#include <scml2_testing/test_group_base.h>

namespace scml2 { namespace testing {
  template<typename MODEL_TYPE, typename MIRROR_TYPE>
  class test_group : public test_group_base {
    protected:
      // Implemented by harness
      virtual void do_initialize_properties() {}
      virtual void do_initialize_test_group() {}
      virtual void do_initialize_constants() {}

      // Overridable by user
      virtual MODEL_TYPE* create_model_under_test(const char* name) {
        return new MODEL_TYPE(name);
      }

      virtual MIRROR_TYPE* create_mirror_model(const char* name) {
        return new MIRROR_TYPE(name);
      }

      // User-defined
      virtual void setup() {}
      virtual void teardown() {}
      virtual void initialize() {}
      virtual void shutdown() {}

      MODEL_TYPE* get_model_under_test() {
        return modelUnderTest;
      }

      MIRROR_TYPE* get_mirror_model() {
        return mirrorModel;
      }

    private:
      virtual void do_shutdown() {
        shutdown();
      }

      virtual void do_setup() {
        setup();
      }

      virtual void do_teardown() {
        teardown();
      }

      virtual void do_initialize() {
        do_initialize_properties();
        load_parameter_configuration();
        do_initialize_constants();
        modelUnderTest = create_model_under_test(get_model_under_test_name().c_str());
        mirrorModel = create_mirror_model(get_mirror_model_name().c_str());
        do_initialize_test_group();
        initialize();
      }


    
    protected:
      MODEL_TYPE* modelUnderTest;
      MIRROR_TYPE* mirrorModel;
  };
}}
