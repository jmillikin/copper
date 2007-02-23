AC_DEFUN([COPPER_CHECK_TEMPLATES],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if templates are supported],
    [coppper_template_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [
          template<class C>
          class Test {
          public:
            Test(){}
            ~Test(){}
            int func() { return 0; }
          };
        ],
        [Test<int> test; return test.func();]
      )],
      [coppper_template_support=yes], # Test passed
      [coppper_template_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
  if test "$coppper_template_support" = "no"; then
    AC_MSG_ERROR([Template support is required for compiling Copper])
  fi
])
