#ifndef SCML2_BITFIELD_CALLBACK_FUNCTIONS_INCLUDE_H
#define SCML2_BITFIELD_CALLBACK_FUNCTIONS_INCLUDE_H
namespace scml2 {
template <typename DT, typename C>
inline void set_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_store_after_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_store_after_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_store_after_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_store_after_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_store_after_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_store_after_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_store_after_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_store_after_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT>
inline void set_clear_on_read(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) {
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_default_read_behavior_adapter<DT>(bitfield_null_adapter<DT>(), bitfield), bitfield, (DT) 0x0), "<clear_on_read>", syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield, (DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield, (DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield, (DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield, (DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield, (DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield, (DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield, (DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield, (DT) 0x0), cbName, syncType));
}

template <typename DT>
inline void set_set_on_read(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) {
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_default_read_behavior_adapter<DT>(bitfield_null_adapter<DT>(), bitfield), bitfield, ~(DT) 0x0), "<set_on_read>", syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb), bitfield, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_read_callback(create_bitfield_read_callback<DT>(create_bitfield_set_on_read_adapter<DT>(create_bitfield_read_adapter<DT>(*c, cb, id), bitfield, ~(DT) 0x0), cbName, syncType));
}

template <typename DT, typename C>
inline void set_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_adapter<DT>(*c, cb), cbName, syncType));
}

template <typename DT, typename C>
inline void set_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_adapter<DT>(*c, cb), cbName, syncType));
}

template <typename DT, typename C>
inline void set_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_adapter<DT>(*c, cb, id), cbName, syncType));
}

template <typename DT, typename C>
inline void set_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_adapter<DT>(*c, cb, id), cbName, syncType));
}

template <typename DT, typename C>
inline void set_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_adapter<DT>(*c, cb), cbName, syncType));
}

template <typename DT, typename C>
inline void set_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_adapter<DT>(*c, cb), cbName, syncType));
}

template <typename DT, typename C>
inline void set_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_adapter<DT>(*c, cb, id), cbName, syncType));
}

template <typename DT, typename C>
inline void set_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_adapter<DT>(*c, cb, id), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_default_write_behavior_adapter(create_bitfield_post_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_write_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_default_write_behavior_adapter(create_bitfield_post_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT>
inline void set_clear_on_write_0(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) {
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<false>(bitfield_null_adapter<DT>(), bitfield), "<clear_on_write_0>", syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<true>(create_bitfield_post_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_clear_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_0_adapter<true>(create_bitfield_post_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT>
inline void set_clear_on_write_1(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) {
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<false>(bitfield_null_adapter<DT>(), bitfield), "<clear_on_write_1>", syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<true>(create_bitfield_post_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_clear_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_clear_on_write_1_adapter<true>(create_bitfield_post_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT>
inline void set_set_on_write_0(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) {
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<false>(bitfield_null_adapter<DT>(), bitfield), "<set_on_write_0>", syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<true>(create_bitfield_post_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_set_on_write_0_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_0_adapter<true>(create_bitfield_post_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT>
inline void set_set_on_write_1(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) {
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<false>(bitfield_null_adapter<DT>(), bitfield), "<set_on_write_1>", syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<false>(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<true>(create_bitfield_post_write_adapter<DT>(*c, cb), bitfield), cbName, syncType));
}

template <typename DT, typename C>
inline void set_post_set_on_write_1_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_set_on_write_1_adapter<true>(create_bitfield_post_write_adapter<DT>(*c, cb, id), bitfield), cbName, syncType));
}

template <typename DT>
inline write_once_state* set_write_once_ignore(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) {
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<false>(create_bitfield_default_write_behavior_adapter(bitfield_null_adapter<DT>(), bitfield), bitfield, &result), "<write_once_ignore>", syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_post_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<true>(create_bitfield_default_write_behavior_adapter(create_bitfield_post_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_post_write_once_ignore_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_ignore_adapter<true>(create_bitfield_default_write_behavior_adapter(create_bitfield_post_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT>
inline write_once_state* set_write_once_error(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) {
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<false>(create_bitfield_default_write_behavior_adapter(bitfield_null_adapter<DT>(), bitfield), bitfield, &result), "<write_once_error>", syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<false>(create_bitfield_default_write_behavior_adapter(create_bitfield_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_post_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<true>(create_bitfield_default_write_behavior_adapter(create_bitfield_post_write_adapter<DT>(*c, cb), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

template <typename DT, typename C>
inline write_once_state* set_post_write_once_error_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter_tagged<DT,C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) {
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }
  assert(c);
  write_once_state* result;
  bitfield.set_write_callback(create_bitfield_write_callback<DT>(create_bitfield_write_once_error_adapter<true>(create_bitfield_default_write_behavior_adapter(create_bitfield_post_write_adapter<DT>(*c, cb, id), bitfield), bitfield, &result), cbName, syncType));
  return result;
}

}
#endif
