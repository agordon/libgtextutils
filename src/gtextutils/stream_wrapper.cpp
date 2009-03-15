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
#include <string>
#include <fstream>
#include <iostream>
#include <ios>

#include <err.h>

#include "stream_wrapper.h"


InputStreamWrapper::InputStreamWrapper(const std::string & filename) :
	use_stdin(filename.length()==0)
{
	if (!use_stdin) {
		input_file.open(filename.c_str()) ;
		if (!input_file)
			err(1,"Failed to open input file (%s)", 
				filename.c_str()) ;
	}
};

OutputStreamWrapper::OutputStreamWrapper(const std::string & filename, bool _compressed ) :
	use_stdout(filename.length()==0), compressed(_compressed)
{
	if (compressed) {
		/* compressed output stream:
		   fork and run GZIP */

	} 
	else {
		/* normal (not-compressed) output file:
		   just open the file (if needed) */
		if (!use_stdout) {
			output_file.open(filename.c_str()) ;
			if (!output_file)
				err(1,"Failed to create output file (%s)", 
						filename.c_str()) ;
		}
	}
};
	

