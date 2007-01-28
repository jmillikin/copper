AC_DEFUN([COPPER_CHECK_BOOLEAN],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if booleans are a distinct type],
    [coppper_boolean_support],
    [AC_RUN_IFELSE(
      [AC_LANG_PROGRAM(
        [],
        [bool b = 5; if (b == 5) return 1; else return 0;]
      )],
      [coppper_boolean_support=yes], # Test passed
      [coppper_boolean_support=no],  # Test failed
      [coppper_boolean_support=no],  # Cross compiling
    )]
  )

  AC_LANG_POP([C++])
])
