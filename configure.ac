# Copyright (C) 2008 Assaf Gordon <gordon@cshl.edu>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([Gordon-Text_utils-Library],
        [0.0.1],
        [A. Gordon gordon@cshl.edu],
        [libgtextutils])
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])

LF_CONFIGURE_CC
LF_CONFIGURE_CXX
LF_HOST_TYPE
LF_SET_WARNINGS
AC_PROG_RANLIB

AC_DEFINE([CXX_HAS_BUGGY_FOR_LOOPS], [], [Description])
AC_DEFINE([CXX_HAS_NO_BOOL], [], [Description])
AC_DEFINE([NDEBUG], [], [Description])
AC_DEFINE([YOUR_OS], [], [Description])

dnl --enable-wall
EXTRA_CHECKS="-Wall -Wextra -Wformat-nonliteral -Wformat-security -Wswitch-default -Wswitch-enum -Wunused-parameter -Wfloat-equal -Werror"
AC_ARG_ENABLE(wall,
[  --enable-wall          Enable many common GCC warnings (-Wall,-Wextra, -Werror etc., default enabled)],
[case "${enableval}" in
  yes) wall=true ;;
  no)  wall=false ;;
  *) AC_MSG_ERROR(bad value ${enableval} for --enable-wall) ;;
esac],[wall=true])
if test "$wall" = "true"
then
  CFLAGS="${CFLAGS} ${EXTRA_CHECKS}"
  CXXFLAGS="${CXXFLAGS} ${EXTRA_CHECKS}"
fi

dnl --enable-debug
AC_ARG_ENABLE(debug,
[  --enable-debug          Enable debug mode (default enabled)],
[case "${enableval}" in
  yes) debug=true ;;
  no)  debug=false ;;
  *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
esac],[debug=true])
if test "$debug" = "true"
then
  CFLAGS="${CFLAGS} -DDEBUG -g -O1"
  CXXFLAGS="${CFLAGS} -DDEBUG -g -O1"
else
  CFLAGS="${CFLAGS} -O3"
  CXXFLAGS="${CFLAGS} -O3"
fi


AC_CONFIG_FILES([
   Makefile
   README
   doc/Makefile
   m4/Makefile
   src/Makefile
   src/gtextutils/Makefile
   gtextutils-0.1.pc
])

AC_OUTPUT
