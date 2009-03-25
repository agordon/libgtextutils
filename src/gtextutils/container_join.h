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
#ifndef __LIBGTEXTUTILS_CONTAINER_JOIN_H__
#define __LIBGTEXTUTILS_CONTAINER_JOIN_H__

/* 
 * Easily joins a container and outputs it to a stream.
 * 
 * Tries to emulate Perl's join in an STL way.

Usage:

 send container's elements into an output-stream:

	STD::OSTREAM << join ( CONTAINER, [DELIMITER] ) ;
	STD::OSTREAM << join ( BEGIN-ITERATOR, END-ITERATOR, [DELIMITER] ) ;

 send container's elements into a string:

	STD::STRING = join ( CONTAINER, [DELIMITER] ) ;
	STD::STRING = join ( BEGIN-ITERATOR, END-ITERATOR, [DELIMITER] ) ;

	[DELIMITER] = optional std::string, will be used as delimiter between two elements.
	              defaults to a single tab.
		      can contain multiple characters.

Usage example:

	// A simple container (could also be a list/deque/stack/whatever):
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


*/


#include <ostream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>

template<typename ITERATOR, typename OP> 
struct joiner
{
	joiner ( ITERATOR _begin, ITERATOR _end, const std::string& _delimiter="\t" ) : 
		begin(_begin), 
		end(_end),
		delimiter(_delimiter)
	{} 

	ITERATOR begin, end;
	std::string delimiter;
	OP op;

	operator std::string() const
	{
		std::ostringstream os;
		os << *this;
		return os.str();
	}
};

template<typename ITERATOR, typename OP>
inline std::ostream& operator<< ( std::ostream& strm, const joiner<ITERATOR, OP>& j )
{
	ITERATOR it = j.begin;
	if (it != j.end) {
		//first element - doesn't need a delimiter
		strm << j.op(*it);
		it++;
	}
	for (; it != j.end ; ++it) {
		//print a delimiter before all other elements
		strm << j.delimiter ;
		strm << j.op(*it);
	}
	return strm;
}

template <typename T>
struct joiner_noop
{
const T& operator() (const T& t) const { return t; }
};

template <typename FIRST, typename SECOND>
struct joiner_select1st
{
const FIRST& operator() ( const std::pair<FIRST,SECOND>& pair ) const { return pair.first ; }
};

template <typename FIRST, typename SECOND>
struct joiner_select2nd
{
const SECOND& operator() ( const std::pair<FIRST,SECOND>& pair ) const { return pair.second; }
};

template<typename ITERATOR >
inline 
joiner< ITERATOR, joiner_noop<typename ITERATOR::value_type> > 
join(ITERATOR begin, ITERATOR end, const std::string& delimiter="\t")
{
	return joiner< ITERATOR, joiner_noop<typename ITERATOR::value_type> > (begin, end, delimiter);
}

template<typename ITERATOR >
inline 
joiner< ITERATOR, joiner_select1st<typename ITERATOR::value_type::first_type, typename ITERATOR::value_type::second_type> > 
join_firsts(ITERATOR begin, ITERATOR end, const std::string& delimiter="\t")
{
	return joiner< ITERATOR, joiner_select1st<typename ITERATOR::value_type::first_type, typename ITERATOR::value_type::second_type> > (begin, end, delimiter);
}

template<typename ITERATOR >
inline 
joiner< ITERATOR, joiner_select2nd<typename ITERATOR::value_type::first_type, typename ITERATOR::value_type::second_type> > 
join_seconds(ITERATOR begin, ITERATOR end, const std::string& delimiter="\t")
{
	return joiner< ITERATOR, joiner_select2nd<typename ITERATOR::value_type::first_type, typename ITERATOR::value_type::second_type> > (begin, end, delimiter);
}

template<typename CONTAINER>
inline 
joiner< typename CONTAINER::const_iterator, joiner_noop<typename CONTAINER::value_type>	> 
join(const CONTAINER& a, const std::string& delimiter="\t")
{
	return join(a.begin(), a.end(), delimiter);
}


template<typename CONTAINER>
inline 
joiner< typename CONTAINER::const_iterator, joiner_select1st<typename CONTAINER::value_type::first_type, typename CONTAINER::value_type::second_type> > 
join_firsts(const CONTAINER& a, const std::string& delimiter="\t")
{
	return join_firsts(a.begin(), a.end(), delimiter);
}

template<typename CONTAINER>
inline 
joiner< typename CONTAINER::const_iterator, joiner_select2nd<typename CONTAINER::value_type::first_type, typename CONTAINER::value_type::second_type> > 
join_seconds(const CONTAINER& a, const std::string& delimiter="\t")
{
	return join_seconds(a.begin(), a.end(), delimiter);
}

#endif
