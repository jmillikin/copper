/* qt4_output_handler.hpp -- Runs in a window constructed using QT 4
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef QT4_OUTPUT_HANDLER_HPP
#define QT4_OUTPUT_HANDLER_HPP

#include <QApplication>
#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QTabWidget>
#include <QStandardItemModel>
#include <QPushButton>
#include <list>
#include "../output_handler.hpp"

namespace UnitTests {

class Qt4OutputHandler;

/** Output to a window constructed with Qt 4 */
class Qt4OutputHandler_Window : public QMainWindow {
  Q_OBJECT
public:
  /** Default constructor */
  Qt4OutputHandler_Window(Qt4OutputHandler* handler) throw ();

  /** Default destructor */
  ~Qt4OutputHandler_Window() throw ();

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

  /** show the window, and start the QApplication */
  void run();

protected:
  /** Update the list of tests to run */
  std::list<Test*> find_tests() throw ();

  /** Reset for another round of tests */
  void reset() throw ();

  /** Interfaces with the normal OutputHandler functions */
  Qt4OutputHandler* handler;

  /** Shows the progress of running tests */
  QProgressBar* progress;

  /** Shows statistics about run tests */
  QLabel* statistics;

  /** Contains two tabs, one for failed tests and one for errors */
  QTabWidget* result_tabs;

  /** List of test failures */
  QStandardItemModel* failure_list;

  /** Index of the failure list tab in the tab widget */
  int failure_tab_index;

  /** List of test errors */
  QStandardItemModel* error_list;

  /** Index of the error list tab in the tab widget */
  int error_tab_index;

  /** The button that begins the running of tests */
  QPushButton* test_execution_button;

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

protected slots:
  /**
    Update labels and the progress bar, using thread synchronization if
    needed
  */
  void do_update() throw ();

  /** Called to begin running tests */
  void run_tests();

  /** Called when all tests have finished */
  void tests_finished();

signals:
  /** Called to update the window, the next time the GUI thread is available */
  void update_window();
};

class Qt4OutputHandler: public OutputHandler {
  friend class TestRunner;
public:
  Qt4OutputHandler(int& argc, char**& argv);
  ~Qt4OutputHandler();
  void begin(const Test* test) throw ();
  void pass(const Test* test) throw ();
  void fail(const Test* test, const Assertion* assertion) throw ();
  void error(const Test* test, const ErrorException& error) throw ();
  void run();
  
protected:
  QApplication app;
  Qt4OutputHandler_Window* window;
};

} /* namespace */

#endif /* QT4_OUTPUT_HANDLER_HPP */
