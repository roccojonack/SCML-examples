/*****************************************************************************
 *                   Copyright (C) 1996-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
/*
 * Modifications : 
 *
 * Purpose of file :
 *
 */

#ifndef SCML_POOL_H
#define SCML_POOL_H

#include <cstddef>
#include <cassert>

#ifdef _WIN32
#define SCML_MAX(a, b) ((a) < (b) ? (b) : (a))
#else
#define SCML_MAX(a, b) std::max((a), (b))
#endif 


template< typename DT>
class scml_pool {
public:
  typedef DT value_type;
  typedef value_type * pointer;
  typedef const value_type * const_pointer;
  typedef value_type * iterator;
  typedef const value_type * const_iterator;
  typedef value_type & reference;
  typedef const value_type & const_reference;
  typedef size_t size_type;

public:
  explicit scml_pool( size_type initial_pool_size = 0);
  virtual ~scml_pool();  

  void allocate_additional_entries( size_type number_entries);
  void reduce_pool();

  pointer claim();
  void release( reference);
  void release( pointer);
  void release_all();

  void clear();

  size_type get_number_free() const;
  size_type get_number_in_use() const;

private:
  class List {
  public:
    struct Node {
      Node() : prev(0), next(0) {}
      Node* prev;
      Node* next;
      value_type data;
    };

  public:
    List() : mHead(0), mSize(0) {}
    ~List() { clear(); }

    void clear()
    {
      while (mHead) {
        Node* n = mHead;
        erase(mHead);
        delete n;
      }
    }
    bool empty() const { return mSize == 0; }
    unsigned int size() const { return mSize; }

    void push(Node* n)
    {
      n->next = mHead;
      n->prev = 0;
      if (mHead) {
        mHead->prev = n;
      }
      mHead = n;
      ++mSize;
    }
    void allocate_entry()
    {
      Node* n = new Node();
      push(n);
    }
    void erase(Node* n)
    {
      if (n != mHead) {
        n->prev->next = n->next;
      } else {
        mHead = n->next;
      }

      if (n->next != 0) {
        n->next->prev = n->prev;
      }
      assert(mSize);
      --mSize;
    }
    Node* pop()
    {
      assert(mHead);
      Node* n = mHead;
      erase(mHead);
      return n;
    }
    // insert contents of list l in this list
    void insert(List& l)
    {
      if (l.mHead == 0) return;

      if (mHead == 0) {
        mHead = l.mHead;
        mSize = l.mSize;

      } else {
        Node* tail = mHead;
        while (tail->next) {
          tail = tail->next;
        }
        tail->next = l.mHead;
        l.mHead->prev = tail;
        mSize += l.mSize;
      }

      l.mHead = 0;
      l.mSize = 0;
    }

    static Node* getNode(value_type* d)
    {
      // triggers gcc warning if value_type is a C++ type
      // size_t delta = offsetof(struct Node, data);
      
      // The trick with not using a null pointer avoids the GCC warning. I
      // (dpetras) proved by checking the generated ASM code that the 4 is
      // optimized away.
      size_t delta = (size_t)&((struct Node*)4)->data - 4;
      
      return reinterpret_cast<Node*>(reinterpret_cast<char*>(d) - delta);
    }

  private:
    Node* mHead;
    unsigned int mSize;
  };
private:
  // disable
  scml_pool( const scml_pool & );
  scml_pool & operator= ( const scml_pool & );

private:
  // data members
  List releasedItems;
  List claimedItems;
};

/************************************************************************
 * INLINE IMPLEMENTATIONS
 */

template< typename DT >
inline
scml_pool< DT>::
scml_pool( size_type initial_pool_size) :
  releasedItems(),
  claimedItems()
{
  allocate_additional_entries( initial_pool_size);
}

template< typename DT >
inline
scml_pool< DT>::
~scml_pool()
{
}

template< typename DT >
inline
void
scml_pool< DT>::
clear()
{
  releasedItems.clear();
  claimedItems.clear();
}

template< typename DT >
inline
void
scml_pool< DT>::
allocate_additional_entries( size_type n)
{
  for( size_type i( 0); i < n; ++i) {
    releasedItems.allocate_entry();
  }
}

template< typename DT >
inline
void
scml_pool< DT>::
reduce_pool()
{
  releasedItems.clear();
}

template< typename DT >
inline
typename scml_pool< DT>::pointer
scml_pool< DT>::
claim()
{
  if( releasedItems.empty()) {
    const size_type minval( 4);
    const size_type fractionInUse( get_number_in_use() / 10);
    allocate_additional_entries( SCML_MAX( minval, fractionInUse));
  }
  typename List::Node* n = releasedItems.pop();
  claimedItems.push(n);
  return &n->data;
}

template< typename DT >
inline
void
scml_pool< DT>::
release( pointer p)
{
  typename List::Node* n = List::getNode(p);
  claimedItems.erase(n);
  releasedItems.push(n);
}

template< typename DT >
inline
void
scml_pool< DT>::
release( reference r)
{
  release( &r);
}

template< typename DT >
inline
void
scml_pool< DT>::
release_all()
{
  releasedItems.insert(claimedItems);
}

template< typename DT >
inline
typename scml_pool< DT>::size_type
scml_pool< DT>::
get_number_free() const
{
  return releasedItems.size();
}

template< typename DT >
inline
typename scml_pool< DT>::size_type
scml_pool< DT>::
get_number_in_use() const
{
  return claimedItems.size();
}

#undef SCML_MAX

#endif
