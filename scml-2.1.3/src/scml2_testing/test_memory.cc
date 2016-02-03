/*****************************************************************************
 *                   Copyright (C) 2009-2012 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/

#include <scml2_testing/test_memory.h>
#include <scml2_testing/initiator_socket_proxy_base.h>

#include <cassert>

#define MIN(x, y) ((x < y) ? x : y)
#define BUFFER_SIZE 4096

namespace {
  void readFile(const std::string& file, size_t size, std::vector<unsigned char>& data) {
    std::ifstream input(file.c_str(), std::ios_base::in|std::ios_base::binary);
    data.resize(0);
    while (input.good() && data.size() < size) {
      size_t oldSize = data.size();
      data.resize(oldSize + BUFFER_SIZE);
      input.read(reinterpret_cast<char*>(&data[oldSize]), BUFFER_SIZE);
      data.resize(MIN(oldSize + input.gcount(), size));
    }
    input.close();
  }
}

namespace scml2 { namespace testing {

test_memory::test_memory(unsigned long long base, unsigned long long size, initiator_socket_proxy_base& socket) : base(base), size(size), socket(&socket), data(sc_core::sc_gen_unique_name("data"), size) {
  socket.add_memory(this);
}

test_memory::~test_memory() {
  socket->remove_memory(this);
}

test_memory_element test_memory::operator[](unsigned long long offset) {
  assert(offset < size);
  return test_memory_element(data[offset]);
}

unsigned long long test_memory::get_size() const {
  return size;
}

unsigned long long test_memory::get_offset() const {
  return base;
}

scml2::mappable_if& test_memory::get_internal_memory() {
  return data;
}

void test_memory::load(const std::string& file, unsigned long long addr, size_t size) {
  std::vector<unsigned char> rawData;
  readFile(file, size, rawData);
  for (size_t i = 0; i < rawData.size(); ++i) {
    data[addr + i] = rawData[i];
  }
}

void test_memory::save(const std::string& file, unsigned long long addr, size_t size) {
  std::ofstream output(file.c_str(), std::ios_base::out|std::ios_base::binary);
  for (size_t i = addr; i < MIN(addr+size, data.get_size()); ++i) {
    output.put(data[i]);
  }
  output.close();
}

bool test_memory::compare(const std::string& file, unsigned long long addr, size_t size) {
  std::vector<unsigned char> rawData;
  readFile(file, size, rawData);
  for (size_t i = 0; i < rawData.size(); ++i) {
    if (data[addr + i] != rawData[i]) {
      return false;
    }
  }
  return true;
}

}}
