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
        [0.6],
        [A. Gordon gordon@cshl.edu],
        [libgtextutils])

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR([m4])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])

# dynamic library version
LIBGTU_CURRENT=0
LIBGTU_REVISION=0
LIBGTU_AGE=0

AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL

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


dnl --enable-tuple-parser-check
AC_ARG_ENABLE(tuple-parser-check,
[  --enable-tuple-parser-check	Enable Tuple Parser Check (default disabled, requires g++ > 4.3.2)],
[case "${enableval}" in
  yes) tuple_parser_check=true ;;
  no)  tuple_parser_check=false ;;
  *) AC_MSG_ERROR(bad value ${enableval} for --enable-tuple-parser-check) ;;
esac],[tuple_parser_check=false])
AM_CONDITIONAL([TUPLE_PARSER_CHECK], [test x$tuple_parser_check = xtrue])


AC_SUBST(LIBGTU_CURRENT)
AC_SUBST(LIBGTU_REVISION)
AC_SUBST(LIBGTU_AGE)


AC_CONFIG_FILES([
   Makefile
   README
   doc/Makefile
   m4/Makefile
   src/Makefile
   src/gtextutils/Makefile
   gtextutils.pc
   tests/Makefile
])

AC_OUTPUT
