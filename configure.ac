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

AC_CONFIG_FILES([
   Makefile
   README
   doc/Makefile
   m4/Makefile
   src/Makefile
])

AC_OUTPUT
