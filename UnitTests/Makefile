CXX=g++
CXXFLAGS=-Wall -Wextra -g3 -O0
RM=rm -f

OBJECTS= \
  build/assertion.o \
	build/error_exception.o \
	build/exception_protector.o \
  build/failure_exception.o \
  build/fixture.o \
  build/linux_protector.o \
  build/output_handler.o \
  build/protector.o \
  build/sample_suite.o \
  build/test.o \
  build/test_registry.o \

all: builddir tests

build/assertion.o: assertion.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/error_exception.o: error_exception.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/exception_protector.o: protectors/exception_protector.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/failure_exception.o: failure_exception.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/fixture.o: fixture.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/linux_protector.o: protectors/linux_protector.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/output_handler.o: output_handler.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/protector.o: protector.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/sample_suite.o: sample_suite.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

build/test_registry.o: test_registry.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

tests: $(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS) -o $@

builddir:
	@mkdir -p build

clean:
	$(RM) $(OBJECTS)
