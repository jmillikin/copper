INCLUDES = -I$(top_srcdir)/include

SUBDIRS=protectors util

lib_LTLIBRARIES = libcu.la

libcu_la_SOURCES = \
  assertion.cpp \
  assertion_result.cpp \
  assertions.cpp \
  error.cpp \
  output_handler.cpp \
  protector.cpp \
  suite.cpp \
  test.cpp \
  test_status.cpp

libcu_la_LIBADD = protectors/libcu_protectors.la util/libcu_util.la
