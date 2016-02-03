/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_DMI_H
#define SCML2_MEMORY_DMI_H

#include <scml2_logging/stream.h>
#include <list>

namespace scml2 {

class memory_dmi
{
public:
  struct DmiDataEntry
  {
    DmiDataEntry(unsigned long long startIndex,
                 unsigned long long endIndex,
                 bool dmiAllowed);
    unsigned long long startIndex;
    unsigned long long endIndex;
    bool dmiAllowed;
  };

  typedef std::list<DmiDataEntry> DmiData;
  typedef DmiData::iterator DmiDataIter;
  typedef DmiData::const_iterator DmiDataConstIter;

public:
  memory_dmi(unsigned long long size);

  void clear();

  void disable();
  void disable(unsigned long long startIndex,
               unsigned long long endIndex);

  const DmiDataEntry& find(unsigned long long index) const;

  DmiDataConstIter begin() const;
  DmiDataConstIter end() const;
  unsigned long long nrOfRegions() const;

private:
  static logging::stream mInternalError;

private:
  unsigned long long mSize;
  DmiData mDmiData;
};

inline
memory_dmi::DmiDataConstIter
memory_dmi::
begin() const
{
  return mDmiData.begin();
}

inline
memory_dmi::DmiDataConstIter
memory_dmi::
end() const
{
  return mDmiData.end();
}

inline
unsigned long long
memory_dmi::
nrOfRegions() const
{
  return mDmiData.size();
}

}

#endif
