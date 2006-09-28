/* gtk_output_handler.hpp -- Runs in a window constructed using GTK+
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef GTK_OUTPUT_HANDLER_HPP
#define GTK_OUTPUT_HANDLER_HPP

#include <gtk/gtk.h>

#include "../output_handler.hpp"

namespace UnitTests {

/**
  Use the GTK+ library to output to a window
*/
class GtkOutputHandler : public OutputHandler {
  friend gpointer run_tests(gpointer data);
public:
  /** Default constructor */
  GtkOutputHandler(int& argc, char**& argv) throw ();

  /** Default destructor */
  ~GtkOutputHandler() throw ();

  /**
    Marks a test as beginning

    @param test The test that just started
  */
  void begin(const Test* test) throw ();

  /**
    Marks a test as having passed

    @param test The test that just passed
  */
  void pass(const Test* test) throw ();

  /**
    Marks a test as having failed

    @param test The test that failed
    @param assetion The assertion that caused the test to fail
  */
  void fail(const Test* test, const Assertion* assertion) throw ();

  /**
    Marks a test as having errored out before completion

    @param test The test that failed
    @param error The error that was thrown
  */
  void error(const Test* test, const ErrorException& error) throw ();

  /** show the window, and start the GTK+ main loop */
  void run();

protected:
  /**
    Update labels and the progress bar, using thread synchronization if needed
  */
  void update() throw ();

  /** Update the list of tests to run */
  void find_tests() throw ();

  /** Reset for another round of tests */
  void reset() throw ();

  /** Main window of the test runner */
  GtkWindow* window;

  /** Shows the progress of running tests */
  GtkProgressBar* progress;

  /** Shows statistics about run tests */
  GtkLabel* statistics;

  /** List of test failures */
  GtkListStore* failure_list;

  /** Label for the failure list tab in the notebook */
  GtkLabel* failure_label;

  /** List of test errors */
  GtkListStore* error_list;

  /** Label for the error list tab in the notebook */
  GtkLabel* error_label;

  /** The button that begins the running of tests */
  GtkButton* test_execution_button;

  /** True if tests are currently being run */
  bool running_tests;

  /** If currently running tests, these are the tests that are being run */
  std::list<Test*> tests;

  /** Number of tests that have passed */
  unsigned int passed;

  /** Number of tests that have failed */
  unsigned int failures;

  /** Number of test that encountered an error */
  unsigned int errors;

  ///////////////////////////////////////
  //             Callbacks             //
  ///////////////////////////////////////

  static gboolean close_window(GtkWidget* widget, GdkEvent*, gpointer data)
    throw ();

  static void on_execute_button_clicked(GtkButton* button, gpointer data)
    throw ();
};

} /* namespace */

#endif /* GTK_OUTPUT_HANDLER_HPP */
