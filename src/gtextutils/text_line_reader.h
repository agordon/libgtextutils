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
	bool unget_line_active ;

	TextLineReader(const TextLineReader&);
    	TextLineReader& operator=(const TextLineReader&);

public:
	TextLineReader(std::istream& _input_stream) ; 

	size_t line_number() const { return current_line_number ; }

	bool next_line() ;

	void unget_line ( const std::string& line ) 
	{ 
		unget_line_active = true ;
		current_line_string = line ;
	}
	void unget_current_line () { unget_line_active = true; } 

	//explicit conversions
	const std::string& line_string() const { return current_line_string; }
	std::istringstream& line_stream() { return current_line_stream; }

	//implicit conversions
	operator const std::string& () const { return line_string() ; }
	operator std::string() const { return line_string(); }
	operator std::istream& () { return line_stream(); }

};

#endif

