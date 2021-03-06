AC_DEFUN([COPPER_CHECK_CXA_DEMANGLE],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if __cxa_demangle() is supported],
    [copper_cv_cxa_demangle_support],
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

            int status = -1;
            char* demangled_name = ::abi::__cxa_demangle(
              info->name(), NULL, NULL, &status);
          }
          return 0;
        ]
      )],
      [copper_cv_cxa_demangle_support=yes], # Test passed
      [copper_cv_cxa_demangle_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
