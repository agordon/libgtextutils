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
#ifndef __PRINT_UTILS_H__
#define __PRINT_UTILS_H__

#include <string>
#include <sstream>

template<class COLLECTION>
inline
std::string
join_collection(const COLLECTION &col, const std::string& delimiter="\t")
{
	std::ostringstream os;
	bool first = true ;

	typename COLLECTION::const_iterator it = col.begin();

	while ( it != col.end() ) {
		if ( first ) 
			first = false;
		else
			os << delimiter ;
		os << *it ;
		it++ ;
	}

	return os.str();
}

#endif

