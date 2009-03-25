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
#include <err.h>
#include <iostream>
#include <string>

#include <gtextutils/stream_wrapper.h>
#include <gtextutils/text_line_reader.h>

#include "tests_assertion.h"

/*
 * Testing the TextLineReader class
 *
 * Read four lines from a known file,
 * using different methods
 */

using namespace std;

int main()
{
	InputStreamWrapper input("test.txt");
	TextLineReader reader ( input.stream() );

	string line ;

	ASSERT ( reader.next_line() );
	line = reader.line_string() ; //first line - with explicit method to get the string
	ASSERT( line == "first line" ) ;

	ASSERT ( reader.next_line() );
	line = reader ; //second line - with implicit conversion to std::string
	ASSERT( line == "second line" ) ;

	ASSERT ( reader.next_line() );
	istream &is1 ( reader.line_stream() ); //third line - with explicit method to get the istream
	is1 >> line ; // read each word from the line
	ASSERT( line == "third" ) ;
	is1 >> line ;
	ASSERT ( line == "line" ) ;
	is1 >> line ; // read past the end of the line - this should fail (and not read the next word from the next line, as it would have happened with a normal istream;
	ASSERT ( ! is1 ) ;

	ASSERT ( reader.next_line() );
	istream &is2 ( reader ) ; // fourth line - with implicit conversion to std::istream
	is2 >> line ;
	ASSERT( line == "fourth" ) ;
	is2 >> line ;
	ASSERT( line == "line" ) ;
	is1 >> line ; // read past the end of the line - this should fail (and not read the next word from the next line
	ASSERT ( !is2 ) ;


	//read past the end of the file - make sure it fails.
	ASSERT ( !reader.next_line() ) ;
	return 0;
}
