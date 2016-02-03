/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_ROUTER_H
#define SCML2_ROUTER_H

#include <scml2/router_base.h>
#include <scml2/utils.h>

#include <tlm.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT>
class router : public router_base
{
public:
  typedef DT data_type;

public:
  router(const std::string& name, unsigned long long size);
  ~router();

  using router_base::put_with_triggering_callbacks;
  using router_base::get_with_triggering_callbacks;

  tlm::tlm_response_status
  put_with_triggering_callbacks(unsigned long long index,
                                const DT& data,
                                unsigned int size,
                                unsigned int offset,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  put_with_triggering_callbacks(unsigned long long index,
                                const DT& data,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  get_with_triggering_callbacks(unsigned long long index,
                                DT& data,
                                unsigned int size,
                                unsigned int offset,
                                sc_core::sc_time& t);
  tlm::tlm_response_status
  get_with_triggering_callbacks(unsigned long long index,
                                DT& data,
                                sc_core::sc_time& t);

  using router_base::put_debug_with_triggering_callbacks;
  using router_base::get_debug_with_triggering_callbacks;

  unsigned int
  put_debug_with_triggering_callbacks(unsigned long long index,
                                      const DT& data,
                                      unsigned int size,
                                      unsigned int offset);
  unsigned int
  put_debug_with_triggering_callbacks(unsigned long long index,
                                      const DT& data);
  unsigned int
  get_debug_with_triggering_callbacks(unsigned long long index,
                                      DT& data,
                                      unsigned int size,
                                      unsigned int offset);
  unsigned int
  get_debug_with_triggering_callbacks(unsigned long long index,
                                      DT& data);
};

template <typename DT>
inline
tlm::tlm_response_status
router<DT>::
put_with_triggering_callbacks(unsigned long long index,
                              const DT& data,
                              unsigned int size,
                              unsigned int offset,
                              sc_core::sc_time& t)
{
  return put_with_triggering_callbacks(index_to_address<DT>(index) + offset,
                                       dt_to_array<DT>(data),
                                       size,
                                       t);
}

template <typename DT>
inline
tlm::tlm_response_status
router<DT>::
put_with_triggering_callbacks(unsigned long long index,
                              const DT& data,
                              sc_core::sc_time& t)
{
  return put_with_triggering_callbacks(index,
                                       data,
                                       sizeOf<DT>(),
                                       0,
                                       t);
}

template <typename DT>
inline
tlm::tlm_response_status
router<DT>::
get_with_triggering_callbacks(unsigned long long index,
                              DT& data,
                              unsigned int size,
                              unsigned int offset,
                              sc_core::sc_time& t)
{
  return get_with_triggering_callbacks(index_to_address<DT>(index) + offset,
                                       dt_from_array<DT>(data, size),
                                       size,
                                       t);
}

template <typename DT>
inline
tlm::tlm_response_status
router<DT>::
get_with_triggering_callbacks(unsigned long long index,
                              DT& data,
                              sc_core::sc_time& t)
{
  return get_with_triggering_callbacks(index,
                                       data,
                                       sizeOf<DT>(),
                                       0,
                                       t);
}

template <typename DT>
inline
unsigned int
router<DT>::
put_debug_with_triggering_callbacks(unsigned long long index,
                                    const DT& data,
                                    unsigned int size,
                                    unsigned int offset)
{
  return put_debug_with_triggering_callbacks(index_to_address<DT>(index) + offset,
                                             dt_to_array<DT>(data),
                                             size);
}

template <typename DT>
inline
unsigned int
router<DT>::
put_debug_with_triggering_callbacks(unsigned long long index,
                                    const DT& data)
{
  return put_debug_with_triggering_callbacks(index,
                                             data,
                                             sizeOf<DT>(),
                                             0);
}

template <typename DT>
inline
unsigned int
router<DT>::
get_debug_with_triggering_callbacks(unsigned long long index,
                                    DT& data,
                                    unsigned int size,
                                    unsigned int offset)
{
  return get_debug_with_triggering_callbacks(index_to_address<DT>(index) + offset,
                                             dt_from_array<DT>(data, size),
                                             size);
}

template <typename DT>
inline
unsigned int
router<DT>::
get_debug_with_triggering_callbacks(unsigned long long index,
                                    DT& data)
{
  return get_debug_with_triggering_callbacks(index,
                                             data,
                                             sizeOf<DT>(),
                                             0);
}

}

#endif
