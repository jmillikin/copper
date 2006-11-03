/* fixture.cpp - Allows easy sharing of data between tests
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper/fixture.hpp>
#include "export.hpp"

namespace Copper {

EXPORT Fixture::Fixture(){}

EXPORT Fixture::~Fixture(){}

void Fixture::set_up(){}

EXPORT void Fixture::tear_down(){}

} /* namespace */