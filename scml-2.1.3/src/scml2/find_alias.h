/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_FIND_ALIAS_H
#define SCML2_FIND_ALIAS_H

#include <scml2/toplevel_memory_base.h>
#include <scml2/memory_base.h>

namespace {
  struct HasNonDefaultReadBehavior
  {
    bool operator()(scml2::memory_base* alias) const
    {
      return !alias->has_default_read_behavior();
    }
  };

  struct HasNonDefaultWriteBehavior
  {
    bool operator()(scml2::memory_base* alias) const
    {
      return !alias->has_default_write_behavior();
    }
  };

  struct HasNonDefaultDebugReadBehavior
  {
    bool operator()(scml2::memory_base* alias) const
    {
      return !alias->has_default_debug_read_behavior();
    }
  };

  struct HasNonDefaultDebugWriteBehavior
  {
    bool operator()(scml2::memory_base* alias) const
    {
      return !alias->has_default_debug_write_behavior();
    }
  };
}

namespace scml2 {

template <typename F>
inline
bool
has_refined_behavior(memory_base& alias,
                     unsigned long long lowIndex,
                     unsigned long long highIndex,
                     const F& condition)
{
  memory_base::AliasesConstIterator it = alias.begin_alias();
  memory_base::AliasesConstIterator end = alias.end_alias();

  for (; it != end; ++it) {
    if (highIndex >= (*it)->get_offset() &&
        lowIndex < (*it)->get_offset() + (*it)->get_size()) {
      if (condition(*it) ||
          has_refined_behavior(*(*it), lowIndex, highIndex, condition)) {
        return true;
      }
    }
  }

  return false;
}

template <typename F>
inline
memory_base*
find_alias(toplevel_memory_base& mem,
           unsigned long long lowIndex,
           unsigned long long highIndex,
           const F& condition)
{
  if (highIndex >= mem.get_size()) {
    return 0;
  }

  memory_base* alias = &mem;
  bool stop;

  do {
    memory_base::AliasesConstIterator it = alias->begin_alias();
    memory_base::AliasesConstIterator end = alias->end_alias();

    stop = true;
    for (; it != end; ++it) {
      if (lowIndex >= (*it)->get_offset() &&
          highIndex < (*it)->get_offset() + (*it)->get_size()) {
        alias = *it;
        stop = false;
        break;
      }
    }
  } while (!stop);

  while (alias && !condition(alias)) {
    alias = alias->get_parent();
  }

  if (!alias) {
    alias = &mem;
  }

  if (lowIndex != highIndex &&
      has_refined_behavior(*alias, lowIndex, highIndex, condition)) {
    return 0;

  } else {
    return alias;
  }
}

}

#endif
