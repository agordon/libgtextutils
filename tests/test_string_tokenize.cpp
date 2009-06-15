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
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <err.h>
#include <iterator>

#include "tests_assertion.h"
#include <gtextutils/string_tokenize.h>

/*
 * Tiny test suite for string tokenize
 */

using namespace std;

//Test tokenize by single delimiter character
void test_token1()
{
	string test1 = "Hello|Token|World";
	vector<string> v;

	String_Tokenize ( test1, back_inserter(v), "|" ) ;

	ASSERT ( v[0] == "Hello" ) ;
	ASSERT ( v[1] == "Token" ) ;
	ASSERT ( v[2] == "World" ) ;

}


//Test tokenize by multiple delimiters
void test_token2()
{
	string test1 = "Hello Token|World";
	vector<string> v;

	String_Tokenize ( test1, back_inserter(v), "| " ) ;

	ASSERT ( v[0] == "Hello" ) ;
	ASSERT ( v[1] == "Token" ) ;
	ASSERT ( v[2] == "World" ) ;

}

int main()
{
	test_token1();
	test_token2();


	return 0;
}
