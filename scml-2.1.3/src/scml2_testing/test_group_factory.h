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

#include <string>

#include <scml2_testing/test_group_factory_base.h>
#include <scml2_testing/parameter_configurations.h>
#include <sstream>

namespace scml2 { namespace testing {
  class test_group_base;

  template<typename T>
  class test_group_factory : public test_group_factory_base {
    public:
      test_group_factory(const std::string& name) : name(name) {
      }

      test_group_factory(const std::string& name, const parameter_configurations& configurations) : name(name), configurations(configurations) {
      }

      virtual std::vector<test_group_base*> create_test_groups() {
        std::vector<test_group_base*> result;
        if (configurations.get_configurations().empty()) {
          T* group = new T(); 
          group->set_name(name);
          result.push_back(group);
        }
        else {
          const std::vector<parameter_configuration>& configs = configurations.get_configurations();
          for (size_t i = 0; i < configs.size(); ++i) {
            T* group = new T(); 
            group->set_parameter_configuration(configs[i]);
            std::string configName = configs[i].get_name();
            if (configName.empty()) {
              std::ostringstream s;
              s << i;
              configName = s.str();
            }
            group->set_name(name + "(" + configName + ")");
            result.push_back(group);
          }
        }
        return result;
      }

      virtual std::string get_name() const {
        return name;
      }

    private:
      std::string name;
      parameter_configurations configurations;
  };
}}

