AC_DEFUN([COPPER_CHECK_STD_STRING],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if std::string is supported],
    [coppper_std_string_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <string>],
        [
          std::string s;
          return s.size ();
        ]
      )],
      [coppper_std_string_support=yes], # Test passed
      [coppper_std_string_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
