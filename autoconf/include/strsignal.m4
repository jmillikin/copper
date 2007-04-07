AC_DEFUN([COPPER_CHECK_STRSIGNAL],[
  AC_LANG_PUSH([C])

  AC_CACHE_CHECK(
    [if strsignal is supported],
    [coppper_strsignal_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#ifndef _GNU_SOURCE
         #  define _GNU_SOURCE
         #endif
         #include <string.h>],
        [if (strsignal) return 0; else return 1;]
      )],
      [coppper_strsignal_support=yes], # Test passed
      [coppper_strsignal_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C])
])
