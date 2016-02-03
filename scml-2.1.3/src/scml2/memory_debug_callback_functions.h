/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_DEBUG_CALLBACK_FUNCTIONS_H
#define SCML2_MEMORY_DEBUG_CALLBACK_FUNCTIONS_H

#include <scml2/memory_debug_callback.h>
#include <scml2/debug_transport_adapter.h>
#include <scml2/debug_transport_adapter_tagged.h>
#include <scml2/memory_disallow_debug_access_callback.h>

#include <string>
#include <cassert>

namespace scml2 {

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_debug_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename debug_transport_adapter<C>::CallbackType cb,
                   const std::string& cbName)
{
  assert(c);
  mem.set_debug_callback(
    create_memory_debug_callback(
      create_debug_transport_adapter(*c, cb),
      cbName));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_debug_read_callback(MEM_OBJECT<DT>& mem,
                        C* c,
                        typename debug_transport_adapter<C>::CallbackType cb,
                        const std::string& cbName)
{
  assert(c);
  mem.set_debug_read_callback(
    create_memory_debug_callback(
      create_debug_transport_adapter(*c, cb),
      cbName));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_debug_write_callback(MEM_OBJECT<DT>& mem,
                         C* c,
                         typename debug_transport_adapter<C>::CallbackType cb,
                         const std::string& cbName)
{
  assert(c);
  mem.set_debug_write_callback(
    create_memory_debug_callback(
      create_debug_transport_adapter(*c, cb),
      cbName));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_debug_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename debug_transport_adapter_tagged<C>::CallbackType cb,
                   const std::string& cbName,
                   int id)
{
  assert(c);
  mem.set_debug_callback(
    create_memory_debug_callback(
      create_debug_transport_adapter(*c, cb, id),
      cbName));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_debug_read_callback(MEM_OBJECT<DT>& mem,
                        C* c,
                        typename debug_transport_adapter_tagged<C>::CallbackType cb,
                        const std::string& cbName,
                        int id)
{
  assert(c);
  mem.set_debug_read_callback(
    create_memory_debug_callback(
      create_debug_transport_adapter(*c, cb, id),
      cbName));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_debug_write_callback(MEM_OBJECT<DT>& mem,
                         C* c,
                         typename debug_transport_adapter_tagged<C>::CallbackType cb,
                         const std::string& cbName,
                         int id)
{
  assert(c);
  mem.set_debug_write_callback(
    create_memory_debug_callback(
      create_debug_transport_adapter(*c, cb, id),
      cbName));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_disallow_debug_access(MEM_OBJECT<DT>& mem)
{
  mem.set_debug_callback(new scml2::memory_disallow_debug_access_callback());
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_disallow_debug_read_access(MEM_OBJECT<DT>& mem)
{
  mem.set_debug_read_callback(new scml2::memory_disallow_debug_access_callback());
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_disallow_debug_write_access(MEM_OBJECT<DT>& mem)
{
  mem.set_debug_write_callback(new scml2::memory_disallow_debug_access_callback());
}

}

#endif
