/* assertion_result.cpp - The result of a single assertion
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstring>
#include <cstdlib>
#include <copper/assertion_result.hpp>
#include "export.hpp"

namespace Copper
{
	EXPORT
	AssertionResult::AssertionResult () throw ():
	                                  m_finished (false),
	                                  m_passed (false),
	                                  m_failure_message ("Unitialized AssertionResult")
	{
	}

	EXPORT
	AssertionResult::AssertionResult (bool result) throw ():
	                                  m_finished (true),
	                                  m_passed (result)
	{
		if (!passed ())
			m_failure_message = "Boolean assertion failed";

		else
			m_failure_message = "No Error";
	}

	EXPORT
	AssertionResult::AssertionResult (const AssertionResult &other) throw ()
	{
		m_finished = other.m_finished;
		m_passed = other.m_passed;
		m_failure_message = other.m_failure_message;
	}

	EXPORT
	const AssertionResult &
	AssertionResult::operator= (const AssertionResult &other) throw ()
	{
		m_finished = other.m_finished;
		m_passed = other.m_passed;
		m_failure_message = other.m_failure_message;

		return *this;
	}

	EXPORT
	AssertionResult::~AssertionResult () throw ()
	{
	}

	EXPORT
	void
	AssertionResult::pass () throw ()
	{
		if (!m_finished)
		{
			m_passed = true;
			m_finished = true;
			m_failure_message = "No Error";
		}
	}

	EXPORT
	const AssertionResult &
	AssertionResult::fail (const String &failure_message) throw ()
	{
		if (!m_finished)
		{
			m_passed = false;
			m_finished = true;
			m_failure_message = failure_message;
		}

		return *this;
	}

	EXPORT
	bool
	AssertionResult::passed () const throw ()
	{
		return m_finished && m_passed;
	}

	EXPORT
	const String &
	AssertionResult::failure_message () const throw ()
	{
		return m_failure_message;
	}
}
