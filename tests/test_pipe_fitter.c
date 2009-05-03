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
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include <gtextutils/pipe_fitter.h>
#include "tests_assertion.h"

const char* text = "Hello World\n";

int main()
{
	int fd;
	int pid;
	char temp[1000];
	char str[1000];
	int n ;

	//Pipe output through a GZIP program
	fd = pipe_output_command ( "gzip", "pipe_out.txt.gz", &pid ) ;
	write ( fd, text, strlen(text))  ;
	pipe_close(fd, pid);


	//Read input through a GUNZIP program
	fd = pipe_input_command ( "gunzip", "pipe_out.txt.gz", &pid );

	//Read entire input from the pipe.
	//Note:
	//   'read' doesn't have to return the entire input in one read - so
	//   we loop until the end of the file and concatnate the input.
	strcat(str,"");
	while (1) {
		n = read ( fd, temp, sizeof(temp)-1) ;
		if (n==-1)
			err(1,"Read from GZIP input pipe failed");

		if (n==0)
			break; //End-Of-File

		//Ensure proper NULL termination
		temp[n] = 0 ;

		strncpy ( str, temp, sizeof(str)-1);
	}
	pipe_close(fd,pid);


	//Validate the input
	ASSERT ( strcmp(str, text)==0 ) ;

	return 0 ;
}
