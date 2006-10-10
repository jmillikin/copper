AC_INIT(UnitTests, 0.1, jmillikin@gmail.com)
AC_CONFIG_SRCDIR(src/test.cpp)

dnl Initialize automake
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS(config.h)

dnl Enable maintainer mode flag
AM_MAINTAINER_MODE

AC_PROG_CXX
AM_PROG_LIBTOOL

dnl Required only when building the Qt output handler
QT_REQUIRED=4.1.0

AC_ARG_ENABLE(qt,
  AS_HELP_STRING(--enable-qt, Enable building the Qt output handler),
  [enable_qt_output="$enableval"],
  [enable_qt_output=no]
)

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

AC_MSG_CHECKING([whether to build the Qt output handler])
if test "$enable_qt" = "yes"; then
  AC_MSG_RESULT([yes])

  PKG_CHECK_MODULES(Qt, QtGui >= $QT_REQUIRED QtCore >= $QT_REQUIRED)

  dnl Check that moc is in path
  AC_PATH_PROG(MOC, moc-qt4)
  if test -z "$MOC"; then
    AC_PATH_PROG(MOC, moc)
    if test -z "$MOC"; then
      AC_MSG_ERROR([*** moc must be in path])
    fi
  fi
else
  AC_MSG_RESULT([no])
fi
AM_CONDITIONAL(ENABLE_QT_OUTPUT, test "$enable_qt" = "yes")

FEATURES_CPPFLAGS="$Qt_CFLAGS"
FEATURES_LIBS="$Qt_LIBS"

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
  src/output_handlers/Makefile
  src/protectors/Makefile
])
