SUBDIRS=protectors util

#################################################
##########           Headers           ##########
#################################################
copper_include_HEADERS = copper.hpp
copper_include_real_HEADERS = \
  assertion_result.hpp \
  assertions.hpp \
  compat.hpp \
  default_output_handler.hpp \
  error.hpp \
  export.hpp \
  failure.hpp \
  failure_format.hpp \
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
lib_LTLIBRARIES = libcopper.la

libcopper_la_SOURCES = \
  assertion_result.cpp \
  assertions.cpp \
  default_output_handler.cpp \
  error.cpp \
  failure.cpp \
  failure_format.cpp \
  output_handler.cpp \
  protector.cpp \
  suite.cpp \
  test.cpp \
  test_runner.cpp \
  test_status.cpp

libcopper_la_LIBADD = protectors/libcopper_protectors.la util/libcopper_util.la
