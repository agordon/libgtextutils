/*
   Gordon's Text-Utilities Library
   Copyright (C) 2009 Assaf Gordon (gordon@cshl.edu)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <gtextutils/inbuf1.hpp>
#include "tests_assertion.h"

/*
 * Test for File-Descriptor-based input buffer.
 */

using namespace std;

const char* filename = "test.txt" ;

int main()
{
	//Open a file using C API
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror ("Failed to open test file 'test.txt'");

	//Connect the file-descriptor to an input stream
	josuttis_fdistream in1(fd);
	string s;

	//Read and verify the file content
	in1 >> s ;
	ASSERT ( s == "first" ) ;
	in1 >> s ;
	ASSERT ( s == "line" ) ;
	in1 >> s ;
	ASSERT ( s == "second" ) ;
	in1 >> s ;
	ASSERT ( s == "line" ) ;
	in1 >> s ;
	ASSERT ( s == "third" ) ;
	in1 >> s ;
	ASSERT ( s == "line" ) ;
	in1 >> s ;
	ASSERT ( s == "fourth" ) ;
	in1 >> s ;
	ASSERT ( s == "line" ) ;

	close(fd);
}
