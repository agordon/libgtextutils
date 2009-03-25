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

using namespace std;

int main()
{
	InputStreamWrapper input("test.txt");
	TextLineReader reader ( input.stream() );

	string line ;

	//Read first line
	ASSERT ( reader.next_line() );
	line = reader; 
	ASSERT( line == "first line" ) ;

	//Unget the current line -
	//The next call to 'reader.next_line' should return this SAME line
	//instead of actually reading the next line from the file.
	reader.unget_current_line();

	//Read the next line -
	//but because of the 'unget' it should still return the first line
	ASSERT ( reader.next_line() ) ;
	line = reader ;
	ASSERT( line == "first line" ) ;
	ASSERT ( reader.line_number() == 1 ) ; //we should still be on line 1


	//Read the next line - 
	//This should be the real second line from the file.
	ASSERT ( reader.next_line() ) ;
	line = reader;
	ASSERT ( line == "second line" );
	ASSERT ( reader.line_number() == 2 ) ;

	//Test multiple consecutive ungets
	for ( int i=0 ; i < 10; ++i ) {
		reader.unget_current_line();

		ASSERT ( reader.next_line() ) ;
		line = reader;
		ASSERT ( line == "second line" );
		ASSERT ( reader.line_number() == 2 ) ;
	}

	//Read the next line - 
	//This should be the real third line from the file.
	ASSERT ( reader.next_line() ) ;
	line = reader;
	ASSERT ( line == "third line" );
	ASSERT ( reader.line_number() == 3 ) ;

	//Unget a custom line string
	reader.unget_line("hello world");


	//Read the next line - this should return the ungot text ("hello world")
	ASSERT ( reader.next_line() ) ;
	line = reader;
	ASSERT ( line == "hello world" );

	return 0;
}
