INCLUDES = -I$(top_srcdir)/copper

# Used for 'make check'
check_PROGRAMS=run_tests
run_tests_SOURCES=\
  argument_parser_tests.cpp \
  assertion_tests.cpp \
  string_tests.cpp \
  format_tests.cpp \
  main.cpp \
  self_tests.cpp

run_tests_LDADD = ../copper/libcu.la

check:
	./run_tests
