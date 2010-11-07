ACLOCAL_AMFLAGS = -I autoconf/macro

# libcopper
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = copper.pc
lib_LTLIBRARIES = libcopper.la

libcopper_la_CPPFLAGS = -I $(top_srcdir)/include/ -I ./include/
libcopper_la_SOURCES = \
	src/AssertionResult.cpp \
	src/Assertions.cpp \
	src/driver/BatchDriver.cpp \
	src/repr.cpp \
	src/String.cpp \
	src/Test.cpp \
	src/TestRun.cpp

# headers
include_copperdir = $(includedir)/copper0.5
include_copper_HEADERS = include/copper.hpp

include_copper_privdir = $(include_copperdir)/copper
include_copper_priv_HEADERS = \
	include/copper/AssertionResult.hpp \
	include/copper/Assertions.hpp \
	include/copper/config.h \
	include/copper/List.hpp \
	include/copper/macros.hpp \
	include/copper/repr.hpp \
	include/copper/String.hpp \
	include/copper/Test.hpp \
	include/copper/TestRun.hpp

include_copper_driverdir = $(include_copperdir)/copper/driver
include_copper_driver_HEADERS = \
	include/copper/driver/BatchDriver.hpp

# self-tests
TESTS = copper_tests
check_PROGRAMS = copper_tests

copper_tests_CPPFLAGS = -I $(top_srcdir)/include/ -I ./include/
copper_tests_LDADD = libcopper.la
copper_tests_SOURCES = \
	tests/assertion_tests.cpp \
	tests/repr_tests.cpp \
	tests/list_tests.cpp \
	tests/main.cpp \
	tests/self_tests.cpp \
	tests/string_tests.cpp
