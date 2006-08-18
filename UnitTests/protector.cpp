#include <list>
#include <algorithm>
#include "protector.h"
#include "test.h"

namespace UnitTests {

std::list<Protector*> protectors;

Protector::Protector() throw () {}

Protector::~Protector() throw () {}

void Protector::add(Protector* protector) {
  protectors.push_back(protector);
}

void Protector::guard(Test* test) {
  if (protectors.size() > 0) {
    std::list<Protector*>::iterator iter;

    for (iter = protectors.begin(); iter != protectors.end(); iter++) {
      (*iter)->_guard(test);
    }
  }

  else {
    test->run();
  }
}

void Protector::next_protector(Test* test) {
  std::list<Protector*>::iterator iter =
    std::find(protectors.begin(), protectors.end(), this);

  if (iter != protectors.end()) {
    ++iter;
    if (iter != protectors.end()) {
      (*iter)->_guard(test);
    }
    else {
      test->run();
    }
  }
}

} // namespace
