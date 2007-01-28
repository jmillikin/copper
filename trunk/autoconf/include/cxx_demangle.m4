AC_DEFUN([COPPER_CHECK_CXA_DEMANGLE],[
  AC_LANG_PUSH([C++])

  AC_CACHE_CHECK(
    [if __cxa_demangle() is supported],
    [coppper_cxa_demangle_support],
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
            std::type_info* info = __cxxabiv1::__cxa_current_exception_type();

            int status = -1;
            char* demangled_name = __cxxabiv1::__cxa_demangle(
              info->name(), NULL, NULL, &status);
          }
          return 0;
        ]
      )],
      [coppper_cxa_demangle_support=yes], # Test passed
      [coppper_cxa_demangle_support=no]   # Test failed
    )]
  )

  AC_LANG_POP([C++])
])
