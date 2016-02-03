/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_CALLBACK_FUNCTIONS_H
#define SCML2_MEMORY_CALLBACK_FUNCTIONS_H

#include <scml2/memory_callback.h>
#include <scml2/transport_adapter.h>
#include <scml2/read_adapter.h>
#include <scml2/null_adapter.h>
#include <scml2/on_write_adapter.h>
#include <scml2/write_adapter.h>
#include <scml2/transport_adapter_tagged.h>
#include <scml2/read_adapter_tagged.h>
#include <scml2/write_adapter_tagged.h>
#include <scml2/untimed_transport_adapter.h>
#include <scml2/untimed_read_adapter.h>
#include <scml2/untimed_write_adapter.h>
#include <scml2/untimed_transport_adapter_tagged.h>
#include <scml2/untimed_read_adapter_tagged.h>
#include <scml2/untimed_write_adapter_tagged.h>
#include <scml2/store_after_read_adapter.h>
#include <scml2/memory_disallow_access_callback.h>
#include <scml2/default_behavior_adapter.h>
#include <scml2/set_on_read_adapter.h>
#include <scml2/write_once_adapter.h>
#include <scml2/word_read_adapter.h>
#include <scml2/word_read_adapter_tagged.h>
#include <scml2/word_write_adapter.h>
#include <scml2/word_write_adapter_tagged.h>
#include <scml2/untimed_word_read_adapter.h>
#include <scml2/untimed_word_read_adapter_tagged.h>
#include <scml2/untimed_word_write_adapter.h>
#include <scml2/untimed_word_write_adapter_tagged.h>
#include <scml2/read_extensions_adapter.h>
#include <scml2/word_read_extensions_adapter.h>
#include <scml2/write_extensions_adapter.h>
#include <scml2/word_write_extensions_adapter.h>
#include <scml2/untimed_read_extensions_adapter.h>
#include <scml2/untimed_word_read_extensions_adapter.h>
#include <scml2/untimed_write_extensions_adapter.h>
#include <scml2/untimed_word_write_extensions_adapter.h>
#include <scml2/read_extensions_adapter_tagged.h>
#include <scml2/word_read_extensions_adapter_tagged.h>
#include <scml2/write_extensions_adapter_tagged.h>
#include <scml2/word_write_extensions_adapter_tagged.h>
#include <scml2/untimed_read_extensions_adapter_tagged.h>
#include <scml2/untimed_word_read_extensions_adapter_tagged.h>
#include <scml2/untimed_write_extensions_adapter_tagged.h>
#include <scml2/untimed_word_write_extensions_adapter_tagged.h>
#include <scml2/post_write_adapter.h>
#include <scml2/post_write_adapter_tagged.h>
#include <scml2/word_access_unroller.h>
#include <scml2/streams.h>
#include <scml2/types.h>

#include <scml2_logging/stream.h>
#include <string>
#include <cassert>

#include <scml2/memory_callback_functions_include.h>

namespace scml2 {


template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_ignore_access(MEM_OBJECT<DT>& mem)
{
  mem.set_callback(new scml2::memory_disallow_access_callback(false));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_ignore_read_access(MEM_OBJECT<DT>& mem)
{
  mem.set_read_callback(new scml2::memory_disallow_access_callback(false));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_ignore_write_access(MEM_OBJECT<DT>& mem)
{
  mem.set_write_callback(new scml2::memory_disallow_access_callback(false));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_disallow_access(MEM_OBJECT<DT>& mem)
{
  mem.set_callback(new scml2::memory_disallow_access_callback(true));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_disallow_read_access(MEM_OBJECT<DT>& mem)
{
  mem.set_read_callback(new scml2::memory_disallow_access_callback(true));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_disallow_write_access(MEM_OBJECT<DT>& mem)
{
  mem.set_write_callback(new scml2::memory_disallow_access_callback(true));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_read_only(MEM_OBJECT<DT>& mem)
{
  set_disallow_write_access(mem);
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_write_only(MEM_OBJECT<DT>& mem)
{
  set_disallow_read_access(mem);
}

}

#endif
