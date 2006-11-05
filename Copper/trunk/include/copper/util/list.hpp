/* list.hpp -- Simple linked list to avoid dependency on std::list
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_UTIL_LIST_HPP
#define COPPER_UTIL_LIST_HPP

namespace Copper {

template <class C>
struct ListNode {
  ListNode(C* _value): next(0), value(_value) {}
  ListNode* next;
  C* value;
};

template <class C>
class List {
public:
  List() throw (): _root(0), _size(0) {}

  List(const List& b) {
    if (!b._root) {
      _root = 0;
      return;
    }

    _root = new ListNode<C>(b._root->value);

    ListNode<C>* node = _root, *b_node = b._root->next;

    while (b_node) {
      node->next = new ListNode<C>(b_node->value);
      node = node->next;
      b_node = b_node->next;
    }

    _size = b._size;
  }

  List& operator=(const List& b) {
    if (!b._root) {
      _root = 0;
      return *this;
    }

    _root = new ListNode<C>(b._root->value);

    ListNode<C>* node = _root, *b_node = b._root->next;

    while (b_node) {
      node->next = new ListNode<C>(b_node->value);
      node = node->next;
      b_node = b_node->next;
    }

    _size = b._size;
    return *this;
  }

  ~List() throw () {
    ListNode<C>* node = _root, *next;
    while (node) {
      next = node->next;
      delete node;
      node = next;
    }
  }

  void append(C* value) throw () {
    if (_root) {
      ListNode<C>* last = _root;
      while (last->next) {
        last = last->next;
      }

      last->next = new ListNode<C>(value);
    }

    else {
      _root = new ListNode<C>(value);
    }

    ++_size;
  }

  /**
    Perform a search for the node containing the given key

    @return The list node containing the given key, or NULL if the key was not
    found
  */
  const ListNode<C>* find(C* key) const throw () {
    ListNode<C>* node = _root;
    while (node) {
      // Yes, this is meant to compare pointers
      if (node->value == key) {
        return node;
      }
      node = node->next;
    }
    return 0;
  }

  const ListNode<C>* root() const throw () {
    return _root;
  }

  int size() const throw () {
    return _size;
  }

protected:
  ListNode<C>* _root;
  int _size;
};

} /* Namespace */

#endif /* COPPER_UTIL_LIST_HPP */
