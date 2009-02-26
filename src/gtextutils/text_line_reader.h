#ifndef __TEXT_FILE_READER__
#define __TEXT_FILE_READER__

#include <string>
#include <istream>
#include <sstream>

class TextLineReader
{
private:
	std::istream& input_stream ;
	size_t current_line_number;
	std::string current_line_string ;
	std::istringstream current_line_stream ;

	TextLineReader(const TextLineReader&);
    	TextLineReader& operator=(const TextLineReader&);

public:
	TextLineReader(std::istream& _input_stream) ; 

	size_t line_number() const { return current_line_number ; }

	bool next_line() ;

	const std::string& line_string() const { return current_line_string; }
	std::istringstream& line_stream() { return current_line_stream; }
};

#endif

