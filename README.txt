Copper: crash-proof unit tests for C and C++
=============================================

Copper is a library for unit-testing low-quality or unstable C/C++ code.
Each test is run in a separate process, so any errors occuring during testing
(such as segfaults or ``exit()``) will not prevent other tests from running.

Please e-mail any problems or suggestions to me at <jmillikin@gmail.com>.

See ``tests/sample_tests.cpp`` for examples of writing tests. Other files in
``tests/`` may be of interest also, though they are not as well commented.

Installing
----------

Use the standard UNIX install stanza ``./configure && make && make install``
to install Copper. Optionally, you may run the included self-tests with
``make check``. Copper does not have any dependencies aside from a reasonably
capable C++ compiler. If present, Copper will take advantage of advanced
features such as RTTI and ``std::stringstream``.

Copper is installed as a static library and set of header files; use
``$(pkg-config --cflags --libs copper)`` when compiling tests. For example,
after installing Copper, you may build and run the included sample tests with::

  $ g++ -o samples tests/sample_tests.cpp tests/main.cpp $(pkg-config --cflags --libs copper)
  $ ./samples
  FAILURE in tests/sample_tests.cpp:111:
  sample_suite.assertion_failure:
  	equal("the answer", "42")
  	"the answer" != "42"
  
  ERROR in tests/sample_tests.cpp:
  sample_suite.NULL_pointer_dereference:
  	Segmentation fault
  
  ERROR in tests/sample_tests.cpp:
  sample_suite.division_by_zero:
  	Floating point exception
  
  10 tests passed
  0 tests failed
  2 errors

Development
-----------

Copper's source code is versioned using Bazaar; to download a copy of the
latest code, run::

  $ bzr branch http://john-millikin.com/software/copper/

Building from scratch requires installation of the GNU Autotools.
