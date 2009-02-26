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
	

