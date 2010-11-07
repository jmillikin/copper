AC_DEFUN([COPPER_CHECK_CONST_WRITE],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if write(const char *) is supported],
    [copper_cv_const_write],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <unistd.h>],
        [const char *buf = "";
        write(0, buf, 0);
        return 0;
        ]
      )],
      [copper_cv_const_write=yes], # Test passed
      [copper_cv_const_write=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
