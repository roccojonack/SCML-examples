/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_PAIR_SIGNAL_H
#define SCML2_PAIR_SIGNAL_H

#include <ostream>
#include <systemc>
#include <map>
#include <string>

namespace sc_core {

template <typename T1, typename T2>
inline
::std::ostream&
operator<<(::std::ostream& os, const std::pair<T1,T2>& a)
{
  os << "{" << a.first << "," << a.second << "}";
  return os;
}

template <class T1, class T2>
inline
::std::ostream&
operator << (::std::ostream& os, const std::pair<T1,T2>* a)
{
  os << "{" << a->first << "," << a->second << "}";
  return os;
}

template <class T1, class T2> 
inline void
sc_trace(sc_trace_file* tf , const std::pair<T1,T2>& cp, const std::string& name)
{
  sc_trace(tf, cp.first, name + ".first");
  sc_trace(tf, cp.second, name + ".second");
}

template <class T1, class T2> 
inline void
sc_trace(sc_trace_file* tf , const std::pair<T1,T2>* cp, const std::string& name )
{
  sc_trace<T1,T2>(tf, *cp, name);
}

}

#endif

