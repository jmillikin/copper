SUBDIRS=Protectors

copper_include_HEADERS = copper.hpp
copper_include_real_HEADERS = \
	AssertionResult.hpp \
	Assertions.hpp \
	compat.hpp \
	copper.hpp \
	DefaultOutputHandler.hpp \
	Error.hpp \
	export.hpp \
	FailureFormat.hpp \
	Failure.hpp \
	Formatters.hpp \
	List.hpp \
	macros.hpp \
	OutputHandler.hpp \
	Protector.hpp \
	SafeException.hpp \
	String.hpp \
	Test.hpp \
	TestRunner.hpp \
	TestStatus.hpp


copper_includedir = $(includedir)/copper-0
copper_include_realdir = $(copper_includedir)/copper
EXTRA_DIST = $(copper_include_HEADERS) $(copper_include_real_HEADERS)

lib_LTLIBRARIES = libcopper.la

libcopper_la_SOURCES = \
	AssertionResult.cpp \
	Assertions.cpp \
	DefaultOutputHandler.cpp \
	Error.cpp \
	Failure.cpp \
	FailureFormat.cpp \
	Formatters.cpp \
	OutputHandler.cpp \
	Protector.cpp \
	String.cpp \
	Test.cpp \
	TestRunner.cpp \
	TestStatus.cpp

libcopper_la_LIBADD = Protectors/libcopper_protectors.la
