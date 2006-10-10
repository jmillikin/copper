SUBDIRS=output_handlers protectors

lib_LTLIBRARIES = libunittests.la

libunittests_la_SOURCES = \
  assertion.cpp \
  assertion_result.cpp \
  assertions.cpp \
  error.cpp \
  fixture.cpp \
  output_handler.cpp \
  protector.cpp \
  suite.cpp \
  test.cpp

libunittests_la_LIBADD = \
  output_handlers/libunittests_output_handlers.la \
  protectors/libunittests_protectors.la
