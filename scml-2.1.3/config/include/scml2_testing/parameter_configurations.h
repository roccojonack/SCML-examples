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

#include <scml2_testing/parameter_configuration.h>

namespace scml2 { namespace testing {
  class parameter_configurations {
    public:
      parameter_configurations() {
      }

      parameter_configurations(const parameter_configuration& pairs) {
        (*this)(pairs);
      }
      
      parameter_configurations& operator()(const parameter_configuration& values) {
        configurations.push_back(values);
        return *this;
      }

      const std::vector<parameter_configuration>& get_configurations() const {
        return configurations;
      }
      
    private:
      std::vector< parameter_configuration > configurations;
  };    
}}
