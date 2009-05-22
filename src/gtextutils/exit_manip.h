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
#ifndef __EXIT_MANIP__
#define __EXIT_MANIP__

/* 
 Easily terminates a program while printing an error message.
   
 Tries to be an STL spirited version of errx(3)
 
 Usage:

	// from where ever in the code you wish to print message and terminate:
	// will print message to STDERR and exit with exit code 1
	cerr << "Error: something failed. " << exit_program(1);

	// if you want file+list information, use:
	cerr << "Error: something failed. " << exit_program_with_source(1);

 */

struct exit_process_struct
{
	int exitcode;
	bool show_source;
	const char* source_file;
	size_t      source_file_line_number ;
} ; 

#define exit_program_with_source(exitcode) exit_program((exitcode),__FILE__,__LINE__)
inline exit_process_struct exit_program(int exitcode, const char* filename = NULL, const size_t line = 0 )
{
	exit_process_struct eps;
	eps.exitcode = exitcode ;
	if ( filename == NULL || line == 0 )
		eps.show_source = false ;
	else {
		eps.show_source = true ;
		eps.source_file = filename ;
		eps.source_file_line_number = line ;
	}
	return eps;
}

inline std::ostream& operator<< ( std::ostream& strm, const exit_process_struct& eps )
{
	if (eps.show_source)
		strm << " [ " 
		     << eps.source_file
		     << " : " << eps.source_file_line_number << " ]";

	strm << std::endl;
	exit(eps.exitcode);
	
	return strm ;
}


#endif
