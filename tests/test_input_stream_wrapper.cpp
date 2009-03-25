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
#include "tests_assertion.h"

/*
 * Simple unit test - InputStreamWrapper
 *
 * Read the first word out of a test file (whose content we know),
 */

using namespace std;

int main()
{
	//The object will create a 'ifstream' file with this file,
	//or exit if there was an error
	InputStreamWrapper input("test.txt");

	// InputStreamWrapper can be used as 'istream&'
	// with it's conversion operator
	istream& is ( input ) ;

	std::string s;

	is >> s ;

	ASSERT ( s == "first" ) ;

	return 0;
}
