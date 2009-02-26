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

