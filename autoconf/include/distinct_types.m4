AC_DEFUN([COPPER_CHECK_DISTINCT_BOOL],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if bool is a distinct type],
    [copper_cv_distinct_bool],
    [AC_RUN_IFELSE(
      [AC_LANG_PROGRAM(
        [void copper_test(unsigned char){}
         void copper_test(unsigned int){}
         void copper_test(int){}
         void copper_test(bool){}
        ],
        [return 0;]
      )],
      [copper_cv_distinct_bool=yes], # Test passed
      [copper_cv_distinct_bool=no],  # Test failed
      [copper_cv_distinct_bool=no],  # Cross compiling
    )]
  )

  AC_LANG_POP([C++])
])

AC_DEFUN([COPPER_CHECK_DISTINCT_SIZE_T],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if size_t is a distinct type],
    [copper_cv_distinct_size_t],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [#include <cstddef>
         void copper_test(unsigned int){}
         void copper_test(unsigned long){}
         void copper_test(std::size_t){}
        ],
        [return 0;]
      )],
      [copper_cv_distinct_size_t=yes], # Test passed
      [copper_cv_distinct_size_t=no],  # Test failed
      [copper_cv_distinct_size_t=no],  # Cross compiling
    )]
  )

  AC_LANG_POP([C++])
])
