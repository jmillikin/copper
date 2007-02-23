AC_DEFUN([COPPER_CHECK_EXCEPTIONS],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if exceptions are supported],
    [coppper_exception_support],
    [AC_RUN_IFELSE(
      [AC_LANG_PROGRAM(
        [],
        [try { throw 0; } catch (int i) { return i; }]
      )],
      [coppper_exception_support=yes], # Test passed
      [coppper_exception_support=no],  # Test failed
      [coppper_exception_support=no],  # Cross compiling
    )]
  )

  AC_LANG_POP([C++])
])
