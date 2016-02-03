/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_BEHAVIOR_FUNCTIONS_H
#define SCML2_MEMORY_BEHAVIOR_FUNCTIONS_H

#include <scml2/memory_index_reference.h>

namespace scml2 {

template <typename DT, template <typename> class MEM_OBJECT>
void clear_on_write_1(MEM_OBJECT<DT>& object,
                      const DT& data,
                      const DT& mask)
{
  object &= ~(data & mask);
}

template <typename DT, template <typename> class MEM_OBJECT>
void clear_on_write_0(MEM_OBJECT<DT>& object,
                      const DT& data,
                      const DT& mask)
{
  object &= ~(~data & mask);
}

template <typename DT, template <typename> class MEM_OBJECT>
void set_on_write_1(MEM_OBJECT<DT>& object,
                    const DT& data,
                    const DT& mask)
{
  object |= data & mask;
}

template <typename DT, template <typename> class MEM_OBJECT>
void set_on_write_0(MEM_OBJECT<DT>& object,
                    const DT& data,
                    const DT& mask)
{
  object |= ~data & mask;
}

template <typename DT, template <typename> class MEM_OBJECT>
void invert_on_write_1(MEM_OBJECT<DT>& object,
                       const DT& data,
                       const DT& mask)
{
  object ^= data & mask;
}

template <typename DT, template <typename> class MEM_OBJECT>
void invert_on_write_0(MEM_OBJECT<DT>& object,
                       const DT& data,
                       const DT& mask)
{
  object ^= ~data & mask;
}

// temporary memory_index_reference can not be passed by reference
template <typename DT>
void clear_on_write_1(memory_index_reference<DT> object,
                      const DT& data,
                      const DT& mask)
{
  clear_on_write_1<DT, memory_index_reference>(object, data, mask);
}

template <typename DT>
void clear_on_write_0(memory_index_reference<DT> object,
                      const DT& data,
                      const DT& mask)
{
  clear_on_write_0<DT, memory_index_reference>(object, data, mask);
}

template <typename DT>
void set_on_write_1(memory_index_reference<DT> object,
                    const DT& data,
                    const DT& mask)
{
  set_on_write_1<DT, memory_index_reference>(object, data, mask);
}

template <typename DT>
void set_on_write_0(memory_index_reference<DT> object,
                    const DT& data,
                    const DT& mask)
{
  set_on_write_0<DT, memory_index_reference>(object, data, mask);
}

template <typename DT>
void invert_on_write_1(memory_index_reference<DT> object,
                       const DT& data,
                       const DT& mask)
{
  invert_on_write_1<DT, memory_index_reference>(object, data, mask);
}

template <typename DT>
void invert_on_write_0(memory_index_reference<DT> object,
                       const DT& data,
                       const DT& mask)
{
  invert_on_write_0<DT, memory_index_reference>(object, data, mask);
}

}

#endif
