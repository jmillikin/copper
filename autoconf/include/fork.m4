AC_DEFUN([COPPER_CHECK_FORK],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if fork is supported],
    [copper_cv_fork_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <sys/types.h>
         #include <unistd.h>],
        [if (fork) return 0; else return 1;]
      )],
      [copper_fork_support=yes], # Test passed
      [copper_fork_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
