ACLOCAL_AMFLAGS = -I autoconf/macro

# libcopper
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = copper.pc
lib_LTLIBRARIES = libcopper.la

libcopper_la_CPPFLAGS = -I $(top_srcdir)/include/ -I ./include/
libcopper_la_SOURCES = \
	src/AssertionResult.cpp \
	src/Assertions.cpp \
	src/DefaultOutputHandler.cpp \
	src/Error.cpp \
	src/ExceptionProtector.cpp \
	src/Failure.cpp \
	src/FailureFormat.cpp \
	src/Fixture.cpp \
	src/ForkingTestRunner.cpp \
	src/Formatters.cpp \
	src/OutputHandler.cpp \
	src/Protector.cpp \
	src/String.cpp \
	src/Test.cpp \
	src/TestRun.cpp \
	src/TestRunner.cpp

# headers
include_copperdir = $(includedir)/copper-0
include_copper_HEADERS = include/copper.hpp

include_copper_privdir = $(include_copperdir)/copper
include_copper_priv_HEADERS = \
	include/copper/AssertionResult.hpp \
	include/copper/Assertions.hpp \
	include/copper/config.h \
	include/copper/DefaultOutputHandler.hpp \
	include/copper/Error.hpp \
	include/copper/Failure.hpp \
	include/copper/FailureFormat.hpp \
	include/copper/Fixture.hpp \
	include/copper/ForkingTestRunner.hpp \
	include/copper/Formatters.hpp \
	include/copper/FuncAttrs.hpp \
	include/copper/List.hpp \
	include/copper/macros.hpp \
	include/copper/OutputHandler.hpp \
	include/copper/Protector.hpp \
	include/copper/SafeException.hpp \
	include/copper/String.hpp \
	include/copper/Test.hpp \
	include/copper/TestRun.hpp \
	include/copper/TestRunner.hpp

# self-tests
TESTS = copper_tests
check_PROGRAMS = copper_tests

copper_tests_CPPFLAGS = -I $(top_srcdir)/include/ -I ./include/
copper_tests_LDADD = libcopper.la
copper_tests_SOURCES = \
	tests/argument_parser_tests.cpp \
	tests/assertion_tests.cpp \
	tests/failure_format_tests.cpp \
	tests/format_tests.cpp \
	tests/list_tests.cpp \
	tests/main.cpp \
	tests/self_tests.cpp \
	tests/string_tests.cpp
