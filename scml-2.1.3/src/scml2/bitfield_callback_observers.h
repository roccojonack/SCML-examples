/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_CALLBACK_OBSERVERS_H
#define SCML2_BITFIELD_CALLBACK_OBSERVERS_H

#include <scml2/bitfield_callback_observer.h>
#include <scml2/types.h>

#include <set>

namespace scml2 {

template <typename DT> class bitfield_callback_observer_owner;

template <typename DT>
class bitfield_callback_observers
{
public:
  bitfield_callback_observers();
  ~bitfield_callback_observers();

  bool has_observers() const;

  unsigned int notify_begin(const DT* data,
                            const DT* bitMask,
                            access_type type,
                            access_mode mode) const;
  void notify_end(const DT* data, unsigned int id) const;
  void notify_callback_changed(access_type type, access_mode mode);

  bool register_observer(bitfield_callback_observer<DT>* o);
  bool unregister_all_observers();
  bool unregister_observer(bitfield_callback_observer<DT>* o);

private:
  typedef std::set<bitfield_callback_observer<DT>*> Observers;
  typedef typename Observers::iterator ObserversIter;
  typedef typename Observers::const_iterator ObserversConstIter;

  Observers& get_mutable_observers();
  void update_observers() const;

private:
  bool mObservingEnabled;
  mutable Observers* mObservers;
  mutable Observers* mMutableObservers;
  mutable int mNotifyLevel;
};

template <typename DT>
inline
bool
bitfield_callback_observers<DT>::
has_observers() const
{
  return mObservingEnabled;
}

}

#endif
