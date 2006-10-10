SUBDIRS = src

# Used for 'make check'
check_PROGRAMS=run_self_tests
run_self_tests_SOURCES=\
  tests/main.cpp \
  tests/self_tests.cpp

run_self_tests_LDADD = src/libunittests.la

check:
	./run_self_tests
