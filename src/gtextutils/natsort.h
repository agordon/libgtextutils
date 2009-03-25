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
#ifndef __NATURAL_SORT_STL_H__
#define __NATURAL_SORT_STL_H__

/*
 * natsort.h - 
 * STL-compatible interface to Martin Pool's Natural-Order sorting routines.
 *
 * see http://sourcefrog.net/projects/natsort/ for more details
 *
 * Note 1:
 * There's a boost equivalent version of 'composable natural sort'
 * at http://www.boostcookbook.com/Recipe:/1235053
 * But it requires the boost library (including the regex engine),
 * and I prefer not to use it for now.
 *
 * Note 2:
 * As of FSF GNU Coreutils version 7.1, the 'sort' progarm as a similar sorting order
 * called 'version' (with the -V command argument).
 * Coreutils's implementation is found in <coreutils-7.1>/src/filevercmp.{ch}.
 * The results are similar to Matrin Poo's NatSort, but not identical
 * if the sorted strings are more complex than <prefixNUM>.
 */

/*
Usage:
	// sort an array in natural order
	vector<string> v;
	v.push_back("chr20");
	v.push_back("chr10");
	v.push_back("chr5");
	v.push_back("chr1");
	v.push_back("chr2");

	// "regular" sort
	sort(v.begin(), v.end() );
	// order will be:  
	//	chr1
	//	chr10
	//	chr2
	//	chr20
	//	chr5
	
	// "natural order" sort
	sort(v.begin(), v.end(), natural_sort_predicate() );
	// order will be: 
	// 	chr1
	// 	chr2
	// 	chr5
	// 	chr10
	// 	chr20
*/


extern "C" {
/*
  strnatcmp.{h,c} -- Perform 'natural order' comparisons of strings in C.
  Copyright (C) 2000, 2004 by Martin Pool <mbp sourcefrog net>
*/
#include "strnatcmp.h"
}

#include <string>

struct natural_sort_predicate : public std::binary_function<std::string, std::string, bool>
{
	bool operator() ( const std::string& s1, const std::string& s2 )
	{
		return strnatcmp(s1.c_str(), s2.c_str()) < 0 ;
	}
};

struct natural_sort_ignore_case_predicate : public std::binary_function<std::string, std::string, bool>
{
	bool operator() ( const std::string& s1, const std::string& s2 )
	{
		return strnatcasecmp(s1.c_str(), s2.c_str()) < 0 ;
	}
};

/*
inline bool natural_sort_predicate(const std::string& s1, const std::string& s2)
{
	return strnatcmp(s1.c_str(), s2.c_str()) < 0 ;
}

inline bool natural_sort_ignore_case_predicate(const std::string& s1, const std::string& s2)
{
	return strnatcasecmp(s1.c_str(), s2.c_str()) < 0 ;
}*/


#endif

