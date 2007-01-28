AC_DEFUN([COPPER_CHECK_STATIC_CAST],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if static_cast is supported],
    [coppper_static_cast_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [],
        [char i = 0; return static_cast<int>(i);]
      )],
      [coppper_static_cast_support=yes], # Test passed
      [coppper_static_cast_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])

  if test "$coppper_static_cast_support" = "no"; then
    AC_MSG_ERROR([static_cast support is required for compiling Copper])
  fi
])
