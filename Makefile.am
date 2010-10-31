ACLOCAL_AMFLAGS = -I autoconf/macro

# libcopper
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = copper.pc
lib_LTLIBRARIES = libcopper.la

libcopper_la_SOURCES = \
	copper/AssertionResult.cpp \
	copper/Assertions.cpp \
	copper/DefaultOutputHandler.cpp \
	copper/Error.cpp \
	copper/Failure.cpp \
	copper/FailureFormat.cpp \
	copper/Fixture.cpp \
	copper/ForkingTestRunner.cpp \
	copper/Formatters.cpp \
	copper/OutputHandler.cpp \
	copper/Protector.cpp \
	copper/Protectors/ExceptionProtector.cpp \
	copper/String.cpp \
	copper/Test.cpp \
	copper/TestRun.cpp \
	copper/TestRunner.cpp

# headers
include_copperdir = $(includedir)/copper-0
include_copper_HEADERS = copper/copper.hpp

include_copper_privdir = $(include_copperdir)/copper
include_copper_priv_HEADERS = \
	copper/AssertionResult.hpp \
	copper/Assertions.hpp \
	copper/compat.hpp \
	copper/DefaultOutputHandler.hpp \
	copper/Error.hpp \
	copper/Failure.hpp \
	copper/FailureFormat.hpp \
	copper/Fixture.hpp \
	copper/ForkingTestRunner.hpp \
	copper/Formatters.hpp \
	copper/FuncAttrs.hpp \
	copper/List.hpp \
	copper/macros.hpp \
	copper/OutputHandler.hpp \
	copper/Protector.hpp \
	copper/SafeException.hpp \
	copper/String.hpp \
	copper/Test.hpp \
	copper/TestRun.hpp \
	copper/TestRunner.hpp

# self-tests
TESTS = copper_tests
noinst_PROGRAMS = copper_tests

copper_tests_CPPFLAGS = -Icopper
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
