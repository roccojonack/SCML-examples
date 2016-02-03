/*****************************************************************************
 *                   Copyright (C) 1996-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#ifndef SCML2_THREAD_POOL_H
#define SCML2_THREAD_POOL_H

// FIXME: wrapper to make OSCI scml compile without snps_sc_thread_pool.h
#ifdef CWRSCML2_DEFINED

#include <scext/runtime/snps_sc_thread_pool.h>

namespace scml2 {
using namespace snps::sc;
}

#else

#include <systemc>
#include <sysc/kernel/sc_dynamic_processes.h>

namespace scml2 {

template <class T>
class worker_thread {
public:
  sc_core::sc_event mWakeup;

  worker_thread(const T& function) :
    mFunction(function)
  {
  }

  void single_shot_do_work() {
    sc_core::wait(mWakeup);
    mFunction();    
    delete this;
  }

private:
  T mFunction;
};
  
template <class T>
class thread_pool {
public:
  worker_thread<T>* spawn_thread(const T& function)
  {       
    worker_thread<T>* t = new worker_thread<T>(function);
    sc_core::sc_spawn(sc_bind(&worker_thread<T>::single_shot_do_work, t),
  		      sc_core::sc_gen_unique_name("sc_worker_thread"));
    return t;
  }

};


template <class T>
sc_core::sc_event& spawn_thread_pooled(const T& function)
{
  static thread_pool<T> thread_pool;
  
  worker_thread<T>* thread = thread_pool.spawn_thread(function); 
  return thread->mWakeup;
}

}

#endif

#endif
