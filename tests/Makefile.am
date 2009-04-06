# Copyright (C) 2008 Assaf Gordon <gordon@cshl.edu>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


noinst_DATA = test.txt


check_PROGRAMS = test_container_join \
		 test_natural_sort \
		 test_input_stream_wrapper \
		 test_text_reader \
		 test_text_reader_unget \
		 test_fd_outbuf \
		 test_fd_inbuf \
		 test_in_out_buf \
		 test_tuple_parser \
		 test_pipe_fitter

TESTS = $(check_PROGRAMS)

LDADD = $(top_srcdir)/src/gtextutils/libgtextutils-$(VERSION).a
INCLUDES = -I$(top_srcdir)/src

test_container_join_SOURCES = test_container_join.cpp
test_natural_sort_SOURCES = test_natural_sort.cpp
test_input_stream_wrapper_SOURCES = test_input_stream_wrapper.cpp
test_text_reader_SOURCES = test_text_reader.cpp
test_text_reader_unget_SOURCES = test_text_reader_unget.cpp
test_fd_outbuf_SOURCES = test_fd_outbuf.cpp
test_fd_inbuf_SOURCES = test_fd_inbuf.cpp
test_in_out_buf_SOURCES = test_in_out_buf.cpp
test_pipe_fitter_SOURCES = test_pipe_fitter.c
test_tuple_parser_SOURCES = test_tuple_parser.cpp
