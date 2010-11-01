AC_DEFUN([COPPER_CHECK_EXCEPTIONS],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if exceptions are supported],
    [copper_cv_exception_support],
    [AC_RUN_IFELSE(
      [AC_LANG_PROGRAM(
        [],
        [try { throw 0; } catch (int i) { return i; }]
      )],
      [copper_exception_support=yes], # Test passed
      [copper_exception_support=no],  # Test failed
      [copper_exception_support=no],  # Cross compiling
    )]
  )

  AC_LANG_POP([C++])
])
