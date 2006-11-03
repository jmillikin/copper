/* protector.cpp - Base class for all protectors
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <list>
#include <algorithm>
#include <copper/protector.hpp>
#include <copper/test.hpp>

namespace Copper {

std::list<Protector*>* protectors() {
  static std::list<Protector*> _protectors;
  return &_protectors;
}

Protector::Protector() throw () {}

Protector::~Protector() throw () {}

void Protector::add(Protector* protector) {
  protectors()->push_back(protector);
}

void Protector::guard(Test* test, Assertion** failure, Error** error) {
  if (protectors()->size() > 0) {
    std::list<Protector*>::iterator iter = protectors()->begin();
    (*iter)->_guard(test, failure, error);
  }

  else {
    *failure = test->run();
  }
}

void Protector::next_protector(Test* test, Assertion** failure,
  Error** error) {

  std::list<Protector*>::iterator iter =
    std::find(protectors()->begin(), protectors()->end(), this);

  if (iter != protectors()->end()) {
    ++iter;
    if (iter != protectors()->end()) {
      (*iter)->_guard(test, failure, error);
    }
    else {
      *failure = test->run();
    }
  }
}

} // namespace
