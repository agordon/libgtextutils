#ifndef __BPO_IO_H__
#define __BPO_IO_H__

#include <string>
#include <boost/program_options.hpp>
#include "bpo_base.h"

/*
   Future improvements:
     option "SKIP_FIRST_LINE",
     option "DEBUG"
     make "VERBOSE" optional
*/
class InputOutputOptions : public GenericBoostProgramOptions
{
	boost::program_options::options_description io_options;

	std::string _input_filename ;
	std::string _output_filename ;
	bool _verbose ;
	bool _help ;

public:
	InputOutputOptions();
	virtual ~InputOutputOptions() { }

	virtual const boost::program_options::options_description& options_description() const { return io_options; } ;

	std::string input_file() const { return _input_filename ; }
	std::string output_file() const { return _output_filename ; } 
	bool verbose() const { return _verbose; }
	bool help() const { return _help ; }
};

#endif
