# Copyright (C) 2008 Assaf Gordon <gordon@cshl.edu>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


EXTRA_DIST = test.txt
noinst_DATA = test.txt

if TUPLE_PARSER_CHECK
TUPLE_PROG = test_tuple_parser \
	     test_tuple_parser_file
else
TUPLE_PROG = 
endif

check_PROGRAMS = test_container_join \
		 test_natural_sort \
		 test_input_stream_wrapper \
		 test_text_reader \
		 test_text_reader_unget \
		 test_fd_outbuf \
		 test_fd_inbuf \
		 test_in_out_buf \
		 test_pipe_fitter \
		 test_string_tokenize \
		 $(TUPLE_PROG)

TESTS = $(check_PROGRAMS)

LDADD = $(top_srcdir)/src/gtextutils/libgtextutils.la
INCLUDES = -I$(top_srcdir)/src

test_container_join_SOURCES = test_container_join.cpp tests_assertion.h
test_natural_sort_SOURCES = test_natural_sort.cpp tests_assertion.h
test_input_stream_wrapper_SOURCES = test_input_stream_wrapper.cpp tests_assertion.h
test_text_reader_SOURCES = test_text_reader.cpp tests_assertion.h
test_text_reader_unget_SOURCES = test_text_reader_unget.cpp tests_assertion.h
test_fd_outbuf_SOURCES = test_fd_outbuf.cpp tests_assertion.h
test_fd_inbuf_SOURCES = test_fd_inbuf.cpp tests_assertion.h
test_in_out_buf_SOURCES = test_in_out_buf.cpp tests_assertion.h
test_pipe_fitter_SOURCES = test_pipe_fitter.c tests_assertion.h
test_tuple_parser_SOURCES = test_tuple_parser.cpp tests_assertion.h
test_tuple_parser_file_SOURCES = test_tuple_parser_file.cpp tests_assertion.h
test_string_tokenize_SOURCES = test_string_tokenize.cpp tests_assertion.h
