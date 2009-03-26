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

#include <gtextutils/outbuf3.hpp>
#include "tests_assertion.h"

/*
 * Test for File-Descriptor-based output buffer.
 */

using namespace std;

const char* filename = "fdout.tmp" ;

void create_file()
{
	//Create a File (using C API),
	//then connect an output stream to it
	int fd = open("fdout.tmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR|S_IWUSR ) ;
	if ( fd == -1 )
		perror("Failed to create file 'fdout.tmp'");

	josuttis_fdostream out2(fd);
	out2 << "first line" << endl ;
	out2 << "second line" << endl ;
	out2 << "third line" << endl;

	close(fd);
}

void verify_file()
{
	//To verify - use only STL classes,
	//no home made libgtextutils classes.
	ifstream ifs(filename);
	string s;
	ifs >> s ;
	ASSERT ( s == "first" ) ;
	ifs >> s ;
	ASSERT ( s == "line" ) ;
	ifs >> s ;
	ASSERT ( s == "second" ) ;
	ifs >> s ;
	ASSERT ( s == "line" ) ;
	ifs >> s ;
	ASSERT ( s == "third" ) ;
	ifs >> s ;
	ASSERT ( s == "line" ) ;
}

int main()
{
	//Use file-descriptor 1 = STDOUT
	josuttis_fdostream out1(1);
	out1 << "Hello World from File-Descriptor Output Stream (josuttifs_fdostream)!" << endl;

	create_file();

	verify_file();

	unlink(filename);
}
