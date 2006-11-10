/* protector.cpp - Base class for all protectors
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper/protector.hpp>
#include <copper/test.hpp>
#include <copper/util/list.hpp>
#include "export.hpp"

namespace Copper {

List<Protector>& protectors() {
  static List<Protector> _protectors;
  return _protectors;
}

Protector::Protector() throw () {
  add(this);
}

Protector::~Protector() throw () {}

EXPORT void Protector::add(Protector* protector) {
  protectors().append(protector);
}

void Protector::guard(Test* test, Assertion** failure, Error** error) {
  if (protectors().size() > 0) {
    protectors().root()->value->_guard(test, failure, error);
  }

  else {
    *failure = test->run();
  }
}

void Protector::next_protector(Test* test, Assertion** failure,
  Error** error) {

  const ListNode<Protector>* node = protectors().find(this);

  if (!node) {
    // This protector isn't in the protector list???
    return;
  }

  node = node->next;

  if (node) {
    node->value->_guard(test, failure, error);
  }

  else {
    // Reached the end of the list
    *failure = test->run();
  }
}

} // namespace
