/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2_logging/streambuf.h>
#include <scml2_logging/registry.h>

#define INITIAL_BUFFER_SIZE 120

namespace scml2 { namespace logging {

streambuf::
streambuf(const stream_base& streamBase) :
  std::streambuf(),
  mBuffer(INITIAL_BUFFER_SIZE),
  mStreamBase(streamBase)
{
  setp(begin(), end());
}

std::streamsize
streambuf::
xsputn(const char* p, std::streamsize n)
{
  if (pptr() + n >= epptr()) {
    std::streamsize offset = pptr() - pbase();
    mBuffer.resize(mBuffer.size() + n - (epptr() - pptr()));
    setp(begin(), end());
    pbump(offset);
  }

  std::copy(p, p + n, pptr());
  pbump(n);

  return n;
}

int
streambuf::
sync()
{
  if (pptr() + 1 >= epptr()) {
    mBuffer.push_back(0);
    setp(begin(), end());

  } else {
    *pptr() = 0;
  }

  std::streamsize n = pptr() - pbase();
  pbump(-n);

  registry::get_instance().log(mStreamBase, begin());

  return n;
}

int
streambuf::
overflow(int c)
{
  std::streamsize offset = pptr() - pbase();
  mBuffer.push_back(c);
  setp(begin(), end());
  pbump(offset + 1);

  return c;
}

} }

#undef INITIAL_BUFFER_SIZE

