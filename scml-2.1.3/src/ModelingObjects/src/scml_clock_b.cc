/*****************************************************************************
 *                   Copyright (C) 1996-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/


#include "systemc.h"
#include "scml_clock_b.h"
#if SYSTEMC_VERSION < 20060505
#include "sysc/kernel/sc_process_base.h"
#endif
#include <scml2_logging/severity.h>

/************************************************************************
 * scml_clock.cc on 02/14/2006 07:11 PM
 */


using namespace std;



void scml_clock::init_local() {
  m_parent_port = NULL;
  m_master_clock = NULL;
  m_period_multiplier = 1;
  m_start_multiplier = 0;
  m_posedge_first = true;
  m_deferred_init = false;    
  m_disabled=0;
  m_resetted = 0;
  m_clock_count = 0;
  m_reset_delta = 0;
  m_stubbed = 0;
  m_allow_stub = false;
  m_user_disabled = false;
  m_sync_on_posedge = true;
}

// based on current time and clock attributes find the last posedge
static sc_time get_last_posedge(const sc_time &start_time,const sc_time &period,bool posedge_first,double duty_cycle) {
  const sc_time & curr_time = sc_get_curr_simcontext()->time_stamp();
  if (curr_time >= start_time) {
    sc_time ellapsed = curr_time-start_time;
    sc_dt::uint64 dt =  ellapsed.value()% period.value();
    if (posedge_first) {
      return sc_time(curr_time.value()-dt,false);
    } else {
      sc_time negedge_time = period *duty_cycle;
      sc_time posedge_time = period - negedge_time;
      if ( posedge_time.value() <= dt) {
	return curr_time + posedge_time - sc_time(dt,false);
      } else {
	return curr_time - negedge_time - sc_time(dt,false);
      }
    }
  } else {
    return SC_ZERO_TIME;
  }
}
// based on current time and clock attributes find the last negedge
static sc_time get_last_negedge(const sc_time &start_time,const sc_time &period,bool posedge_first,double duty_cycle) {
  const sc_time & curr_time = sc_get_curr_simcontext()->time_stamp();
  if (curr_time >= start_time) {
    sc_time ellapsed = curr_time-start_time;
    sc_dt::uint64 dt =  ellapsed.value()% period.value();
    if (!posedge_first) {
      return sc_time(curr_time.value()-dt,false);
    } else {
      sc_time negedge_time = period *duty_cycle;
      sc_time posedge_time = period - negedge_time;
      if ( negedge_time.value() <= dt) {
	return curr_time + negedge_time - sc_time(dt,false);
      } else {
	return curr_time - posedge_time - sc_time(dt,false);
      }
    }
  } else {
    return SC_ZERO_TIME;
  }
}
 
// check if the clock is disabled
bool scml_clock::disabled(){ return m_disabled || m_resetted; }

// get the last posedge of the clock
static sc_time get_last_posedge(scml_clock_if *clk) {
  return get_last_posedge(clk->get_start_time(),clk->get_period(),clk->get_posedge_first(),clk->get_duty_cycle());

}

// get the last posedge of the clock
static sc_time get_last_negedge(scml_clock_if *clk) {
  return get_last_negedge(clk->get_start_time(),clk->get_period(),clk->get_posedge_first(),clk->get_duty_cycle());
}

// constructors
scml_clock::scml_clock(const char *name_,scml_clock_if &intf,double period_multiplier,double start_multiplier):
  sc_clock(name_),
  mError(this->name(), scml2::logging::severity::error()),
  mWarning(this->name(), scml2::logging::severity::warning())
{
  init_local();
  set_master(intf,period_multiplier,start_multiplier);
}
    
scml_clock::scml_clock(const char *name_,sc_in<bool> &clk,double period_multiplier,double start_multiplier,bool allow_stub):
  sc_clock(name_),
  mError(this->name(), scml2::logging::severity::error()),
  mWarning(this->name(), scml2::logging::severity::warning())
{
  init_local();
  set_master(clk,period_multiplier,start_multiplier,allow_stub);
}
  
void scml_clock::set_master(scml_clock_if &intf,double period_multiplier,double start_multiplier) {
  if (simcontext()->elaboration_done()) {
    SCML2_LOG(mError)
      << "set_master can only be done during construction!" << std::endl;
  }
  m_master_clock = &intf;
  m_deferred_init = true;
  m_period_multiplier =period_multiplier;
  m_start_multiplier = start_multiplier;

}

void scml_clock::set_master(sc_in<bool> &clk,double period_multiplier,double start_multiplier,bool allow_stub) {
  if (simcontext()->elaboration_done()) {
    SCML2_LOG(mError)
      << "set_master can only be done during construction!" << std::endl;
  }
  m_allow_stub = allow_stub;
  m_deferred_init = true;
  m_parent_port = &clk;
  m_period_multiplier =period_multiplier;
  m_start_multiplier = start_multiplier;

}

scml_clock::scml_clock() : 
  sc_clock(),
  mError(this->name(), scml2::logging::severity::error()),
  mWarning(this->name(), scml2::logging::severity::warning())
{
  init_local();
}
    
scml_clock::scml_clock( const char* name_ ) :
  sc_clock(name_),
  mError(this->name(), scml2::logging::severity::error()),
  mWarning(this->name(), scml2::logging::severity::warning())
{
  init_local();
}

scml_clock::scml_clock( const char*    name_,
		      const sc_time& period_,
		      double         duty_cycle_ ,
		      const sc_time& start_time_ ,
		      bool           posedge_first_ ):
  sc_clock(name_,period_,duty_cycle_,start_time_,posedge_first_),
  mError(this->name(), scml2::logging::severity::error()),
  mWarning(this->name(), scml2::logging::severity::warning())
{
  init_local();
  m_posedge_first = posedge_first_;
}
 
scml_clock::scml_clock( const char*    name_,
		      double         period_v_,
		      sc_time_unit   period_tu_,
		      double         duty_cycle_  ) :
  sc_clock(name_, period_v_,period_tu_,duty_cycle_ ),
  mError(this->name(), scml2::logging::severity::error()),
  mWarning(this->name(), scml2::logging::severity::warning())
{
  init_local();
}

scml_clock::scml_clock( const char*    name_,
		      double         period_v_,
		      sc_time_unit   period_tu_,
		      double         duty_cycle_,
		      double         start_time_v_,
		      sc_time_unit   start_time_tu_,
		      bool           posedge_first_  ) : 
  sc_clock(name_,period_v_,period_tu_,duty_cycle_,start_time_v_, start_time_tu_,posedge_first_),
  mError(this->name(), scml2::logging::severity::error()),
  mWarning(this->name(), scml2::logging::severity::warning())
{
  init_local();
  m_posedge_first = posedge_first_;
}
 
// for backward compatibility with 1.0
scml_clock::scml_clock( const char*    name_,
		      double         period_,            // in default time units
		      double         duty_cycle_ ,
		      double         start_time_ ,  // in default time units
		      bool           posedge_first_  ) : 
  sc_clock(name_,period_,duty_cycle_,start_time_,posedge_first_),
  mError(this->name(), scml2::logging::severity::error()),
  mWarning(this->name(), scml2::logging::severity::warning())
{
  init_local();
  m_posedge_first = posedge_first_;
}


// callback in case the master clock's attribute have changed
void scml_clock::master_changed() {
  if (m_master_clock) {
    sc_time new_period = m_master_clock->get_period() * m_period_multiplier;
    sc_time new_start_time = m_sync_on_posedge ? get_last_posedge(m_master_clock):  get_last_negedge(m_master_clock);
    if (new_period != m_period || new_start_time != m_start_time) {
      set_period(new_period);
    }
  }
}

// get the period
const sc_time& scml_clock::get_period() const {
  return m_period;
}

// get the start time
const sc_time& scml_clock::get_start_time() const {
  return m_start_time;
}

// get the posedge_first 
bool scml_clock::get_posedge_first() const {
  return m_posedge_first;
}
// get the current clock count
sc_dt::uint64 scml_clock::get_clock_count() {
  return m_clock_count;
}

// get the duty cycle
double scml_clock::get_duty_cycle() const {
  return m_duty_cycle;
}

// update the clock value : gate with the disabled signal
void scml_clock::update() {
  bool tmp = m_new_val;
  if (m_resetted) {
    if (m_new_val && !m_cur_val && m_reset_delta != sc_delta_count()) {
      
      if (--m_resetted) {
	m_new_val = false;
      }
    } else {	
      m_new_val = false;
    }
  } else {
    m_new_val &= !m_disabled;
  }
  if (m_new_val && !m_cur_val)
    m_clock_count++;
  sc_signal<bool>::update();
  m_new_val = tmp;
}

// dump the state
void scml_clock::dump(ostream& os) const {
  os << " scml_clock : " << name() << ":\n"
     << "    m_start_time : " << m_start_time << "\n"
     << "    m_period : " << m_period << "\n"
     << "    m_duty_cycle : " << m_duty_cycle << "\n"
     << "    m_posedge_first : " << m_posedge_first << "\n"
     << "    disabled : " << m_disabled << "\n";
}
// enable the clock from_master indicates if this is the master clock being enabled
void scml_clock::enable(bool from_master) {
  if (!from_master) {
    if (!m_user_disabled) {
      return;
    }
    m_user_disabled = false;
  }
  for (int i=0,size =m_derived.size();i<size;i++) {
    m_derived[i]->master_enabled();
  }
  enable_local();
  request_update();

}
// implementation 
bool scml_clock::enable_local() {

  m_disabled--;
  if (m_resetted) {
    return false;
  }
  if (m_disabled) {
    return false;
  }
  return read();
 
}

// initialize the clock in case of derived clock
void scml_clock::end_of_elaboration() {
  if (m_deferred_init) {
    deferred_init();
  }
}

// set up derived clock
void scml_clock::deferred_init() {
  if (m_deferred_init) {
    m_deferred_init = false;
    // make sure the parent is initialized as well
    if (!m_master_clock) {
      m_master_clock = dynamic_cast<scml_clock_if *>(m_parent_port->get_interface());
      if (!m_master_clock) {
	if (m_allow_stub && dynamic_cast<sc_signal<bool> *>(m_parent_port->get_interface())) {
	  m_stubbed = dynamic_cast<sc_signal<bool> *>(m_parent_port->get_interface());
	  return;
	}
        SCML2_LOG(mWarning)
	  << "Derived clocks must be derived from a channel that implements scml_clock_if!"
	  << " Detected for clock : \"" << name() << " derived via port \"" << m_parent_port->name()
          << std::endl;
	return;
      }
    }
      
    m_master_clock->deferred_init();
    m_master_clock->add_derived(this);
      
    m_period = m_master_clock->get_period() * m_period_multiplier;
    m_start_time =  m_master_clock->get_start_time();
    // adjust for the next edge if necessary
    
    m_duty_cycle = m_master_clock->get_duty_cycle();
    if ((m_master_clock->get_posedge_first() && !m_sync_on_posedge) || (!m_master_clock->get_posedge_first() && m_sync_on_posedge)) {
      m_start_time += m_period * m_duty_cycle; // start at the right edge
    }
    m_start_time= m_start_time + m_master_clock->get_period()* m_start_multiplier;
    restart_clock();
  }
}

// set the duty cycle
void scml_clock::set_duty_cycle(double d) {
  if (d != m_duty_cycle) {
    m_duty_cycle = d;
    restart_clock();
    // notify all derived
    for (int i=0,size =m_derived.size();i<size;i++) {
      m_derived[i]->master_changed();
    }
  }
  
}

void scml_clock::restart_clock() {
  const sc_time & curr_time = simcontext()->time_stamp();
  if (m_start_time < curr_time) {
    if (m_master_clock) {
      // find the last positive edge of the master clock
      m_start_time =  m_sync_on_posedge ? get_last_posedge(m_master_clock): get_last_negedge(m_master_clock);
      /* -- us this if we wantto sync on the next coming sync edge
	while (m_start_time<curr_time) {
	m_start_time += m_master_clock->get_period();
	}
      */
    } else {
      m_start_time = curr_time;
    }
  }

  bool tmp_cur = m_cur_val;
  bool tmp_new = m_new_val;
  init(m_period,m_duty_cycle,m_start_time,m_posedge_first);
  m_cur_val = tmp_cur;
  m_new_val = tmp_new;


  m_next_posedge_event.cancel();
  m_next_negedge_event.cancel();
  sc_time tmp = m_start_time;
  bool pefirst = m_posedge_first;
  while (tmp <  curr_time) {
    tmp += pefirst ? m_negedge_time :m_posedge_time;
    pefirst = !pefirst;
  }
  if( pefirst) {
    // posedge first
    // find the first posedge
    m_next_posedge_event.notify(tmp-curr_time );
  } else {
    // negedge first
    m_next_negedge_event.notify(tmp-curr_time );
  }
  request_update();
  if (m_start_time <  curr_time) {
    sc_signal<bool>::write(m_posedge_first);
  }

 
}
// sync 
void scml_clock::set_sync_on_posedge(bool posedge_sync) {
  if (simcontext()->elaboration_done()) {
    SCML2_LOG(mError)
      << "set_sync_on_posedge can only be called during construction!" << std::endl;
  }
  m_sync_on_posedge = posedge_sync;
}

// set the posedge first attribute
void scml_clock::set_posedge_first(bool posedge_first) {
  if (m_posedge_first != posedge_first) {
    m_posedge_first = posedge_first;
    restart_clock();
    for (int i=0,size =m_derived.size();i<size;i++) {
      m_derived[i]->master_changed();
    }
  }

}
// set the clock period
void scml_clock::set_period(const sc_time &t) {
  // fix the period start time
  if (t != m_period) {
    m_period = t;
    restart_clock();
    for (int i=0,size =m_derived.size();i<size;i++) {
      m_derived[i]->master_changed();
    }
  }
}
// implementation
void scml_clock::disable_local() { // disable only this clock
  m_disabled++;
}

// disable the clock
void scml_clock::disable() {
  disable(false);
}
// enable the clock
void scml_clock::enable() {
  enable(false);
  
}
// master was disabled
void scml_clock::master_disabled() {
  disable(true);
}
// master was enabled
void scml_clock::master_enabled() {
  enable(true);
}
// disable implementation
void scml_clock::disable(bool from_master) {
  if (!from_master) {
    if (m_user_disabled) {
      return;
    }
    m_user_disabled = true;
  }
  for (int i=0,size =m_derived.size();i<size;i++) {
    m_derived[i]->master_disabled();
  }
  disable_local();
  /*  if (read()) {
    m_cur_val = true; // force the value change m_cur_val could be out of sync
    }*/
  request_update();
}    
// reset the clock for n cycles
void scml_clock::reset(int n) {
  m_resetted = n+1;
  m_reset_delta = sc_delta_count();
  request_update();

}



// add a derived clock

void scml_clock::add_derived(scml_clock_if *derived) {
  m_derived.push_back(derived);
}

// destructor  
scml_clock::~scml_clock() {
}

// reset not available
void scml_clock_gate::reset(int n) {
  SCML2_LOG(mWarning)
    << "scml_clock_gate::reset not supported" << std::endl;
}

// enable
void scml_clock_gate::enable() {
  SCML2_LOG(mWarning)
    << "scml_clock_gate needs to be disabled through the en port" << std::endl;
}
void scml_clock_gate::disable() {
  SCML2_LOG(mWarning)
    << "scml_clock_gate needs to be enabled through the en port" << std::endl;
}
void scml_clock_gate::set_duty_cycle(double d) {
  SCML2_LOG(mWarning)
    << "set_duty_cycle not supporetd for scml_clock_gate" << std::endl;

}
void scml_clock_gate::set_period(const sc_time &t) {
  SCML2_LOG(mWarning)
    << "set_period not supported for scml_clock_gate" << std::endl;
}

void scml_clock_gate::set_posedge_first(bool posedge_first) {
  SCML2_LOG(mWarning)
    << "set_posedge_first not supported for scml_clock_gate" << std::endl;
}

// constructor
scml_clock_gate::scml_clock_gate(sc_core::sc_module_name) :
  mWarning(this->name(), scml2::logging::severity::warning()),
  mClock("clock")
{
  SC_METHOD(enable_proc);
  sensitive << en;
  mClock.set_master(clk,1,1);
  
}

// enable process
void scml_clock_gate::enable_proc() {
  if (en.read()) {
    mClock.enable();
  } else {
    mClock.disable();
  }
}

