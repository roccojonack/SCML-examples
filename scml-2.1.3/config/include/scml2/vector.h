/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_VECTOR_H
#define SCML2_VECTOR_H

#include <vector>
#include <sstream>
#include <systemc>

namespace scml2 {

/**
 * This class is a temporary replacement for the upcoming SystemC 2.3's sc_vector.
 * It implements a minimal subset of sc_vector required to create and 
 * index into a vector of sc_objects.
 *
 * This implementation can be replaced with sc_vector.
 */
template <typename T>
class vector : public sc_core::sc_object
{
public:
  vector(const char* name) : sc_core::sc_object(name) {
  }

  vector(const char* name, size_t size) : sc_core::sc_object(name) {
    init(size);
  }

  template<typename Creator>
  vector(const char* name, size_t size, Creator creator) : sc_core::sc_object(name) {
    init(size, creator);
  }

  ~vector() {
    for(size_t i = 0; i < mElements.size(); ++i) {
      delete mElements[i];
    }
    mElements.clear();
  }

  const T& operator[](size_t i) const {
    return *(mElements[i]);
  }

  T& operator[](size_t i) {
    return *(mElements[i]);
  }

  size_t size() const {
    return mElements.size();
  }

  void init(size_t size) {
    init(size, &vector<T>::create_element);
  }

  template<typename Creator>
  void init(size_t size, Creator creator) {
    mElements.resize(size);
    for (size_t i = 0; i < size; ++i) {
      mElements[i] = creator(sc_core::sc_gen_unique_name(basename()), i);
    }
  }

private:
  static T* create_element(const char* prefix, size_t i) {
    return new T(prefix);
  }

private:
  std::vector<T*> mElements;
};

}

#endif
