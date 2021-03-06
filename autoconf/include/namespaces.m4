AC_DEFUN([COPPER_CHECK_NAMESPACES],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if namespaces are supported],
    [copper_cv_namespace_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [namespace foo { int bar = 0; }],
        [return foo::bar;]
      )],
      [copper_cv_namespace_support=yes], # Test passed
      [copper_cv_namespace_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])

  if test "$copper_cv_namespace_support" = "no"; then
    AC_MSG_ERROR([Namespace support is required for compiling Copper])
  fi
])
