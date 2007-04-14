/* output_handler.hpp -- Outputs test results to stdout and stderr
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef OUTPUT_HANDLER_HPP
#define OUTPUT_HANDLER_HPP

#include <copper/output_handler.hpp>

/**
 * This is a default implementation of an OutputHandler. It will output
 * failures to the standard error stream
 */
class OutputHandler : public Copper::OutputHandler
{
public:
	/** Default constructor */
	OutputHandler (int &argc, char **&argv) throw ();

	/** Default destructor */
	~OutputHandler () throw ();

	/** Does nothing */
	void begin (const Copper::Test *test) throw ();

	/**
	 * Outputs nothing, but keeps track of how many tests passed
	 * 
	 * @param test The test that passed
	 */
	void pass (const Copper::Test *test) throw ();

	/**
	 * Outputs failures to the standard error stream. Also keeps track of how
	 * many tests failed
	 * 
	 * @param test The test that failed
	 * @param assetion The assertion that caused the test to fail
	 */
	void
	fail(const Copper::Test* test,
	     const Copper::Assertion* assertion) throw ();

	/**
	 * Outputs errors to the standard error stream. Also keeps track of how
	 * many tests errored out
	 * 
	 * @param test The test that failed
	 * @param error The error that was thrown
	 */
	void
	error(const Copper::Test* test, const Copper::Error* error) throw ();

	/**
	 * Run every test available
	 * 
	 * @return The number of failures + the number of errors
	 */
	int
	run();

protected:
	/** The number of tests that have passed */
	unsigned int num_passed;

	/** The number of failed tests */
	unsigned int num_failed;

	/** The number of tests that had errors */
	unsigned int num_errors;

	/** Whether to protect running tests from runtime errors */
	bool protect;

	/** Tests to run */
	Copper::List<Copper::Test> tests;
};

#endif /* OUTPUT_HANDLER_HPP */
