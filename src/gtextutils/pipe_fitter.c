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

#include "pipe_fitter.h"

int pipe_close ( int fd, pid_t pid ) 
{
	int i, status ;
	pid_t p;
	int exit_code;

	i = close(fd);
	if ( fd == -1 ) 
		err(1,"close(in pipe_close) failed");

	p = waitpid(pid, &status, 0);
	if (p==-1)
		err(1,"waitpid(in pipe_close) failed");

	if (!WIFEXITED(status))
		errx(1,"child process terminated abnormally (in pipe_close), status=%08x", status);

	exit_code = WEXITSTATUS(status);
	if (exit_code != 0)
		errx(1,"child process terminated with error code %d (in pipe_close)", exit_code);

	return 0;
}

static int pipe_open (
	const char* executable,
	const char* filename, 
	int pipe_input,
	pid_t* /*OUTPUT*/ child_pid )
{
	int file_fd=-1;
	pid_t pid;
	int parent_pipe[2];

	//Create the pipe descriptoers
	if (pipe(parent_pipe)!=0)
		err(1,"pipe (for '%s') failed", executable);

	if (filename != NULL) {
		file_fd = open(filename, 
			pipe_input?(O_RDONLY):(O_CREAT|O_WRONLY),
			0666 ) ;

		//create the file descriptor (input or output, based on function argument)
		if ( file_fd == -1 )
			err(1,"failed to %s file '%s'", 
				pipe_input?"open":"create",
				filename ) ;
	}
		
	pid = fork();

	if (pid == -1)
		err(1,"Fork failed for '%s'", executable);


	if (pid>0) {
		/* The parent process */
		*child_pid = pid;
		close(file_fd); //the parent process doesn't need the file handle.
		close(parent_pipe[ pipe_input?1:0 ]); 
		return (parent_pipe[ pipe_input?0:1 ]); 
	}

	/* The child process */

	if (pipe_input) {
		dup2(parent_pipe[1], STDOUT_FILENO);
		close(parent_pipe[0]); 

		if (file_fd != -1)
			dup2(file_fd, STDIN_FILENO);
	} else {
		dup2(parent_pipe[0], STDIN_FILENO);
		close(parent_pipe[1]); 

		if (file_fd!=-1)
			dup2(file_fd, STDOUT_FILENO);
	}

	execlp(executable,executable,(char*)NULL);

	//Should never get here...
	err(1,"execlp(%s) failed",executable);

	return 0; //just to please gcc
}

int pipe_output_command ( const char* command, const char* output_filename, pid_t* /*OUTPUT*/ child_pid )
{
	return pipe_open ( command, output_filename, 0, child_pid ) ;
}

int pipe_input_command ( const char* command, const char* input_filename, pid_t* /*OUTPUT*/ child_pid )
{
	return pipe_open ( command, input_filename, 1, child_pid ) ;
}
