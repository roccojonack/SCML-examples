/*****************************************************************************
 *                   Copyright (C) 1996-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
/*
 * Modifications :
 *
 * Purpose of file : Definition of cnsc clock modeling objects
 *
 */

#ifndef SCML_CLOCK_B_H
#define SCML_CLOCK_B_H

#include "systemc.h"

#include <scml2_logging/stream.h>


/************************************************************************
 * scml_clock.h provided on 02/14/2006 07:11 PM
 * STARTS HERE
 */

/*
 * Copyright (c) 1996-2005 
 * CoWare, Inc.
 * 1732 N. First St. 
 * San Jose, CA, 95112
 * U.S.A.
 * All rights reserved worldwide.
 */

#ifndef SCML__CLOCK_H
#define SCML__CLOCK_H







class scml_clock_if {
public:
  virtual const sc_time& get_period() const=0;
  virtual const sc_time& get_start_time() const=0;
  virtual bool get_posedge_first() const=0;
  virtual double get_duty_cycle() const=0;

  virtual void reset(int n) = 0; // suspends the clock for n cycles
  virtual void enable()=0;     // enable the clock
  virtual void disable()=0;    // disable the clock
  virtual bool disabled()=0;    // is the clock disabled

  virtual void set_duty_cycle(double d)=0;
  virtual void set_period(const  sc_core::sc_time &t)=0;
  virtual void set_posedge_first(bool posedge_first)=0;
  virtual sc_dt::uint64 get_clock_count() = 0;
  // these methods are used to handle derived clocks
  // we have to make sure that master clocks are initializerd before they are being used
  // derived clock need access to the clock properties
  // these methods are not intended to be used by user models
  virtual void deferred_init() = 0; 
  virtual void add_derived(scml_clock_if *derived)=0;
  virtual void master_changed()=0;
  virtual void master_enabled()=0;     // master clock enabled
  virtual void master_disabled()=0;    // master clock disabled

};

class scml_clock_event_cb;

class scml_clock : public sc_core::sc_clock, public scml_clock_if {

  friend class scml_clock_event_cb;
protected:
  mutable scml2::logging::stream mError;
  mutable scml2::logging::stream mWarning;

  scml_clock_event_cb *pos_event_cb;
  scml_clock_event_cb *neg_event_cb;
  scml_clock_event_cb *value_event_cb;
  
  sc_core::sc_event m_reset_event;
  sc_core::sc_time m_reset_start_time;
  sc_core::sc_time m_reset_end_time;
  sc_core::sc_time m_reset_time_remaining;
  sc_core::sc_time m_period_start_time;
  
  sc_core::sc_pvector<scml_clock_if *> m_derived;
  
  sc_core::sc_port_base *m_parent_port;
  scml_clock_if *m_master_clock;
  
  double m_period_multiplier;
  double m_start_multiplier;
  
  sc_dt::uint64 m_clock_count;
  sc_dt::uint64 m_reset_delta;
  
  bool m_posedge_first;
  bool m_sync_on_posedge;
  bool m_deferred_init;
  int m_disabled;
  int m_resetted;
  bool m_user_disabled;
  
  sc_core::sc_signal<bool> * m_stubbed;
  bool m_allow_stub;
  
  
 

  virtual void update();
  

  
public:
  ~scml_clock();
  scml_clock(const char*    name_, scml_clock_if &,double period_multiplier,double start_multiplier);
    
 
  scml_clock(const char*    name_,sc_core::sc_in<bool> &clk,double period_multiplier,double start_multiplier,bool allow_stubbed=false);

  void set_master(scml_clock_if &,double period_multiplier,double start_multiplier);

  void set_master(sc_core::sc_in<bool> &clk,double period_multiplier,double start_multiplier,bool allow_stubbed=false);

  scml_clock();
    
  explicit scml_clock( const char* name_ );
    
  sc_core::sc_signal<bool> * get_stubbed() {
    return m_stubbed;
  }
  scml_clock( const char*    name_,
	     const sc_core::sc_time& period_,
	     double         duty_cycle_ = 0.5,
	     const sc_core::sc_time& start_time_ = sc_core::SC_ZERO_TIME,
	     bool           posedge_first_ = true );

  scml_clock( const char*    name_,
	     double         period_v_,
	     sc_core::sc_time_unit   period_tu_,
	     double         duty_cycle_ = 0.5 ) ;
 
  scml_clock( const char*    name_,
	     double         period_v_,
	     sc_core::sc_time_unit   period_tu_,
	     double         duty_cycle_,
	     double         start_time_v_,
	     sc_core::sc_time_unit   start_time_tu_,
	     bool           posedge_first_ = true ) ; 

  // for backward compatibility with 1.0
  scml_clock( const char*    name_,
	     double         period_,            // in default time units
	     double         duty_cycle_ = 0.5,
	     double         start_time_ = 0.0,  // in default time units
	     bool           posedge_first_ = true ) ;
 		
  virtual void dump(ostream& os) const;

 



  void enable();
  void disable();
  void master_enabled();
  void master_disabled();
  bool disabled();
  void reset(int n);

 
  void end_of_elaboration();



  virtual const sc_core::sc_time& get_period() const;
  virtual const sc_core::sc_time& get_start_time()const;
  virtual bool get_posedge_first()const;
  virtual double get_duty_cycle()const;
  virtual void set_duty_cycle(double d);
  virtual void set_period(const sc_core::sc_time &t);
  virtual void set_posedge_first(bool posedge_first);

  virtual void add_derived(scml_clock_if *derived);
  virtual void master_changed();
  virtual sc_dt::uint64 get_clock_count();

  void set_sync_on_posedge(bool posedge_sync);
private:
  void enable(bool from_master);
  void disable(bool from_master);
  bool enable_local();     // enable the clock
  void disable_local();    // disable the clock
  void restart_clock();
  
  void init_local();
protected:
  void deferred_init();

};
// gated clock 
struct scml_clock_gate : public  ::sc_core::sc_module,public virtual scml_clock_if,public virtual sc_core::sc_signal_in_if<bool> {
  sc_core::sc_in<bool> clk;
  sc_core::sc_in<bool> en;
  SC_HAS_PROCESS(scml_clock_gate);
  scml_clock_gate( ::sc_core::sc_module_name);
   // get the default event
  virtual const sc_core::sc_event& default_event() const { 
    return mClock.default_event();
  }
  
  
  // get the value changed event
  virtual const sc_core::sc_event& value_changed_event() const {
    return mClock.value_changed_event();
  }
  // get the positive edge event
  virtual const sc_core::sc_event& posedge_event() const {
    
    return mClock.posedge_event();
  }
  
  // get the negative edge event
  virtual const sc_core::sc_event& negedge_event() const {
    return mClock.negedge_event();
  }

  
  // read the current value
  virtual const bool& read() const {
    return  mClock.read();
  }

  // get a reference to the current value (for tracing)
  virtual const bool& get_data_ref() const {
    return mClock.get_data_ref();
  }
  
  
  // was there a value changed event?
  virtual bool event() const {
    return mClock.event();
  }
  
  // was there a positive edge event?
  virtual bool posedge() const {
    return mClock.posedge();
  }
  
  // was there a negative edge event?
  virtual bool negedge() const {
    return mClock.negedge();
  }
  
#if SYSTEMC_VERSION < 20060505
  // delayed evaluation
  virtual const sc_core::sc_signal_bool_deval& delayed() const {
    return mClock.delayed();
  }
#endif

  virtual void reset(int n); // suspends the clock for n cycles
  virtual void enable();     // enable the clock
  virtual void disable();    // disable the clock
  virtual void master_enabled() {
    mClock.master_enabled();
  }
  virtual void master_disabled() {
    mClock.master_disabled();
  }
  virtual void set_duty_cycle(double d);
  virtual void set_period(const sc_core::sc_time &t);
  virtual void set_posedge_first(bool posedge_first);
  virtual void master_changed() {
    mClock.master_changed();
  } 
  virtual sc_dt::uint64 get_clock_count() {
    return mClock.get_clock_count();
  }
  virtual bool disabled() {
    return mClock.disabled();
  }
  virtual const sc_core::sc_time& get_period() const {
    return mClock.get_period();
  }
  virtual const sc_core::sc_time& get_start_time() const {
    return mClock.get_start_time();
  }
  virtual bool get_posedge_first() const {
    return mClock.get_posedge_first();
  }
  virtual double get_duty_cycle() const {
    return mClock.get_duty_cycle();
  }
  void deferred_init() {
    static_cast<scml_clock_if *>(&mClock)->deferred_init();
  }
  void add_derived(scml_clock_if *derived) {
    mClock.add_derived(derived);
  }
  private:
  mutable scml2::logging::stream mWarning;
  scml_clock mClock;
  void enable_proc();
  
};


#endif // SCML__CLOCK_H

/************************************************************************
 * scml_clock.h provided on 02/14/2006 07:11 PM
 * ENDS HERE
 */


#endif // SCML_CLOCK_B_H
