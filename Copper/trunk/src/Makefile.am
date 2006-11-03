SUBDIRS=output_handlers protectors

lib_LTLIBRARIES = libcu.la

libcu_la_SOURCES = \
  assertion.cpp \
  assertion_result.cpp \
  assertions.cpp \
  error.cpp \
  fixture.cpp \
  output_handler.cpp \
  protector.cpp \
  suite.cpp \
  test.cpp

libcu_la_LIBADD = \
  output_handlers/libcu_output_handlers.la \
  protectors/libcu_protectors.la
