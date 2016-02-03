#ifndef SCML2_MEMORY_CALLBACK_FUNCTIONS_INCLUDE_H
#define SCML2_MEMORY_CALLBACK_FUNCTIONS_INCLUDE_H
namespace scml2 {
template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_read_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_read_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_read_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_read_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_store_after_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline void set_clear_on_read(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) {
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_default_behavior_adapter(null_adapter(), mem), mem, (DT) 0x0), "<clear_on_read>", syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_transport_adapter(*c, cb), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_transport_adapter(*c, cb), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_transport_adapter(*c, cb, id), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_transport_adapter(*c, cb, id), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, mem), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, mem), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, mem), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, mem), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem, (DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline void set_set_on_read(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) {
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_default_behavior_adapter(null_adapter(), mem), mem, ~(DT) 0x0), "<set_on_read>", syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_transport_adapter(*c, cb), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_transport_adapter(*c, cb), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_transport_adapter(*c, cb, id), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_transport_adapter(*c, cb, id), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, mem)), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_access_unroller<DT>(create_read_adapter(*c, cb, id, mem)), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, mem), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, mem), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, mem), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, mem), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_read_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_read_callback(create_memory_callback(create_set_on_read_adapter(create_word_read_adapter(*c, cb, id, mem), mem, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_transport_adapter(*c, cb), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_transport_adapter(*c, cb), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_transport_adapter(*c, cb, id), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_transport_adapter(*c, cb, id), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_write_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_write_adapter(*c, cb, mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_write_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_write_adapter(*c, cb, mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_write_adapter(*c, cb, mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_write_adapter(*c, cb, mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_write_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_write_adapter(*c, cb, id, mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_write_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_write_adapter(*c, cb, id, mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_write_adapter(*c, cb, id, mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_write_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_word_write_adapter(*c, cb, id, mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_write_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_default_behavior_adapter(create_post_write_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_write_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_default_behavior_adapter(create_post_write_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline void set_clear_on_write_0(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) {
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(null_adapter(), mem), "<clear_on_write_0>", syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<true>(create_post_write_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_clear_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_0_adapter<true>(create_post_write_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline void set_clear_on_write_1(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) {
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(null_adapter(), mem), "<clear_on_write_1>", syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<true>(create_post_write_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_clear_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_clear_on_write_1_adapter<true>(create_post_write_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline void set_set_on_write_0(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) {
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(null_adapter(), mem), "<set_on_write_0>", syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<true>(create_post_write_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_set_on_write_0_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_0_adapter<true>(create_post_write_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline void set_set_on_write_1(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) {
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(null_adapter(), mem), "<set_on_write_1>", syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_word_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<false>(create_word_write_adapter(*c, cb, id, mem), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<true>(create_post_write_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_post_set_on_write_1_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_write_callback(create_memory_callback(create_set_on_write_1_adapter<true>(create_post_write_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline write_once_state* set_write_once_ignore(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) {
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(null_adapter(), mem), mem, &result), "<write_once_ignore>", syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_transport_adapter(*c, cb), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_transport_adapter(*c, cb), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_transport_adapter(*c, cb, id), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_transport_adapter(*c, cb, id), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, id, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, id, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, id, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, id, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_post_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<true>(create_default_behavior_adapter(create_post_write_adapter(*c, cb), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_post_write_once_ignore_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_ignore_adapter<true>(create_default_behavior_adapter(create_post_write_adapter(*c, cb, id), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT>
inline write_once_state* set_write_once_error(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) {
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(null_adapter(), mem), mem, &result), "<write_once_error>", syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_transport_adapter(*c, cb), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_transport_adapter(*c, cb), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_transport_adapter(*c, cb, id), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_transport_adapter(*c, cb, id), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_access_unroller<DT>(create_write_adapter(*c, cb, id, mem)), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, id, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, id, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, id, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_word_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_extensions_adapter_tagged<MEM_OBJECT<DT>,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<false>(create_default_behavior_adapter(create_word_write_adapter(*c, cb, id, mem), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_post_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<true>(create_default_behavior_adapter(create_post_write_adapter(*c, cb), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline write_once_state* set_post_write_once_error_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  mem.set_write_callback(create_memory_callback(create_write_once_error_adapter<true>(create_default_behavior_adapter(create_post_write_adapter(*c, cb, id), mem), mem, &result), cbName, syncType));
  return result;
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  mem.set_callback(create_memory_callback(create_store_after_read_adapter(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_callback(create_memory_callback(create_store_after_read_adapter(create_transport_adapter(*c, cb), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  mem.set_callback(create_memory_callback(create_store_after_read_adapter(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline void set_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }
  assert(c);
  mem.set_callback(create_memory_callback(create_store_after_read_adapter(create_transport_adapter(*c, cb, id), mem), cbName, syncType));
}

}
#endif
