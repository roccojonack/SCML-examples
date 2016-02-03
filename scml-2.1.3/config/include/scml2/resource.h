/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_RESOURCE_H
#define SCML2_RESOURCE_H

#include <cassert>

namespace scml2 {

class resource
{
public:
  resource();

  void ref() const;
  void unref() const;
  unsigned int getRefCount() const;

protected:
  virtual ~resource();

private:
  resource(const resource&);
  resource& operator=(const resource&);

private:
  mutable unsigned int mRefCount;
};

inline
resource::
resource() :
  mRefCount(0)
{
}

inline
resource::
~resource()
{
}

inline
void
resource::
ref() const
{
  ++mRefCount;
}

inline
void
resource::
unref() const
{
  assert(mRefCount);
  if (--mRefCount == 0) {
    delete this;
  }
}

inline
unsigned int
resource::
getRefCount() const
{
  return mRefCount;
}

}

#endif
