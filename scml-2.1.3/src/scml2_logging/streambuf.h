/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_LOGGING_STREAMBUF_H
#define SCML2_LOGGING_STREAMBUF_H

#include <ios>
#include <vector>

namespace scml2 { namespace logging {

class stream_base;

class streambuf : public std::streambuf
{
public:
  streambuf(const stream_base& streamBase);

  virtual std::streamsize xsputn(const char* p, std::streamsize n);
  virtual int sync();
  virtual int overflow(int c);

private:
  char* begin();
  char* end();

private:
  std::vector<char> mBuffer;
  mutable const stream_base& mStreamBase;

  // disabled
  streambuf();
  streambuf(const streambuf&);
  streambuf& operator= (const streambuf&);
};

inline
char*
streambuf::
begin()
{
  return &mBuffer.front();
}

inline
char*
streambuf::
end()
{
  return &mBuffer.back() + 1;
}

} }

#endif
