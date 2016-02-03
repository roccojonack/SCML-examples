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
#include <string>

#include <scml2_testing/test_exception.h>
#include <scml2_testing/reporter_if.h>
#include <scml2_testing/property_server.h>
#include <systemc> // For evaluate_assertion
#include <scml2_testing/parameter_configuration.h>

namespace scml2 { namespace logging {
  class stream_logger;
}}

namespace scml2 { namespace testing {
  class test_base;
  struct complete;
  template<typename A, typename B, typename C> class predicate;

  class test_group_base {
    public:
      template<typename T> friend class test_group_factory;

      test_group_base();
      ~test_group_base();

      virtual void register_tests() = 0;

      virtual void do_initialize() = 0;
      virtual void do_shutdown() = 0;
      virtual void do_setup() = 0;
      virtual void do_teardown() = 0;

      const std::vector<test_base*> get_tests() const;
      const std::string& get_name() const;
      const parameter_configuration& get_parameter_configuration() const;

      void set_reporter(reporter_if* reporter);

      void evaluate_assertion(bool value, const std::string& filename, int linenum);
      void evaluate_assertion(bool value, const std::string& message, const std::string& filename, int linenum);

      template<typename VALUE_PROXY_TYPE, typename VALUE_TYPE>
      void evaluate_assertion(predicate<complete, VALUE_PROXY_TYPE, VALUE_TYPE> predicate, const std::string& filename, int linenum) {
        evaluate_assertion(predicate, "", filename, linenum);
      }

      template<typename VALUE_PROXY_TYPE, typename VALUE_TYPE>
      void evaluate_assertion(predicate<complete, VALUE_PROXY_TYPE, VALUE_TYPE> predicate, const std::string& message, const std::string& filename, int linenum) {
        reporter->count_check();

        // Wait the given number of cycles
        if (predicate.get_cycles() >= 0) {
          sc_core::wait(predicate.get_cycles()*predicate.get_clock()->get_period_ps(), sc_core::SC_PS);
        }
        if (predicate.get_after_ms() >= 0) {
          sc_core::wait(predicate.get_after_ms(), sc_core::SC_MS);
        }

        if (predicate.get_within_ms() >= 0) {
          // Poll the value 
          long long waitNS = 0;
          long long increment = predicate.get_within_ms_polling_interval_ns();
          while (waitNS < predicate.get_within_ms()*1000000) {
            if (predicate.get_expect_fail()) {
              if (check_value_fail(predicate, message, filename, linenum, false)) {
                return;
              }
            }
            else {
              if (check_value_equal(predicate, message, filename, linenum, false)) {
                return;
              }
            }
            sc_core::wait(increment, sc_core::SC_NS);
            waitNS += increment;
          }
        }

        // Process all pending events
        while (sc_core::sc_pending_activity_at_current_time()) {
          sc_core::wait(sc_core::SC_ZERO_TIME);
        }

        // Perform the check
        if (predicate.get_expect_fail()) {
          check_value_fail(predicate, message, filename, linenum, true);
        }
        else {
          check_value_equal(predicate, message, filename, linenum, true);
        }
      }

    protected:
      scml2::testing::property_server* get_property_server();
      
      std::string get_model_under_test_name() const;
      std::string get_mirror_model_name() const;
      void set_name(const std::string& name);
      void set_parameter_configuration(const parameter_configuration& configuration);
      void add_test(test_base* test);
      void load_parameter_configuration();

      void enable_logging();
      void disable_logging();

    private:
      template<typename VALUE_PROXY_TYPE, typename VALUE_TYPE>
      bool check_value_fail(predicate<complete, VALUE_PROXY_TYPE, VALUE_TYPE> predicate, const std::string& message, const std::string& filename, int linenum, bool throwIfFails) {
        bool ok = false;
        predicate.get_value_proxy().get_value(&ok);
        if (ok) {
          if (throwIfFails) {
            std::ostringstream msg;
            msg << "predicate failed:" << std::endl;
            if (message.empty()) {
              msg << "  Reading value succeeded (expected failure)" << std::endl;
            }
            else {
              msg << "  " << message;
            }
            reporter->handle_test_failed(msg.str(), filename, linenum);
            throw test_exception();
          }
        }
        return !ok;
      }

      template<typename VALUE_PROXY_TYPE, typename VALUE_TYPE>
      bool check_value_equal(predicate<complete, VALUE_PROXY_TYPE, VALUE_TYPE> predicate, const std::string& message, const std::string& filename, int linenum, bool throwIfFails) {
        bool ok = false;
        typename VALUE_PROXY_TYPE::ValueType actualValue = predicate.get_value_proxy().get_value(&ok);
        if (!ok) {
          if (throwIfFails) {
            std::ostringstream msg;
            msg << "predicate failed:" << std::endl;
            if (message.empty()) {
              msg << "  Error while reading value" << std::endl;
            }
            else {
              msg << "  " << message;
            }
            reporter->handle_test_failed(msg.str(), filename, linenum);
            throw test_exception();
          }
          return false;
        }
        VALUE_TYPE expectedValue = predicate.get_expected_value();
        bool isEqual = equals(actualValue, expectedValue);
        if (!isEqual && throwIfFails) {
          std::ostringstream msg;
          msg << "predicate failed:" << std::endl;
          if (message.empty()) {
            msg << "  Expected: " << std::dec << predicate.get_expected_value() 
              << " (0x" << std::hex << predicate.get_expected_value() << ")" << std::endl;
            msg << "  Got: " << std::dec << predicate.get_value_proxy().get_value(NULL)
              << " (0x" << std::hex << predicate.get_value_proxy().get_value(NULL) << ")" << std::endl;
          }
          else {
            msg << "  " << message;
          }
          reporter->handle_test_failed(msg.str(), filename, linenum);
          throw test_exception();
        }
        return isEqual;
      }

    private:
      std::vector<test_base*> tests;
      std::string name;
      reporter_if* reporter;
      scml2::logging::stream_logger* logger;
      scml2::testing::property_server property_server;
      parameter_configuration configuration;
  };
}}

