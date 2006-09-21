#include <QVBoxLayout>
#include <QThread>
#include <QTreeView>
#include "qt4_output_handler.h"
#include "../test.h"
#include "../error_exception.h"

namespace UnitTests {

/** List of columns in the failure list */
enum FailureListColumns {
  FAILURE_COL_SUITE = 0,/**< Test suite name */
  FAILURE_COL_TEST,     /**< Test name */
  FAILURE_COL_FILE,     /**< File the test is in */
  FAILURE_COL_LINE,     /**< Line the assertion is on */
  FAILURE_COL_MESSAGE,  /**< Failure message */
  FAILURE_N_COLS        /**< Number of columns in the failure list */
};

/** And their titles */
static const char* failure_column_titles[FAILURE_N_COLS] = {
  "Suite", "Test", "File", "Line", "Message"
};

/** List of columns in the error list */
enum ErrorListColumns {
  ERROR_COL_SUITE = 0,/**< Test suite name */
  ERROR_COL_TEST,     /**< Test name */
  ERROR_COL_FILE,     /**< File the test is in */
  ERROR_COL_MESSAGE,  /**< Error message */
  ERROR_N_COLS        /**< Number of columns in the error list */
};

/** And their titles */
static const char* error_column_titles[ERROR_N_COLS] = {
  "Suite", "Test", "File", "Message"
};

Qt4OutputHandler_Window::Qt4OutputHandler_Window(
  Qt4OutputHandler* _handler) throw ():
  handler(_handler), running_tests(false) {

  setWindowTitle("Graphical Unit Test Runner");
  resize(600, 400);

  QWidget* central_widget = new QWidget(this);
  setCentralWidget(central_widget);
  QVBoxLayout* vbox = new QVBoxLayout(central_widget);

  // Button to begin testing
  test_execution_button = new QPushButton("Begin Tests", central_widget);
  vbox->addWidget(test_execution_button);
  connect(test_execution_button, SIGNAL(clicked(bool)),
    this, SLOT(run_tests()));

  // Progress bar
  progress = new QProgressBar(central_widget);
  progress->setMinimum(0);
  progress->setMaximum(1);
  progress->setValue(0);
  vbox->addWidget(progress);

  // Shows statistics after completed test runs
  statistics = new QLabel(central_widget);
  vbox->addWidget(statistics);

  // Contains two tabs, one for failed tests and one for errors
  result_tabs = new QTabWidget(central_widget);

  // List of failed tests
  failure_list = new QStandardItemModel(0, 0, central_widget);
  QTreeView* failure_list_view = new QTreeView();
  failure_list_view->setModel(failure_list);
  failure_list_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

  failure_tab_index = result_tabs->addTab(failure_list_view,
    "Failures (0)");

  // List of tests that encountered an error during execution
  error_list = new QStandardItemModel(0, 0, central_widget);
  QTreeView* error_list_view = new QTreeView();
  error_list_view->setModel(error_list);
  error_list_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

  error_tab_index = result_tabs->addTab(error_list_view,
    "Errors (0)");

  vbox->addWidget(result_tabs);

  connect(this, SIGNAL(update_window()), this, SLOT(do_update()));

  // Allow QModelIndex to be passed between threads in signals
  qRegisterMetaType<QModelIndex>("QModelIndex");

  // Initialize the view
  reset();
}

Qt4OutputHandler_Window::~Qt4OutputHandler_Window() throw () {
}

void Qt4OutputHandler_Window::begin(const Test* test) throw () {
  update_window();
}

void Qt4OutputHandler_Window::pass(const Test*) throw () {
  passed++;
  update_window();
}

void Qt4OutputHandler_Window::fail(const Test* test,
  const FailureException& failure) throw () {

  int new_row = failure_list->rowCount();
  failure_list->insertRows(new_row, 1);
  QModelIndex idx;

  idx = failure_list->index(new_row, FAILURE_COL_SUITE);
  failure_list->setData(idx, test->suite->name.c_str());

  idx = failure_list->index(new_row, FAILURE_COL_TEST);
  failure_list->setData(idx, test->name.c_str());

  idx = failure_list->index(new_row, FAILURE_COL_FILE);
  failure_list->setData(idx, test->file_name.c_str());

  idx = failure_list->index(new_row, FAILURE_COL_LINE);
  failure_list->setData(idx, failure.line);

  idx = failure_list->index(new_row, FAILURE_COL_MESSAGE);
  failure_list->setData(idx, failure.message.c_str());

  failures++;
  update_window();
}

void Qt4OutputHandler_Window::error(const Test* test,
  const ErrorException& error) throw () {

  int new_row = error_list->rowCount();
  error_list->insertRows(new_row, 1);
  QModelIndex idx;

  idx = error_list->index(new_row, ERROR_COL_SUITE);
  error_list->setData(idx, test->suite->name.c_str());

  idx = error_list->index(new_row, ERROR_COL_TEST);
  error_list->setData(idx, test->name.c_str());

  idx = error_list->index(new_row, ERROR_COL_FILE);
  error_list->setData(idx, test->file_name.c_str());

  idx = error_list->index(new_row, ERROR_COL_MESSAGE);
  error_list->setData(idx, error.message.c_str());

  errors++;
  update_window();
}

void Qt4OutputHandler_Window::run() {
  show();
  progress->hide();
  statistics->hide();
  qApp->exec();
}

std::list<Test*> Qt4OutputHandler_Window::find_tests() throw () {
  std::list<Test*> tests;

  std::list<Suite*> suites = Suite::all_suites();
  std::list<Suite*>::const_iterator suite;
  for (suite = suites.begin(); suite != suites.end(); suite++) {

    std::list<Test*> suite_tests = (*suite)->get_tests();
    std::list<Test*>::const_iterator test;
    for (test = suite_tests.begin(); test != suite_tests.end(); test++) {
      tests.push_back(*test);
    }
  }

  return tests;
}

void Qt4OutputHandler_Window::reset() throw () {
  // Reset counts of passed, failures, and errors
  passed = 0;
  failures = 0;
  errors = 0;

  // Clear the lists of failures and errors
  failure_list->clear();
  error_list->clear();

  // Re-add columns
  failure_list->insertColumns(0, FAILURE_N_COLS);
  for (unsigned int ii = 0; ii < FAILURE_N_COLS; ii++) {
    failure_list->setHeaderData(ii, Qt::Horizontal,
      failure_column_titles[ii]);
  }

  error_list->insertColumns(0, ERROR_N_COLS);
  for (unsigned int ii = 0; ii < ERROR_N_COLS; ii++) {
    error_list->setHeaderData(ii, Qt::Horizontal,
      error_column_titles[ii]);
  }

  // Show the progress bar
  progress->show();

  // Hide previous statistics
  statistics->hide();
}

void Qt4OutputHandler_Window::do_update() throw () {
  // Update the progress bar
  progress->setValue(passed + failures + errors);
  
  // Update titles of the failure and error list tabs
  QString failure_string = QString("Failures (%1)").arg(failures);
  result_tabs->setTabText(failure_tab_index, failure_string);

  QString error_string = QString("Errors (%1)").arg(errors);
  result_tabs->setTabText(error_tab_index, error_string);
}

/** Small class to run tests in a separate thread */
class TestRunner : public QThread {
public:
  TestRunner(Qt4OutputHandler* _handler, const std::list<Test*> _tests):
    handler(_handler), tests(_tests) {}

  void run() {
    std::list<Test*>::const_iterator test;
    for (test = tests.begin(); test != tests.end(); test++) {
      handler->run_test(*test);
    }
  }

protected:
  Qt4OutputHandler* handler;
  const std::list<Test*> tests;
};

void Qt4OutputHandler_Window::run_tests() {
  test_execution_button->setEnabled(false);
  running_tests = true;
  std::list<Test*> tests = find_tests();
  reset();
  progress->setMaximum(tests.size());
  TestRunner* runner = new TestRunner(handler, tests);
  connect(runner, SIGNAL(finished()), this, SLOT(tests_finished()));
  runner->start();
}

void Qt4OutputHandler_Window::tests_finished() {
  progress->hide();

  // Show statistics about the test
  unsigned int test_count = passed + failures + errors;
  QString statistics_string = QString("%1 of %2 tests passed (%3%)")
    .arg(passed).arg(test_count)
    .arg(static_cast<double>(passed) / static_cast<double>(test_count) * 100);
  statistics->setText(statistics_string);
  statistics->show();
  test_execution_button->setEnabled(true);
  running_tests = false;
}

Qt4OutputHandler::Qt4OutputHandler(int& argc, char**& argv):
  OutputHandler(), app(argc, argv) {
  window = new Qt4OutputHandler_Window(this);
}

Qt4OutputHandler::~Qt4OutputHandler() {
  delete window;
}

void Qt4OutputHandler::begin(const Test* test) throw () {
  window->begin(test);
}

void Qt4OutputHandler::pass(const Test* test) throw () {
  window->pass(test);
}

void Qt4OutputHandler::fail(const Test* test,
  const FailureException& failure) throw () {

  window->fail(test, failure);
}

void Qt4OutputHandler::error(const Test* test,
  const ErrorException& error) throw () {

  window->error(test, error);
}

void Qt4OutputHandler::run() { window->run(); }

} /* namespace */
