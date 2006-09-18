#include "gtk_output_handler.h"
#include "../test.h"
#include "../error_exception.h"

namespace UnitTests {

GtkOutputHandler::GtkOutputHandler() throw ():
  OutputHandler() {

  window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
  progress = GTK_PROGRESS_BAR(gtk_progress_bar_new());

  
}

GtkOutputHandler::~GtkOutputHandler() throw () {
  gtk_widget_destroy(GTK_WIDGET(window));
}

void GtkOutputHandler::begin(const Test*) throw () {}

void GtkOutputHandler::pass(const Test*) throw () {}

void GtkOutputHandler::fail(const Test* test,
  const FailureException& failure) throw () {}

void GtkOutputHandler::error(const Test* test,
  const ErrorException& error) throw () {}

} /* namespace */
