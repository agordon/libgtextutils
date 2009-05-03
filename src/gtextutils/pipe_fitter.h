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

#ifndef __PIPE_FITTER_H__
#define __PIPE_FITTER_H__


#ifdef __cplusplus
extern "C"
{
#endif 

int pipe_output_command ( const char* command, const char* output_filename, pid_t* /*OUTPUT*/ child_pid );
int pipe_input_command ( const char* command, const char* input_filename, pid_t* /*OUTPUT*/ child_pid );

int pipe_close ( int fd, pid_t pid ) ;

#ifdef __cplusplus
}
#endif 

#endif
