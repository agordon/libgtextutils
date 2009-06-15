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
#ifndef __STRING_TOKENIZE_H__
#define __STRING_TOKENIZE_H__

#include <string>
#include <iterator>

/*
   Splits a string into tokens, based on delimiter

   Heavily based on code from:
   
   	C++ Programming HOW-TO
	Al Dev (Alavoor Vasudevan) alavoor[AT]yahoo.com
	http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html

	(Distributed under GPL)


   Usage Example:

      string input = "Hello|Token|World";
      vector<string> tokens;
      String_Tokenize ( input, back_inserter<string>(tokens), "|" ); 

*/
template <typename OutputIterator>
void String_Tokenize(const std::string& str,
		OutputIterator 	output_iter,
		const std::string& delimiters = " ")
{
	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		*output_iter = str.substr(lastPos, pos - lastPos);
		++output_iter;

		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}


#endif

