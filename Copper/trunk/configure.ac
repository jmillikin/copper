AC_INIT(Copper, 0.1, jmillikin@gmail.com)
AC_CONFIG_SRCDIR(src/test.cpp)

dnl Initialize automake
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS(config.h)

dnl Enable maintainer mode flag
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

AC_MSG_CHECKING([if RTTI is enabled])
if test "$enable_rtti" = "yes"; then
  AC_MSG_RESULT([yes])
  RTTI_CPPFLAGS="-frtti"
else
  AC_MSG_RESULT([no])
  RTTI_CPPFLAGS="-fno-rtti"
fi

AC_MSG_CHECKING([if exception handling is enabled])
if test "$enable_exceptions" = "yes"; then
  AC_MSG_RESULT([yes])
  EXCEPTION_CPPFLAGS="-fexceptions"
else
  AC_MSG_RESULT([no])
  EXCEPTION_CPPFLAGS="-fno-exceptions -DNO_EXCEPTIONS=1"
fi

FEATURES_CPPFLAGS="$RTTI_CPPFLAGS $EXCEPTION_CPPFLAGS"
FEATURES_LIBS=""

AC_MSG_CHECKING(if debugging is enabled[])
if test "$enable_debug" = "yes"; then
  AC_MSG_RESULT([yes])

  DEBUG_CPPFLAGS="-g3 -Wall -ansi"
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

CPPFLAGS="$CPPFLAGS $FEATURES_CPPFLAGS $OPTIMIZATION_CPPFLAGS $DEBUG_CPPFLAGS"
LIBS="$LIBS $FEATURES_LIBS $OPTIMIZATION_LIBS $DEBUG_LIBS"

AC_OUTPUT([
  Makefile
  src/Makefile
  src/protectors/Makefile
])
