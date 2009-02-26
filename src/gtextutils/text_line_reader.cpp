#include <istream>
#include <sstream>

#include "text_line_reader.h"

using namespace std;


TextLineReader::TextLineReader(istream& _input_stream) :
	input_stream(_input_stream), current_line_number(0)
{
}

bool TextLineReader::next_line() 
{
	current_line_number++;
	getline(input_stream, current_line_string ) ;

	current_line_stream.str( current_line_string ) ;
	current_line_stream.seekg(0, ios_base::beg );
	current_line_stream.clear();
	
	if (input_stream.eof())
		return false;

	return input_stream ;
}

