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
#include <gtextutils/outbuf3.hpp>
#include "tests_assertion.h"

/*
 * Test for File-Descriptor-based input and output buffers, through a system pipe.
 */

using namespace std;

int fork_pipe_command ( const char* program, const char* output_filename)
{
	int fd;
	pid_t child_pid;
	int parent_pipe[2];
	if (pipe(parent_pipe)!=0)
		err(1,"pipe (for gzip) failed");
		
	child_pid = fork();
	if (child_pid>0) {
		/* The parent process */
		fd = parent_pipe[1];
		close(parent_pipe[0]);
		return fd;
	}

	/* The child process */

	//the compressor's STDIN is the pipe from the parent
	dup2(parent_pipe[0], STDIN_FILENO);
	close(parent_pipe[1]);

	//the compressor's STDOUT is the output file
	//(which can be the parent's STDOUT, too)
	fd = open(output_filename, O_WRONLY | O_CREAT, 0666 );
	if (fd==-1)
		err(1,"Failed to open output '%s'", output_filename);
	dup2(fd, STDOUT_FILENO);
	
	//Run GZIP
	execlp(program,program,"-f",NULL);

	//Should never get here...
	err(1,"execlp(%s) failed",program);
}

void test_compress_output()
{
	int pipe_out_fd = fork_pipe_command ( "gzip", "fdout.txt.gz" ) ;
	josuttis_fdostream out(pipe_out_fd);

	out << "first line" << endl;
	out << "second line" << endl;
	out << "third line" << endl;

	close(pipe_out_fd);
}

int main()
{
	test_compress_output();
}
