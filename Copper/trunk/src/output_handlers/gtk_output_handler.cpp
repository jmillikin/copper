/* gtk_output_handler.cpp -- Runs in a window constructed using GTK+
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "gtk_output_handler.hpp"
#include "../export.hpp"

namespace Copper {

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

// Run all tests
gpointer run_tests(gpointer data) {
  GtkOutputHandler* handler = reinterpret_cast<GtkOutputHandler*>(data);

  std::list<Test*> tests = handler->tests;
  std::list<Test*>::const_iterator test;
  for (test = tests.begin(); test != tests.end(); test++) {
    g_thread_yield();
    handler->run_test(*test);
  }

  return NULL;
}

gboolean GtkOutputHandler::close_window(GtkWidget*, GdkEvent*, gpointer data)
  throw () {

  GtkOutputHandler* handler = reinterpret_cast<GtkOutputHandler*>(data);

  if (handler->running_tests) {
    // Show confirmation dialog to the user
    return true;
  }

  return false;
}

void GtkOutputHandler::on_execute_button_clicked(GtkButton* button,
  gpointer data) throw () {

  GtkOutputHandler* handler = reinterpret_cast<GtkOutputHandler*>(data);

  if (!handler->running_tests) {
    // Disable test runner button until tests have finished running
    gtk_widget_set_sensitive(GTK_WIDGET(button), false);
    handler->running_tests = true;

    // Find all tests that need to be run
    handler->find_tests();

    handler->reset();

    // If possible, run tests in a separate thread to avoid blocking the UI
    if (g_thread_supported()) {
      GThread* thread = g_thread_create(run_tests, handler, false, NULL);
    }

    // Otherwise, run all tests in the main thread
    else {
      run_tests(handler);
    }
  }
}

EXPORT GtkOutputHandler::GtkOutputHandler(int& argc, char**& argv) throw ():
  OutputHandler(argc, argv), running_tests(false) {

  if (!g_thread_supported()) {
    g_thread_init(NULL);
    gdk_threads_init();
  }
  gtk_init(&argc, &argv);

  window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
  gtk_window_set_title(window, "Graphical Unit Test Runner");
  gtk_window_set_default_size(window, 600, 400);

  g_signal_connect(G_OBJECT(window), "delete_event",
    G_CALLBACK (close_window), this);

  g_signal_connect(G_OBJECT(window), "destroy",
    G_CALLBACK (gtk_main_quit), this);

  GtkWidget* vbox = gtk_vbox_new(false, 5);

  // Button to begin testing
  test_execution_button = GTK_BUTTON(
    gtk_button_new_from_stock(GTK_STOCK_EXECUTE));
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(test_execution_button),
    false, false, 5);
  g_signal_connect(G_OBJECT(test_execution_button), "clicked",
    G_CALLBACK (on_execute_button_clicked), this);

  // Progress bar
  progress = GTK_PROGRESS_BAR(gtk_progress_bar_new());
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(progress), false, false, 5);
  gtk_progress_bar_set_fraction(progress, 0);

  // Shows statistics after completed test runs
  statistics = GTK_LABEL(gtk_label_new(""));
  gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(statistics), false, false, 5);

  // Contains two tabs, one for failed tests and one for errors
  GtkWidget* results = gtk_notebook_new();

  // List of failed tests
  failure_list = gtk_list_store_new(FAILURE_N_COLS,
    G_TYPE_STRING, /* Test suite name */
    G_TYPE_STRING, /* Test name */
    G_TYPE_STRING, /* File the test is in */
    G_TYPE_UINT,   /* Line the assertion is on */
    G_TYPE_STRING  /* Failure message */
  );
  GtkWidget* failure_list_view = gtk_tree_view_new_with_model(
    GTK_TREE_MODEL(failure_list));

  // Add columns to the failure list view
  GtkTreeViewColumn* column;
  GtkCellRenderer* renderer;

  for (unsigned int ii = 0; ii < FAILURE_N_COLS; ii++) {
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes (
      failure_column_titles[ii], renderer, "text", ii, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(failure_list_view), column);
  }

  failure_label = GTK_LABEL(gtk_label_new("Failures (0)"));
  gtk_notebook_append_page(GTK_NOTEBOOK(results), failure_list_view,
    GTK_WIDGET(failure_label));

  // List of tests that encountered an error during execution
  error_list = gtk_list_store_new(ERROR_N_COLS,
    G_TYPE_STRING, /* Test suite name */
    G_TYPE_STRING, /* Test name */
    G_TYPE_STRING, /* File the test is in */
    G_TYPE_STRING  /* Error message */
  );

  GtkWidget* error_list_view = gtk_tree_view_new_with_model(
    GTK_TREE_MODEL(error_list));

  for (unsigned int ii = 0; ii < ERROR_N_COLS; ii++) {
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes (
      error_column_titles[ii], renderer, "text", ii, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(error_list_view), column);
  }

  error_label = GTK_LABEL(gtk_label_new("Errors (0)"));
  gtk_notebook_append_page(GTK_NOTEBOOK(results), error_list_view,
    GTK_WIDGET(error_label));

  gtk_box_pack_start(GTK_BOX(vbox), results, true, true, 5);
  gtk_container_add(GTK_CONTAINER(window), vbox);
}

EXPORT GtkOutputHandler::~GtkOutputHandler() throw () {
  //gtk_widget_destroy(GTK_WIDGET(window));
}

void GtkOutputHandler::begin(const Test* test) throw () {
  gdk_threads_enter();
  // Set the text of the progress bar
  gchar* progress_text = g_strdup_printf("%s::%s",
    test->suite->name, test->name);
  gtk_progress_bar_set_text(progress, progress_text);
  g_free(progress_text);

  gdk_threads_leave();
}

void GtkOutputHandler::pass(const Test*) throw () {
  passed++;
  update();
}

void GtkOutputHandler::fail(const Test* test,
  const Assertion* assertion) throw () {


  GtkTreeIter iter;
  gtk_list_store_append (failure_list, &iter);
  gtk_list_store_set (failure_list, &iter,
    FAILURE_COL_SUITE, pretty_name(test->suite->name).c_str(),
    FAILURE_COL_TEST, pretty_name(test->name).c_str(),
    FAILURE_COL_FILE, test->file_name,
    FAILURE_COL_LINE, assertion->line(),
    FAILURE_COL_MESSAGE, assertion->failure_message(),
    -1);

  failures++;
  update();
}

void GtkOutputHandler::error(const Test* test,
  const Error* error) throw () {

  GtkTreeIter iter;
  gtk_list_store_append (error_list, &iter);
  gtk_list_store_set (error_list, &iter,
    ERROR_COL_SUITE, pretty_name(test->suite->name).c_str(),
    ERROR_COL_TEST, pretty_name(test->name).c_str(),
    ERROR_COL_FILE, test->file_name,
    ERROR_COL_MESSAGE, error->message,
    -1);

  errors++;
  update();
}

EXPORT int GtkOutputHandler::run() {
  gtk_widget_show_all(GTK_WIDGET(window));
  gtk_widget_hide(GTK_WIDGET(progress));
  gtk_widget_hide(GTK_WIDGET(statistics));
  gtk_main();

  return failures + errors;
}

void GtkOutputHandler::update() throw () {
  gdk_threads_enter();

  // Update the progress bar
  double percent_done = static_cast<double>(passed + failures + errors) /
    static_cast<double>(tests.size());
  gtk_progress_bar_set_fraction(progress, percent_done);

  // Update titles of the failure and error list tabs
  gchar* failure_string = g_strdup_printf("Failures (%u)", failures);
  gtk_label_set_text(failure_label, failure_string);
  g_free(failure_string);

  gchar* error_string = g_strdup_printf("Errors (%u)", errors);
  gtk_label_set_text(error_label, error_string);
  g_free(error_string);

  // If the test run has completed, re-enable the 'Execute' button and
  // show statistics about the test
  if (passed + failures + errors >= tests.size()) {
    gtk_widget_hide(GTK_WIDGET(progress));
    gtk_widget_set_sensitive(GTK_WIDGET(test_execution_button), true);

    gchar* statistics_string = g_strdup_printf(
      "%u of %u tests passed (%lg%%)", passed, tests.size(),
      (static_cast<double>(passed) / static_cast<double>(tests.size()) * 100.0)
    );
    gtk_label_set_text(statistics, statistics_string);
    g_free(statistics_string);
    gtk_widget_show(GTK_WIDGET(statistics));

    running_tests = false;
  }

  gdk_threads_leave();
}

void GtkOutputHandler::find_tests() throw () {
  tests.clear();

  std::list<Suite*> suites = Suite::all_suites();
  std::list<Suite*>::const_iterator suite;
  for (suite = suites.begin(); suite != suites.end(); suite++) {

    std::list<Test*> suite_tests = (*suite)->get_tests();
    std::list<Test*>::const_iterator test;
    for (test = suite_tests.begin(); test != suite_tests.end(); test++) {
      tests.push_back(*test);
    }
  }
}

void GtkOutputHandler::reset() throw () {
  // Reset counts of passed, failures, and errors
  passed = 0;
  failures = 0;
  errors = 0;

  // Clear the lists of failures and errors
  gtk_list_store_clear(failure_list);
  gtk_list_store_clear(error_list);

  // Show the progress bar
  gtk_progress_bar_set_fraction(progress, 0);
  gtk_widget_show(GTK_WIDGET(progress));

  // Hide previous statistics
  gtk_widget_hide(GTK_WIDGET(statistics));
}

} /* namespace */
