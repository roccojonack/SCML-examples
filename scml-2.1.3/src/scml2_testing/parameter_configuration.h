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

#include <vector>
#include <map>
#include <sstream>

namespace scml2 { namespace testing {
  class parameter_configuration {
    public:
      parameter_configuration() {
      }

      parameter_configuration(const std::string& name) : name(name) {
      }

      template<typename T>
      parameter_configuration(const std::string& key, const T& value) {
        (*this)(key, value);
      }
  
      template<typename T>
      parameter_configuration& operator()(const std::string& key, const T& value) {
        std::ostringstream s;
        s << value;
        values.push_back(std::make_pair(key, s.str()));
        return *this;
      }
  
      const std::vector< std::pair<std::string, std::string> >& get_parameters() const {
        return values;
      }

      const std::string& get_name() const {
        return name;
      }
  
    private:
      std::string name;
      std::vector< std::pair<std::string, std::string> > values;
  };    
}}
