AC_DEFUN([COPPER_CHECK_VARIADIC_MACROS],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if C99 variadic macros are supported],
    [coppper_variadic_macro_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#define test(...) return __VA_ARGS__],
        [test(0);]
      )],
      [coppper_variadic_macro_support=yes], # Test passed
      [coppper_variadic_macro_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
