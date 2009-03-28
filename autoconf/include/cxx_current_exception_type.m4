AC_DEFUN([COPPER_CHECK_CXA_CURRENT_EXCEPTION_TYPE],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if __cxa_current_exception_type() is supported],
    [copper_cxa_current_exception_type_support],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM(
        [
          #include <typeinfo>
          #include <cxxabi.h>
        ],
        [
          try {
            throw 0;
          }

          catch (...) {
            std::type_info* info = ::abi::__cxa_current_exception_type();
          }
          return 0;
        ]
      )],
      [copper_cxa_current_exception_type_support=yes], # Test passed
      [copper_cxa_current_exception_type_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
