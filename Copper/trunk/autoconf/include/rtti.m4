AC_DEFUN([COPPER_CHECK_RTTI],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if RTTI is supported],
    [coppper_rtti_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <typeinfo>],
        [if (typeid(int).name()) return 0; else return 1;]
      )],
      [coppper_rtti_support=yes], # Test passed
      [coppper_rtti_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
