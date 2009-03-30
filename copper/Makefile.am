#SUBDIRS=Protectors

copper_include_HEADERS = copper.hpp
copper_include_real_HEADERS = \
	AssertionResult.hpp \
	Assertions.hpp \
	compat.hpp \
	copper.hpp \
	DefaultOutputHandler.hpp \
	Error.hpp \
	Failure.hpp \
	FailureFormat.hpp \
	ForkingTestRunner.hpp \
	Formatters.hpp \
	FuncAttrs.hpp \
	List.hpp \
	macros.hpp \
	OutputHandler.hpp \
	Protector.hpp \
	SafeException.hpp \
	String.hpp \
	Test.hpp \
	TestRun.hpp \
	TestRunner.hpp


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
	ForkingTestRunner.cpp \
	Formatters.cpp \
	OutputHandler.cpp \
	Protector.cpp \
	String.cpp \
	Test.cpp \
	TestRun.cpp \
	TestRunner.cpp

#libcopper_la_LIBADD = Protectors/libcopper_protectors.la
