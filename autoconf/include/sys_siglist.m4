AC_DEFUN([COPPER_CHECK_SYS_SIGLIST],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if sys_siglist is supported],
    [copper_cv_sys_siglist_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <signal.h>],
        [if (sys_siglist) return 0; else return 1;]
      )],
      [copper_cv_sys_siglist_support=yes], # Test passed
      [copper_cv_sys_siglist_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
