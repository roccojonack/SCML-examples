// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

#ifndef SCML2_H
#define SCML2_H

#include "abstraction_level_switch_observer.h"
#include "autosync_callback.h"
#include "bitfield.h"
#include "bitfield_autosync_read_callback.h"
#include "bitfield_autosync_write_callback.h"
#include "bitfield_base.h"
#include "bitfield_callback_base.h"
#include "bitfield_callback_functions.h"
#include "bitfield_callback_functions_include.h"
#include "bitfield_callback_observer.h"
#include "bitfield_callback_observer_owner.h"
#include "bitfield_callback_observers.h"
#include "bitfield_debug_callback_base.h"
#include "bitfield_debug_callback_functions.h"
#include "bitfield_debug_mask_read_adapter.h"
#include "bitfield_debug_mask_read_adapter_tagged.h"
#include "bitfield_debug_mask_write_adapter.h"
#include "bitfield_debug_mask_write_adapter_tagged.h"
#include "bitfield_debug_read_adapter.h"
#include "bitfield_debug_read_adapter_tagged.h"
#include "bitfield_debug_read_callback.h"
#include "bitfield_debug_read_callback_base.h"
#include "bitfield_debug_write_adapter.h"
#include "bitfield_debug_write_adapter_tagged.h"
#include "bitfield_debug_write_callback.h"
#include "bitfield_debug_write_callback_base.h"
#include "bitfield_default_read_behavior_adapter.h"
#include "bitfield_default_write_behavior_adapter.h"
#include "bitfield_disallow_debug_read_access_callback.h"
#include "bitfield_disallow_debug_write_access_callback.h"
#include "bitfield_disallow_read_access_callback.h"
#include "bitfield_disallow_write_access_callback.h"
#include "bitfield_mask_read_adapter.h"
#include "bitfield_mask_read_adapter_tagged.h"
#include "bitfield_mask_write_adapter.h"
#include "bitfield_mask_write_adapter_tagged.h"
#include "bitfield_neversync_read_callback.h"
#include "bitfield_neversync_write_callback.h"
#include "bitfield_null_adapter.h"
#include "bitfield_on_write_adapter.h"
#include "bitfield_post_write_adapter.h"
#include "bitfield_post_write_adapter_tagged.h"
#include "bitfield_read_adapter.h"
#include "bitfield_read_adapter_tagged.h"
#include "bitfield_read_callback.h"
#include "bitfield_read_callback_base.h"
#include "bitfield_selfsync_read_callback.h"
#include "bitfield_selfsync_write_callback.h"
#include "bitfield_set_on_read_adapter.h"
#include "bitfield_store_after_read_adapter.h"
#include "bitfield_untimed_mask_read_adapter.h"
#include "bitfield_untimed_mask_read_adapter_tagged.h"
#include "bitfield_untimed_mask_write_adapter.h"
#include "bitfield_untimed_mask_write_adapter_tagged.h"
#include "bitfield_untimed_read_adapter.h"
#include "bitfield_untimed_read_adapter_tagged.h"
#include "bitfield_untimed_write_adapter.h"
#include "bitfield_untimed_write_adapter_tagged.h"
#include "bitfield_write_adapter.h"
#include "bitfield_write_adapter_tagged.h"
#include "bitfield_write_callback.h"
#include "bitfield_write_callback_base.h"
#include "bitfield_write_once_adapter.h"
#include "burst_unroller.h"
#include "callback_macro.h"
#include "callback_observer.h"
#include "callback_observer_owner.h"
#include "callback_observers.h"
#include "set_on_read_adapter.h"
#include "debug_burst_unroller.h"
#include "debug_callback.h"
#include "debug_transport_adapter.h"
#include "debug_transport_adapter_tagged.h"
#include "default_behavior_adapter.h"
#include "dmi_handler.h"
#include "initiator_socket.h"
#include "severity.h"
#include "mappable_if.h"
#include "thread_pool.h"
#include "mapped_range.h"
#include "mapped_ranges_observer.h"
#include "mapped_ranges_observer_owner.h"
#include "mapped_ranges_observers.h"
#include "memory.h"
#include "memory_alias.h"
#include "memory_base.h"
#include "memory_behavior_functions.h"
#include "memory_callback.h"
#include "memory_callback_base.h"
#include "memory_callback_functions.h"
#include "memory_callback_functions_include.h"
#include "memory_const_iterator.h"
#include "memory_content_observer.h"
#include "memory_content_observer_owner.h"
#include "memory_content_observers.h"
#include "memory_debug_callback.h"
#include "memory_debug_callback_base.h"
#include "memory_debug_callback_functions.h"
#include "memory_disallow_access_callback.h"
#include "memory_disallow_debug_access_callback.h"
#include "memory_dmi.h"
#include "memory_fast_access.h"
#include "memory_fast_access_impl.h"
#include "memory_index_reference.h"
#include "memory_iterator.h"
#include "memory_iterator_base.h"
#include "memory_region.h"
#include "memory_region_registry.h"
#include "memory_select_callback_base.h"
#include "memory_select_callback.h"
#include "memory_slow_access_base.h"
#include "neversync_callback.h"
#include "null_adapter.h"
#include "on_write_adapter.h"
#include "pair_signal.h"
#include "pin_callback.h"
#include "pin_callback_base.h"
#include "pin_callback_functions.h"
#include "pin_callback_tagged.h"
#include "post_write_adapter.h"
#include "post_write_adapter_tagged.h"
#include "quantumkeeper_if.h"
#include "quantumkeeper_wrapper.h"
#include "read_adapter.h"
#include "read_adapter_tagged.h"
#include "read_extensions_adapter.h"
#include "read_extensions_adapter_tagged.h"
#include "reg.h"
#include "reg_vector_creator.h"
#include "reset_trigger.h"
#include "resource.h"
#include "router.h"
#include "router_base.h"
#include "router_callback.h"
#include "router_callback_base.h"
#include "router_callback_functions.h"
#include "router_debug_callback.h"
#include "router_debug_callback_base.h"
#include "router_debug_callback_functions.h"
#include "scoped_reference.h"
#include "vector.h"
#include "selfsync_callback.h"
#include "status.h"
#include "status_observer.h"
#include "status_observer_owner.h"
#include "status_registry.h"
#include "store_after_read_adapter.h"
#include "stream.h"
#include "streams.h"
#include "symbolic_names.h"
#include "timing_annotation_registry.h"
#include "tlm2_gp_extensions.h"
#include "tlm2_gp_initiator_adapter.h"
#include "tlm2_gp_target_adapter.h"
#include "toplevel_memory_base.h"
#include "transport_adapter.h"
#include "transport_adapter_tagged.h"
#include "trigger_signal.h"
#include "types.h"
#include "untimed_read_adapter.h"
#include "untimed_read_adapter_tagged.h"
#include "untimed_read_extensions_adapter.h"
#include "untimed_read_extensions_adapter_tagged.h"
#include "untimed_transport_adapter.h"
#include "untimed_transport_adapter_tagged.h"
#include "untimed_word_read_adapter.h"
#include "untimed_word_read_adapter_tagged.h"
#include "untimed_word_read_extensions_adapter.h"
#include "untimed_word_read_extensions_adapter_tagged.h"
#include "untimed_word_write_adapter.h"
#include "untimed_word_write_adapter_tagged.h"
#include "untimed_word_write_extensions_adapter.h"
#include "untimed_word_write_extensions_adapter_tagged.h"
#include "untimed_write_adapter.h"
#include "untimed_write_adapter_tagged.h"
#include "untimed_write_extensions_adapter.h"
#include "untimed_write_extensions_adapter_tagged.h"
#include "utils.h"
#include "word_access_unroller.h"
#include "word_access_unroller_base.h"
#include "word_adapter_base.h"
#include "word_read_adapter.h"
#include "word_read_adapter_tagged.h"
#include "word_read_extensions_adapter.h"
#include "word_read_extensions_adapter_tagged.h"
#include "word_write_adapter.h"
#include "word_write_adapter_tagged.h"
#include "word_write_extensions_adapter.h"
#include "word_write_extensions_adapter_tagged.h"
#include "write_adapter.h"
#include "write_adapter_tagged.h"
#include "write_extensions_adapter.h"
#include "write_extensions_adapter_tagged.h"
#include "write_once_adapter.h"
#include "write_once_state.h"

#endif
