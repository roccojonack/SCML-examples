/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_CALLBACK_OBSERVER_OWNER_H
#define SCML2_BITFIELD_CALLBACK_OBSERVER_OWNER_H

#include <scml2/bitfield_callback_observer.h>
#include <scml2/types.h>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename DT>
class bitfield_callback_observer_owner {
public:
  virtual ~bitfield_callback_observer_owner();
  virtual void handle_callback_changed(bitfield_callback_observer<DT>* o,
                                       access_type type,
                                       access_mode mode) = 0;

  virtual void handle_begin_callback(bitfield_callback_observer<DT>* o,
                                     const DT* data,
                                     const DT* bitMask,
                                     access_type type,
                                     access_mode mode,
                                     unsigned int id) = 0;
  virtual void handle_end_callback(bitfield_callback_observer<DT>* o,
                                   const DT* data,
                                   unsigned int id) = 0;
};

template <typename DT>
inline
bitfield_callback_observer_owner<DT>::
~bitfield_callback_observer_owner()
{
}

}

#endif
