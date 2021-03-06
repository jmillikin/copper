AC_DEFUN([COPPER_CHECK_SSTREAM],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if sstream is supported],
    [copper_cv_sstream_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <sstream>],
        [
          std::stringstream ss;
          int i;
          ss << 0;
          ss >> i;
          return i;
        ]
      )],
      [copper_cv_sstream_support=yes], # Test passed
      [copper_cv_sstream_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
