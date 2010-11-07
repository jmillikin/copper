AC_INIT(Copper, 0.5, jmillikin@gmail.com)
AC_PREREQ(2.67)

AC_CONFIG_SRCDIR([src/Test.cpp])
AC_CONFIG_AUX_DIR([autoconf/aux])
AC_CONFIG_MACRO_DIR([autoconf/macro])

AM_INIT_AUTOMAKE([subdir-objects foreign])
AC_CONFIG_HEADERS([include/copper/config.h])

# Enable maintainer mode flag
AM_MAINTAINER_MODE

AC_PROG_CXX
AM_DISABLE_SHARED
AM_PROG_LIBTOOL

AC_ARG_ENABLE(debug,
  AS_HELP_STRING(--enable-debug, Enables various options which aid debugging),
  [enable_debug="$enableval"],
  [enable_debug=no]
)

AC_ARG_ENABLE(optimizations,
  AS_HELP_STRING(--disable-optimizations, Disable optimization of the library),
  [enable_optimizations="$enableval"],
  [enable_optimizations=yes]
)

AC_ARG_ENABLE(rtti,
  AS_HELP_STRING(--disable-rtti,
    Disable building the library with Run-Time Type Identification support),
  [enable_rtti="$enableval"],
  [enable_rtti=yes]
)

AC_ARG_ENABLE(exceptions,
  AS_HELP_STRING(--disable-exceptions,
    Disable building the library with exception handling support),
  [enable_exceptions="$enableval"],
  [enable_exceptions=yes]
)

AC_ARG_ENABLE(sstream,
  AS_HELP_STRING(--disable-sstream,
    Disable using sstream for formatting operations),
  [enable_sstream="$enableval"],
  [enable_sstream=yes]
)

# Required features
COPPER_CHECK_NAMESPACES
COPPER_CHECK_TEMPLATES
COPPER_CHECK_FORK

# Optional features that don't have a ./configure option
COPPER_CHECK_DISTINCT_BOOL
if test "$copper_cv_distinct_bool" = "yes"; then
  AC_DEFINE(COPPER_CONFIG_DISTINCT_BOOL, 1,
    [The compiler has a distinct bool]
  )
else
  AC_DEFINE(COPPER_CONFIG_DISTINCT_BOOL, 0,
    [The compiler does not have a distinct bool]
  )
fi

COPPER_CHECK_DISTINCT_SIZE_T
if test "$copper_cv_distinct_size_t" = "yes"; then
  AC_DEFINE(COPPER_CONFIG_DISTINCT_SIZE_T, 1,
    [The compiler has a distinct size_t]
  )
else
  AC_DEFINE(COPPER_CONFIG_DISTINCT_SIZE_T, 0,
    [The compiler does not have a distinct size_t]
  )
fi

COPPER_CHECK_STD_STRING
if test "$copper_cv_std_string_support" = "yes"; then
  AC_DEFINE(COPPER_CONFIG_STD_STRING, 1, [std::string is available.])
else
  AC_DEFINE(COPPER_CONFIG_STD_STRING, 0, [std::string is not available.])
fi

COPPER_CHECK_CONST_WRITE
if test "$copper_cv_const_write" = "yes"; then
  AC_DEFINE(COPPER_CONFIG_CONST_WRITE, 1, [write() accepts const buffer.])
else
  AC_DEFINE(COPPER_CONFIG_CONST_WRITE, 0, [write() doesn't accept const buffer.])
fi

AC_MSG_CHECKING([if sstreams should be tested])
if test "$enable_sstream" = "yes"; then
  AC_MSG_RESULT([yes])

  COPPER_CHECK_SSTREAM
  if test "$copper_cv_sstream_support" = "yes"; then
    AC_DEFINE(COPPER_CONFIG_SSTREAM, 1,
      [std::stringstream is available]
    )
  else
    AC_MSG_WARN(
      [stringstreams are not supported, only some types may be converted])

    AC_DEFINE(COPPER_CONFIG_SSTREAM, 0,
      [std::stringstream is not available]
    )
  fi
else
  AC_MSG_RESULT([no])
  AC_DEFINE(COPPER_CONFIG_SSTREAM, 0,
    [std::stringstream is not available]
  )
fi

COPPER_CHECK_STRSIGNAL
if test "$copper_cv_strsignal_support" = "yes"; then
  AC_DEFINE(COPPER_CONFIG_STRSIGNAL, 1,
    [strsignal() is available]
  )
else
  AC_DEFINE(COPPER_CONFIG_STRSIGNAL, 0,
    [strsignal() is not available]
  )
fi

COPPER_CHECK_SYS_SIGLIST
if test "$copper_cv_sys_siglist_support" = "yes"; then
  AC_DEFINE(COPPER_CONFIG_SYS_SIGLIST, 1,
    [sys_siglist is available]
  )
else
  AC_DEFINE(COPPER_CONFIG_SYS_SIGLIST, 0,
    [sys_siglist is not available]
  )
fi

# Optional features with ./configure options
AC_MSG_CHECKING([if RTTI is enabled])
if test "$enable_rtti" = "yes"; then
  AC_MSG_RESULT([yes])

  # With RTTI, exception handling can contain magic
  # See TestRun.cpp for details
  COPPER_CHECK_CXA_CURRENT_EXCEPTION_TYPE

  if test "$copper_cv_cxa_current_exception_type_support" = "yes"; then
    AC_DEFINE(COPPER_CONFIG_CXA_CURRENT_EXCEPTION_TYPE, 1,
      [__cxa_current_exception_type() is available]
    )

    # Check if type names can be de-mangled
    COPPER_CHECK_CXA_DEMANGLE

    if test "$copper_cv_cxa_demangle_support" = "yes"; then
        AC_DEFINE(COPPER_CONFIG_CXA_DEMANGLE, 1,
          [__cxa_demangle() is available]
        )
    else
        AC_DEFINE(COPPER_CONFIG_CXA_DEMANGLE, 0,
          [__cxa_demangle() is not available]
        )
    fi
  else
    AC_DEFINE(COPPER_CONFIG_CXA_CURRENT_EXCEPTION_TYPE, 0,
      [__cxa_current_exception_type() is not available]
    )
  fi

else
  AC_MSG_RESULT([no])
  # FIXME: gcc-specific
  CXXFLAGS="-fno-rtti $CXXFLAGS"
fi

AC_MSG_CHECKING(if debugging is enabled[])
if test "$enable_debug" = "yes"; then
  AC_MSG_RESULT([yes])
  CXXFLAGS="-g3 -Wall -Wextra -ansi -pedantic $CXXFLAGS"
else
  AC_MSG_RESULT([no])
fi

AC_MSG_CHECKING([if optimizations are enabled])
if test "$enable_optimizations" = "yes"; then
  AC_MSG_RESULT([yes])
  CXXFLAGS="-O2 $CXXFLAGS"
else
  AC_MSG_RESULT([no])
  CXXFLAGS="-O0 $CXXFLAGS"
fi

AC_CONFIG_FILES([
  Makefile
  copper.pc
])

AC_OUTPUT
