#include <list>
#include <algorithm>
#include "protector.h"
#include "test.h"

namespace UnitTests {

std::list<Protector*>* protectors = 0;

Protector::Protector() throw () {}

Protector::~Protector() throw () {}

void Protector::add(Protector* protector) {
  if (!protectors) {
    static std::list<Protector*> _protectors;
    protectors = &_protectors;
  }
  protectors->push_back(protector);
}

void Protector::guard(Test* test) {
  if (protectors && protectors->size() > 0) {
    std::list<Protector*>::iterator iter = protectors->begin();
    (*iter)->_guard(test);
  }

  else {
    test->run();
  }
}

void Protector::next_protector(Test* test) {
  std::list<Protector*>::iterator iter =
    std::find(protectors->begin(), protectors->end(), this);

  if (iter != protectors->end()) {
    ++iter;
    if (iter != protectors->end()) {
      (*iter)->_guard(test);
    }
    else {
      test->run();
    }
  }
}

} // namespace
