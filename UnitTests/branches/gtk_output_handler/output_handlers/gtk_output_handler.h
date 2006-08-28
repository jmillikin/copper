#ifndef GTK_OUTPUT_HANDLER_H
#define GTK_OUTPUT_HANDLER_H

#include "../output_handler.h"
#include <gtk/gtk.h>

namespace UnitTests {

struct 

/**
  Use the GTK+ library to output to a window
*/
class GtkOutputHandler : public OutputHandler {
public:
  /** Default constructor */
  GtkOutputHandler() throw ();

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
    @param failure The failure that was thrown
  */
  void fail(const Test* test, const FailureException& failure)
    throw ();

  /**
    Marks a test as having errored out before completion

    @param test The test that failed
    @param error The error that was thrown
  */
  void error(const Test* test, const ErrorException& error) throw ();

protected:
};

} /* namespace */

#endif /* GTK_OUTPUT_HANDLER_H */
