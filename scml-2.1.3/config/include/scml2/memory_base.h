/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_BASE_H
#define SCML2_MEMORY_BASE_H

#include <scml2/memory_region.h>
#include <scml2/memory_callback_base.h>
#include <scml2/memory_debug_callback_base.h>
#include <scml2/callback_observers.h>
#include <scml2/symbolic_names.h>

#include <scml2/utils.h>
#include <scml2/scoped_reference.h>
#include <scml2/types.h>

#include <string>
#include <set>
#include <vector>
#include <cassert>

namespace tlm {
  class tlm_generic_payload;
}

namespace sc_core {
  class sc_time;
}

namespace scml2 {

class toplevel_memory_base;
class bitfield_base;

class memory_base : public memory_region
{
public:
  typedef std::vector<memory_base*> Aliases;
  typedef std::vector<memory_base*>::iterator AliasesIterator;
  typedef std::vector<memory_base*>::const_iterator AliasesConstIterator;
  typedef symbolic_names::SymbolicNames SymbolicNames;

protected:
  memory_base(const std::string& name,
              memory_base* parent,
              unsigned long long offset,
              unsigned long long size,
              unsigned int width);

public:
  virtual ~memory_base();

  memory_base* get_parent() const;

  bool has_default_read_behavior() const;
  bool has_default_write_behavior() const;
  bool has_default_debug_read_behavior() const;
  bool has_default_debug_write_behavior() const;
  bool has_never_syncing_read_behavior() const;
  bool has_never_syncing_write_behavior() const;

  bool is_dmi_allowed() const;
  bool is_dmi_read_allowed() const;
  bool is_dmi_write_allowed() const;

  virtual void set_callback(memory_callback_base* cb);
  virtual void set_read_callback(memory_callback_base* cb);
  virtual void set_write_callback(memory_callback_base* cb);

  virtual void remove_callback();
  virtual void remove_read_callback();
  virtual void remove_write_callback();

  virtual memory_callback_base* get_read_callback() const;
  virtual memory_callback_base* get_write_callback() const;

  virtual void set_debug_callback(memory_debug_callback_base* cb);
  virtual void set_debug_read_callback(memory_debug_callback_base* cb);
  virtual void set_debug_write_callback(memory_debug_callback_base* cb);

  virtual void remove_debug_callback();
  virtual void remove_debug_read_callback();
  virtual void remove_debug_write_callback();

  virtual memory_debug_callback_base* get_debug_read_callback() const;
  virtual memory_debug_callback_base* get_debug_write_callback() const;

  virtual unsigned int collect_bitfields(std::vector<bitfield_base*>& b) const;

  virtual bool content_is_observable() const;

  virtual void enable_dmi();
  virtual void disable_dmi();
  virtual bool is_dmi_enabled() const;

  bool set_symbolic_name(const std::vector<unsigned char>& value,
                         const std::string& name);
  unsigned int collect_symbolic_names(SymbolicNames& symbolicNames) const;

protected:
  void init_default_callback(memory_callback_base* cb);
  void init_default_debug_callback(memory_debug_callback_base* cb);

  virtual void invalidate_dmi() = 0;

  virtual void update_fast_access() = 0;
  void propagate_update_fast_access();

private:
  void do_set_read_callback(memory_callback_base* cb);
  void do_set_write_callback(memory_callback_base* cb);
  void do_set_debug_read_callback(memory_debug_callback_base* cb);
  void do_set_debug_write_callback(memory_debug_callback_base* cb);

  friend class toplevel_memory_base;

  void execute_behavior(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
  unsigned int execute_debug_behavior(tlm::tlm_generic_payload& trans);

public:
  AliasesConstIterator begin_alias() const;
  AliasesIterator begin_alias();
  AliasesConstIterator end_alias() const;
  AliasesIterator end_alias();

private:
  void register_alias(memory_base& alias);

private:
  memory_base* mParent;

  memory_callback_base* mDefaultCallback;
  memory_callback_base* mReadCallback;
  memory_callback_base* mWriteCallback;
  memory_debug_callback_base* mDebugReadCallback;
  memory_debug_callback_base* mDebugWriteCallback;
  memory_debug_callback_base* mDefaultDebugCallback;

  Aliases mAliases;

  bool mDmiEnabled;

  symbolic_names mSymbolicNames;
};

inline
memory_base*
memory_base::
get_parent() const
{
  return mParent;
}

inline
bool
memory_base::
has_default_read_behavior() const
{
  assert(mReadCallback);
  return mReadCallback->has_default_behavior();
}

inline
bool
memory_base::
has_default_write_behavior() const
{
  assert(mWriteCallback);
  return mWriteCallback->has_default_behavior();
}

inline
bool
memory_base::
has_default_debug_read_behavior() const
{
  assert(mDebugReadCallback);
  return mDebugReadCallback->has_default_behavior();
}

inline
bool
memory_base::
has_default_debug_write_behavior() const
{
  assert(mDebugWriteCallback);
  return mDebugWriteCallback->has_default_behavior();
}

inline
bool
memory_base::
has_never_syncing_read_behavior() const
{
  assert(mReadCallback);
  return mReadCallback->has_never_syncing_behavior();
}

inline
bool
memory_base::
has_never_syncing_write_behavior() const
{
  assert(mWriteCallback);
  return mWriteCallback->has_never_syncing_behavior();
}

inline
bool
memory_base::
is_dmi_allowed() const
{
  return is_dmi_read_allowed() && is_dmi_write_allowed();
}

inline
bool
memory_base::
is_dmi_read_allowed() const
{
  return has_default_read_behavior() &&
         has_default_debug_read_behavior() &&
         is_dmi_enabled();
}

inline
bool
memory_base::
is_dmi_write_allowed() const
{
  return has_default_write_behavior() &&
         has_default_debug_write_behavior() &&
         is_dmi_enabled();
}

inline
memory_base::AliasesConstIterator
memory_base::
begin_alias() const
{
  return mAliases.begin();
}

inline
memory_base::AliasesIterator
memory_base::
begin_alias()
{
  return mAliases.begin();
}

inline
memory_base::AliasesConstIterator
memory_base::
end_alias() const
{
  return mAliases.end();
}

inline
memory_base::AliasesIterator
memory_base::
end_alias()
{
  return mAliases.end();
}

inline
void
memory_base::
execute_behavior(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  if (trans.is_read()) {
    assert(mReadCallback);
    scoped_reference<memory_callback_base> scopedRef(mReadCallback);
    unsigned int id =
      mCallbackObservers.notify_begin(trans, ACCESS_MODE_REGULAR);
    mReadCallback->execute(trans, t);
    mCallbackObservers.notify_end(trans, id);

  } else {
    assert(mWriteCallback);
    scoped_reference<memory_callback_base> scopedRef(mWriteCallback);
    unsigned int id =
      mCallbackObservers.notify_begin(trans, ACCESS_MODE_REGULAR);
    mWriteCallback->execute(trans, t);
    mCallbackObservers.notify_end(trans, id);
  }
}

inline
unsigned int
memory_base::
execute_debug_behavior(tlm::tlm_generic_payload& trans)
{
  if (trans.is_read()) {
    assert(mDebugReadCallback);
    scoped_reference<memory_debug_callback_base> scopedRef(mDebugReadCallback);
    unsigned int id =
      mCallbackObservers.notify_begin(trans, ACCESS_MODE_DEBUG);
    unsigned int result = mDebugReadCallback->execute(trans);
    mCallbackObservers.notify_end(trans, id);
    return result;

  } else {
    assert(mDebugWriteCallback);
    scoped_reference<memory_debug_callback_base> scopedRef(mDebugWriteCallback);
    unsigned int id =
      mCallbackObservers.notify_begin(trans, ACCESS_MODE_DEBUG);
    unsigned int result = mDebugWriteCallback->execute(trans);
    mCallbackObservers.notify_end(trans, id);
    return result;
  }
}

}

#endif
