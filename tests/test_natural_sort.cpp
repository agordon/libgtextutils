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

#include <gtextutils/container_join.h>

#include <gtextutils/natsort.h>

/*
 * Tiny test suite for natural sort
 */

using namespace std;

int main()
{
	vector<string> v;

	v.push_back("chr4");
	v.push_back("chr2");
	v.push_back("chr10");
	v.push_back("chr11");
	v.push_back("chr1");
	v.push_back("chrX");
	v.push_back("chr20");
	v.push_back("ChR13");

	sort(v.begin(), v.end());

	cout << "Regular sort:                    " << join(v) << endl;

	sort(v.begin(), v.end(), natural_sort_predicate() );
	cout << "Natural sort (case sensitive):   " << join(v) << endl;

	sort(v.begin(), v.end(), natural_sort_ignore_case_predicate() );
	cout << "Natural sort (case-insensitive): " << join(v) << endl;




	return 0;
}
