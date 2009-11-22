# Copyright (C) 2008 Assaf Gordon <gordon@cshl.edu>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


lib_LTLIBRARIES = libgtextutils.la

libgtextutils_la_LDFLAGS = -version-info @LIBGTU_CURRENT@:@LIBGTU_REVISION@:@LIBGTU_AGE@ -release @VERSION@

libgtextutils_la_SOURCES = stream_wrapper.cpp stream_wrapper.h \
		          text_line_reader.cpp text_line_reader.h \
			  container_join.h \
			  natsort.h \
			  strnatcmp.c strnatcmp.h \
			  outbuf3.hpp \
			  tuple_parser.h \
			  exit_manip.h \
			  inbuf1.hpp \
			  pipe_fitter.c pipe_fitter.h

libgtextutils_la_includedir = $(includedir)/gtextutils/gtextutils

libgtextutils_la_include_HEADERS = container_join.h \
		  text_line_reader.h \
		  stream_wrapper.h \
		  natsort.h \
		  strnatcmp.h \
		  outbuf3.hpp \
		  inbuf1.hpp \
		  tuple_parser.h \
		  exit_manip.h \
		  string_tokenize.h \
		  pipe_fitter.h
