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

#include <scml2_testing/test_base.h>
#include <systemc>

namespace scml2 { namespace testing {
  class input_clock_proxy;

  struct null_type {};
  struct complete {};
  struct incomplete {};

  template<typename T, typename VALUE_PROXY_TYPE, typename VALUE_TYPE = null_type>
  class predicate {
    public:
      typedef predicate<complete, VALUE_PROXY_TYPE, VALUE_TYPE> completeType;

      predicate(VALUE_PROXY_TYPE proxy) : valueProxy(proxy), cycles(-1), withinMS(-1), withinMSPollingIntervalNS(-1), afterMS(-1), clock(0), expectFail(false) {
      }

      // Composition

      predicate after_cycles(int cycles, input_clock_proxy& clock) {
        this->cycles = cycles;
        this->clock = &clock;
        return *this;
      }

      predicate after_ms(int afterMS) {
        this->afterMS = afterMS;
        return *this;
      }

      predicate within_ms(int withinMS, long long pollingIntervalNS = 100000) {
        this->withinMS = withinMS;
        this->withinMSPollingIntervalNS = pollingIntervalNS;
        return *this;
      }

      predicate<complete, VALUE_PROXY_TYPE, long long> equals(long long value) { return completeWithValue(value); }
      predicate<complete, VALUE_PROXY_TYPE, unsigned long long> equals(unsigned long long value) { return completeWithValue(value); }
      predicate<complete, VALUE_PROXY_TYPE, int> equals(int value) { return completeWithValue(value); }
      predicate<complete, VALUE_PROXY_TYPE, unsigned int> equals(unsigned int value) { return completeWithValue(value); }
      predicate<complete, VALUE_PROXY_TYPE, short> equals(short value) { return completeWithValue(value); }
      predicate<complete, VALUE_PROXY_TYPE, unsigned short> equals(unsigned short value) { return completeWithValue(value); }
      predicate<complete, VALUE_PROXY_TYPE, char> equals(char value) { return completeWithValue(value); }
      predicate<complete, VALUE_PROXY_TYPE, unsigned char> equals(unsigned char value) { return completeWithValue(value); }
      predicate<complete, VALUE_PROXY_TYPE, bool> equals(bool value) { return completeWithValue(value); }

      template<int W>
      predicate<complete, VALUE_PROXY_TYPE, sc_dt::sc_uint<W> > equals(sc_dt::sc_uint<W> value) { return completeWithValue(value); }
      template<int W>
      predicate<complete, VALUE_PROXY_TYPE, sc_dt::sc_int<W> > equals(sc_dt::sc_int<W> value) { return completeWithValue(value); }

      template<int W>
      predicate<complete, VALUE_PROXY_TYPE, sc_dt::sc_bigint<W> > equals(sc_dt::sc_bigint<W> value) { return completeWithValue(value); }

      predicate<complete, VALUE_PROXY_TYPE, unsigned int > fails() { 
        predicate<complete, VALUE_PROXY_TYPE, unsigned int> result(valueProxy);
        result.cycles = cycles;
        result.expectedValue = ~0U;
        result.expectFail = true;
        result.withinMS = withinMS;
        result.withinMSPollingIntervalNS = withinMSPollingIntervalNS;
        result.afterMS = afterMS;
        return result;
      }

      // Getters

      bool get_expect_fail() {
        return expectFail;
      }

      VALUE_TYPE get_expected_value() {
        return expectedValue;
      }

      VALUE_PROXY_TYPE get_value_proxy() {
        return valueProxy;
      }

      int get_cycles() const {
        return cycles;
      }

      int get_within_ms() const {
        return withinMS;
      }

      long long get_within_ms_polling_interval_ns() const {
        return withinMSPollingIntervalNS;
      }

      int get_after_ms() const {
        return afterMS;
      }

      input_clock_proxy* get_clock() const {
        return clock;
      }

    private:
      template<typename V>
      predicate<complete, VALUE_PROXY_TYPE, V> completeWithValue(V value) {
        predicate<complete, VALUE_PROXY_TYPE, V> result(valueProxy);
        result.cycles = cycles;
        result.expectedValue = value;
        result.withinMS = withinMS;
        result.withinMSPollingIntervalNS = withinMSPollingIntervalNS;
        result.afterMS = afterMS;
        return result;
      }

    protected:
      template<typename W, typename X, typename Z> friend class predicate;
      VALUE_PROXY_TYPE valueProxy;
      int cycles;
      int withinMS;
      long long withinMSPollingIntervalNS;
      int afterMS;
      input_clock_proxy* clock;
      VALUE_TYPE expectedValue;
      bool expectFail;
  };
}}
