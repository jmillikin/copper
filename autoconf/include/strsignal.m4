AC_DEFUN([COPPER_CHECK_STRSIGNAL],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if strsignal is supported],
    [copper_cv_strsignal_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <cstring>],
        [if (strsignal) return 0; else return 1;]
      )],
      [copper_cv_strsignal_support=yes], # Test passed
      [copper_cv_strsignal_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
