#ifndef __STREAM_WRAPPER__
#define __STREAM_WRAPPER__

#include <fstream>

class InputStreamWrapper
{
private:
	std::ifstream input_file ;
	bool use_stdin;

public:
	InputStreamWrapper(const std::string & filename = "") ;

	std::istream& stream() { return (use_stdin)?std::cin:input_file; } ;

	operator std::istream&() { return stream() ; }
};

class OutputStreamWrapper
{
private:
	std::ofstream output_file ;
	bool use_stdout;
	bool compressed ;

public:
	OutputStreamWrapper(const std::string & filename = "", bool _compressed = false) ;

	std::ostream& stream() { return (use_stdout)?std::cout:output_file; } ;

	operator std::ostream&() { return stream() ; }
};

#endif

