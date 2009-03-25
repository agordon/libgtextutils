# Copyright (C) 2008 Assaf Gordon <gordon@cshl.edu>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.



check_PROGRAMS = test_container_join \
		 test_natural_sort

TESTS = $(check_PROGRAMS)

LDADD = $(top_srcdir)/src/gtextutils/libgtextutils-$(VERSION).a
INCLUDES = -I$(top_srcdir)/src

test_container_join_SOURCES = test_container_join.cpp
test_natural_sort_SOURCES = test_natural_sort.cpp
