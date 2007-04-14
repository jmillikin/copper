SUBDIRS=protectors util

#################################################
##########           Headers           ##########
#################################################
copper_include_HEADERS = copper.hpp
copper_include_real_HEADERS = \
  assertion.hpp \
  assertion_result.hpp \
  assertions.hpp \
  compat.hpp \
  error.hpp \
  macros.hpp \
  output_handler.hpp \
  protector.hpp \
  safe_exception.hpp \
  suite.hpp \
  test.hpp \
  test_runner.hpp \
  test_status.hpp

copper_includedir = $(includedir)/copper-0
copper_include_realdir = $(copper_includedir)/copper
EXTRA_DIST = $(copper_include_HEADERS) $(copper_include_real_HEADERS)

#################################################
##########        Source files         ##########
#################################################
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
  test_runner.cpp \
  test_status.cpp

libcu_la_LIBADD = protectors/libcu_protectors.la util/libcu_util.la
