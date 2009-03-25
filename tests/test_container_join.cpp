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
#include <map>
#include <string>
#include <iostream>

#include <gtextutils/container_join.h>

/*
 * Tiny test suite for container-join templates
 */

using namespace std;

int main()
{
	vector<int> v;
	for (int i=0;i<10;++i)
		v.push_back(i);

	// Print the entire container:
	cout << join(v,",") << endl;
	// Will output:  0,1,2,3,4,5,6,7,8,9

	// Print specific range, using begin/end iterators
	cout << join(v.begin(), v.end(),"-") << endl;
	// Will output: 0-1-2-3-4-5-6-7-8-9

	// An std::pair<> based container 
	// map/set/multimap/multiset/unorederd_map etc.
	//   or
	// vector< pair<A,B> > etc.
	map<int, string> m;
	m[42] = "Don't Panic";
	m[666]= "Beast" ;
	
	// Print the first values (of the pair) of the entire container:
	cout << "keys  = " << join_firsts(m) << endl;
	// Will output: 42 <tab> 666

	// Print the first values (of the pair) of a specific range:
	cout << "keys  = " << join_firsts(m.begin(), m.end(), ",") << endl;
	// Will output: 42,666

	// Print the second values (of the pair) of the entire container:
	cout << "values= " << join_seconds(m) << endl;
	// Will output: Don't Panic<tab>Beast

	// Print the second values (of the pair) of a specific range:
	cout << "values= " << join_seconds(m.begin(), m.end(), ",") << endl;
	// Will output: Don't Panic,Beast


	// Store result in a string (instead of an output stream):
	string s = join_firsts(m);
	// 's' will contain: "42\t666";

	return 0;
}
