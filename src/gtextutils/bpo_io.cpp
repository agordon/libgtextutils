#include <string>
#include <sstream>
#include <algorithm>
#include <boost/program_options.hpp>
#include <vector>

#include "bpo_io.h"

namespace po = boost::program_options;

InputOutputOptions::InputOutputOptions() :
	io_options("Input/Output options"),
	_verbose(false),
	_help(false)
{
	io_options.add_options()
		("input-file,i", po::value<std::string>(&_input_filename), "Input file (default: stdin)") 
		("output-file,o", po::value<std::string>(&_output_filename), "Output file (default: stdout)" ) 
		("verbose,v", po::value<bool>(&_verbose)->zero_tokens(), "verbose (if output goes to STDOUT, verbose summary will be printed to STDERR. If output goes to afile, verbose summary will be printed to STDOUT).")
		("help,h", po::value<bool>(&_help)->zero_tokens(), "help and command line options") ;
}


