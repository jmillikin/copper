AC_DEFUN([COPPER_CHECK_SIGBUS],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if SIGBUS is supported],
    [coppper_sigbus_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <csignal>],
        [if (SIGBUS == SIGBUS) return 0; else return 1;]
      )],
      [coppper_sigbus_support=yes], # Test passed
      [coppper_sigbus_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
