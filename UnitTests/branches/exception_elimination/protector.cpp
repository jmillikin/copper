/* protector.cpp - Base class for all protectors
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <list>
#include <algorithm>
#include "protector.h"
#include "test.h"

namespace UnitTests {

std::list<Protector*>* protectors() {
  static std::list<Protector*> _protectors;
  return &_protectors;
}

Protector::Protector() throw () {}

Protector::~Protector() throw () {}

void Protector::add(Protector* protector) {
  protectors()->push_back(protector);
}

Assertion* Protector::guard(Test* test) {
  if (protectors()->size() > 0) {
    std::list<Protector*>::iterator iter = protectors()->begin();
    return (*iter)->_guard(test);
  }

  else {
    return test->run();
  }
}

Assertion* Protector::next_protector(Test* test) {
  std::list<Protector*>::iterator iter =
    std::find(protectors()->begin(), protectors()->end(), this);

  if (iter != protectors()->end()) {
    ++iter;
    if (iter != protectors()->end()) {
      return (*iter)->_guard(test);
    }
    else {
      return test->run();
    }
  }
  return 0;
}

} // namespace
