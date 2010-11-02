/* Fixture.hpp -- Common data shared between unit tests
 * Copyright (C) 2009 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_FIXTURE_HPP
#define COPPER_FIXTURE_HPP

namespace Copper {

class Fixture
{
public:
	virtual void
	Copper_SetUpImpl ();
	
	virtual void
	Copper_TearDownImpl ();
};

}

#endif
