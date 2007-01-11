INCLUDES = -I$(top_srcdir)/include

# Used for 'make check'
check_PROGRAMS=run_tests
run_tests_SOURCES=\
  assertion_tests.cpp \
  string_tests.cpp \
  format_tests.cpp \
  main.cpp \
  output_handler.cpp \
  self_tests.cpp

run_tests_LDADD = ../src/libcu.la

check:
	./run_tests
