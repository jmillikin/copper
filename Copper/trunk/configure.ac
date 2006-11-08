AC_INIT(Copper, 0.1, jmillikin@gmail.com)
AC_CONFIG_SRCDIR(src/test.cpp)

# Store autoconf cruft in a separate directory
AC_CONFIG_AUX_DIR(autoconf)
AC_CONFIG_MACRO_DIR(autoconf)

# Initialize automake
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS(config.h)

# Enable maintainer mode flag
AM_MAINTAINER_MODE

AC_PROG_CXX
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

# Required features
COPPER_CHECK_NAMESPACES
COPPER_CHECK_STATIC_CAST
COPPER_CHECK_TEMPLATES

# Optional features that don't have a ./configure option
COPPER_CHECK_BOOLEAN
if test "$coppper_boolean_support" = "no"; then
  AC_MSG_WARN([Booleans are not distinct types])

  AC_DEFINE(HAVE_BOOLEAN, 0,
    [The compiler does not have a distinct boolean type]
  )
else
  AC_DEFINE(HAVE_BOOLEAN, 1,
    [The compiler has a distinct boolean type]
  )
fi

COPPER_CHECK_SSTREAM
if test "$coppper_sstream_support" = "no"; then
  AC_MSG_WARN(
    [stringstreams are not supported, only some types may be checked])

  AC_DEFINE(HAVE_SSTREAM, 0,
    [The compiler does not have the sstream header]
  )
else
  AC_DEFINE(HAVE_SSTREAM, 1,
    [The compiler has the sstream header]
  )
fi

# Optional features with ./configure options
AC_MSG_CHECKING([if RTTI is enabled])
if test "$enable_rtti" = "yes"; then
  AC_MSG_RESULT([yes])
  RTTI_CPPFLAGS=""
else
  AC_MSG_RESULT([no])
  # FIXME: gcc-specific
  RTTI_CPPFLAGS="-fno-rtti"
fi

AC_MSG_CHECKING([if exception handling is enabled])
if test "$enable_exceptions" = "yes"; then
  AC_MSG_RESULT([yes])

  # Check whether exceptions are actually supported
  COPPER_CHECK_EXCEPTIONS

  if test "$coppper_exception_support" = "yes"; then
    AC_DEFINE(HAVE_EXCEPTIONS, 1,
      [The compiler supports exceptions]
    )
  else
    AC_DEFINE(HAVE_EXCEPTIONS, 0,
      [The compiler does not support exceptions]
    )
  fi

  EXCEPTION_CPPFLAGS=""
else
  AC_MSG_RESULT([no])
  AC_DEFINE(HAVE_EXCEPTIONS, 0,
      [The compiler does not support exceptions]
    )

  # FIXME: gcc-specific
  EXCEPTION_CPPFLAGS="-fno-exceptions"
fi

FEATURES_CPPFLAGS="$RTTI_CPPFLAGS $EXCEPTION_CPPFLAGS"

AC_MSG_CHECKING(if debugging is enabled[])
if test "$enable_debug" = "yes"; then
  AC_MSG_RESULT([yes])

  DEBUG_CPPFLAGS="-g3 -Wall -ansi -pedantic"
else
  AC_MSG_RESULT([no])
fi

AC_MSG_CHECKING([if optimizations are enabled])
if test "$enable_optimizations" = "yes"; then
  AC_MSG_RESULT([yes])

  OPTIMIZATION_CPPFLAGS="-O2"
else
  AC_MSG_RESULT([no])

  OPTIMIZATION_CPPFLAGS="-O0"
fi

# For the Intel C/C++ Compiler
COMPAT_LIBS="-lstdc++"

CPPFLAGS="$FEATURES_CPPFLAGS $OPTIMIZATION_CPPFLAGS $DEBUG_CPPFLAGS"
LIBS="$OPTIMIZATION_LIBS $DEBUG_LIBS $COMPAT_LIBS"

AC_OUTPUT([
  Makefile
  src/Makefile
  src/protectors/Makefile
  src/util/Makefile
  include/Makefile
  include/copper/Makefile
  include/copper/protectors/Makefile
  include/copper/util/Makefile
])
