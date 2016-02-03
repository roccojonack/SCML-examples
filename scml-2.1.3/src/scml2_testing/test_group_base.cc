/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/test_group_base.h>

#include <scml2_testing/reporter_if.h>
#include <scml2_testing/test_base.h>
#include <scml2_testing/assertion_failed.h>
#include <scml2_logging.h>
#include <scmlinc/scml_property_registry.h>

namespace scml2 { namespace testing {

test_group_base::test_group_base() {
  // SCML doesn't support anonymous loggers, so we need to generate
  // a unique name (which interests nobody). We could encode the name of the
  // test in the logger, but this still wouldn't guarantee uniqueness, and it
  // makes it hard to create the logger in a delayed way. Doing a brute force
  // search here, and not even attempting to make the name look sane
  std::string logger_name = "TestLogger";
  while (scml2::logging::registry::get_instance().find_logger_by_name(logger_name)) {
    logger_name += "_";
  }
  logger = new scml2::logging::stream_logger(logger_name, std::cout);
  scml2::logging::registry::get_instance().register_logger(logger);
}

test_group_base::~test_group_base() {
  if (logger) {
    scml2::logging::registry::get_instance().unregister_logger(logger);
    delete logger;
  }
  for (size_t i = 0; i < tests.size(); ++i) {
    delete tests[i];
  }
}

const std::vector<test_base*> test_group_base::get_tests() const {
  return tests;
}

const std::string& test_group_base::get_name() const {
  return name;
}

void test_group_base::evaluate_assertion(bool result, const std::string& filename, int linenum) {
  evaluate_assertion(result, "", filename, linenum);
}

void test_group_base::evaluate_assertion(bool result, const std::string& failmsg, const std::string& filename, int linenum) {
  reporter->count_check();
  if (result == false) {
    if (failmsg.empty()) {
      reporter->handle_test_failed("Assertion failed", filename, linenum);
    }
    else {
      reporter->handle_test_failed(failmsg, filename, linenum);
    }
    assertion_failed();
    throw test_exception();
  }
}

void test_group_base::set_reporter(reporter_if* reporter) {
  this->reporter = reporter;
}

std::string test_group_base::get_model_under_test_name() const {
  return get_name() + "_ModelUnderTest";
}

std::string test_group_base::get_mirror_model_name() const {
  return get_name() + "_Mirror";
}

void test_group_base::set_name(const std::string& name) {
  this->name = name;
}

void test_group_base::add_test(test_base* test) {
  tests.push_back(test);
}

void test_group_base::enable_logging() {
  logger->set_enable(true);
}

void test_group_base::disable_logging() {
  logger->set_enable(false);
}

scml2::testing::property_server* test_group_base::get_property_server() {
  return &property_server;
}

const parameter_configuration& test_group_base::get_parameter_configuration() const {
  return configuration;
}

void test_group_base::set_parameter_configuration(const parameter_configuration& configuration) {
  this->configuration = configuration;
}

void test_group_base::load_parameter_configuration() {
  scml_property_registry::inst().setCustomPropertyServer(&property_server);
  std::vector<std::pair<std::string,std::string> > parameters = configuration.get_parameters();
  for (size_t i = 0; i < parameters.size(); ++i) {
    get_property_server()->setPropertyUntyped(get_model_under_test_name() + "." + parameters[i].first, parameters[i].second);
    get_property_server()->setPropertyUntyped(get_mirror_model_name() + "." + parameters[i].first, parameters[i].second);
  }
}

}}
