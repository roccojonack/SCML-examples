/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_DEBUG_CALLBACK_FUNCTIONS_H
#define SCML2_BITFIELD_DEBUG_CALLBACK_FUNCTIONS_H

#include <scml2/bitfield_debug_read_callback.h>
#include <scml2/bitfield_debug_write_callback.h>
#include <scml2/bitfield_debug_read_adapter.h>
#include <scml2/bitfield_debug_write_adapter.h>
#include <scml2/bitfield_debug_read_adapter_tagged.h>
#include <scml2/bitfield_debug_write_adapter_tagged.h>
#include <scml2/bitfield_debug_mask_read_adapter.h>
#include <scml2/bitfield_debug_mask_write_adapter.h>
#include <scml2/bitfield_debug_mask_read_adapter_tagged.h>
#include <scml2/bitfield_debug_mask_write_adapter_tagged.h>
#include <scml2/bitfield_disallow_debug_read_access_callback.h>
#include <scml2/bitfield_disallow_debug_write_access_callback.h>
#include <scml2/bitfield.h>

#include <string>
#include <cassert>

namespace scml2 {

template <typename DT, typename C>
inline
void
set_debug_read_callback(bitfield<DT>& bitfield,
                        C* c,
                        typename bitfield_debug_read_adapter<DT, C>::CallbackType cb,
                        const std::string& cbName)
{
  assert(c);
  bitfield.set_debug_read_callback(
    create_bitfield_debug_read_callback<DT>(
      create_bitfield_debug_read_adapter<DT>(*c, cb),
      cbName));
}

template <typename DT, typename C>
inline
void
set_debug_write_callback(bitfield<DT>& bitfield,
                         C* c,
                         typename bitfield_debug_write_adapter<DT, C>::CallbackType cb,
                         const std::string& cbName)
{
  assert(c);
  bitfield.set_debug_write_callback(
    create_bitfield_debug_write_callback<DT>(
      create_bitfield_debug_write_adapter<DT>(*c, cb),
      cbName));
}

template <typename DT, typename C>
inline
void
set_debug_read_callback(bitfield<DT>& bitfield,
                        C* c,
                        typename bitfield_debug_read_adapter_tagged<DT, C>::CallbackType cb,
                        const std::string& cbName,
                        int id)
{
  assert(c);
  bitfield.set_debug_read_callback(
    create_bitfield_debug_read_callback<DT>(
      create_bitfield_debug_read_adapter<DT>(*c, cb, id),
      cbName));
}

template <typename DT, typename C>
inline
void
set_debug_write_callback(bitfield<DT>& bitfield,
                         C* c,
                         typename bitfield_debug_write_adapter_tagged<DT, C>::CallbackType cb,
                         const std::string& cbName,
                         int id)
{
  assert(c);
  bitfield.set_debug_write_callback(
    create_bitfield_debug_write_callback<DT>(
      create_bitfield_debug_write_adapter<DT>(*c, cb, id),
      cbName));
}

template <typename DT, typename C>
inline
void
set_debug_read_callback(bitfield<DT>& bitfield,
                        C* c,
                        typename bitfield_debug_mask_read_adapter<DT, C>::CallbackType cb,
                        const std::string& cbName)
{
  assert(c);
  bitfield.set_debug_read_callback(
    create_bitfield_debug_read_callback<DT>(
      create_bitfield_debug_read_adapter<DT>(*c, cb),
      cbName));
}

template <typename DT, typename C>
inline
void
set_debug_write_callback(bitfield<DT>& bitfield,
                         C* c,
                         typename bitfield_debug_mask_write_adapter<DT, C>::CallbackType cb,
                         const std::string& cbName)
{
  assert(c);
  bitfield.set_debug_write_callback(
    create_bitfield_debug_write_callback<DT>(
      create_bitfield_debug_write_adapter<DT>(*c, cb),
      cbName));
}

template <typename DT, typename C>
inline
void
set_debug_read_callback(bitfield<DT>& bitfield,
                        C* c,
                        typename bitfield_debug_mask_read_adapter_tagged<DT, C>::CallbackType cb,
                        const std::string& cbName,
                        int id)
{
  assert(c);
  bitfield.set_debug_read_callback(
    create_bitfield_debug_read_callback<DT>(
      create_bitfield_debug_read_adapter<DT>(*c, cb, id),
      cbName));
}

template <typename DT, typename C>
inline
void
set_debug_write_callback(bitfield<DT>& bitfield,
                         C* c,
                         typename bitfield_debug_mask_write_adapter_tagged<DT, C>::CallbackType cb,
                         const std::string& cbName,
                         int id)
{
  assert(c);
  bitfield.set_debug_write_callback(
    create_bitfield_debug_write_callback<DT>(
      create_bitfield_debug_write_adapter<DT>(*c, cb, id),
      cbName));
}

template <typename DT>
inline
void
set_disallow_debug_read_access(bitfield<DT>& bitfield)
{
  bitfield.set_debug_read_callback(new scml2::bitfield_disallow_debug_read_access_callback<DT>());
}

template <typename DT>
inline
void
set_disallow_debug_write_access(bitfield<DT>& bitfield)
{
  bitfield.set_debug_write_callback(new scml2::bitfield_disallow_debug_write_access_callback<DT>());
}

template <typename DT>
inline
void
set_disallow_debug_access(bitfield<DT>& bitfield)
{
  set_disallow_debug_read_access(bitfield);
  set_disallow_debug_write_access(bitfield);
}

}

#endif
