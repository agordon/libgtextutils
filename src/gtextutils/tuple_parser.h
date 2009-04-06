#ifndef __TUPLE_PARSER_H__
#define __TUPLE_PARSER_H__

#include <typeinfo>
#include <bitset>
#include <sstream>
#include <stdexcept>
#include <tr1/tuple>

//This #pramga allows variadic templates
//in a header file (imitating tr1/tuple)
#pragma GCC system_header

//#define TUPLE_PARSER_DEBUG

/*
   The maximun valid number for a column.
   The value is used in a bitset to prevent duplicated columns.
*/
#ifndef TUPLE_PARSER_MAX_COLUMN_NUMBER
#define TUPLE_PARSER_MAX_COLUMN_NUMBER (128)
#endif

/*
   Premature-end-of-line exception.

   Specialized exception class, which can report back the
   number of actual columns and expected columns.

   The what() still produces a user-friendly string,
   so if the exception is not caught, the report will still
   make some sense.
*/
class tuple_parser_premature_end_of_line : public std::runtime_error
{
private:
	std::string _what;
	size_t	_expected_columns ;
	size_t	_actual_columns;

public:
	tuple_parser_premature_end_of_line(size_t expected_columns, size_t actual_columns) :
		std::runtime_error(""),
		_expected_columns(expected_columns),
		_actual_columns(actual_columns)
	{
		std::ostringstream os;
		os << "Error: premature end-of-line, expecting at least " 
		  << expected_columns
		  << " columns, got only "
		  << actual_columns
		  << " columns" ;

		_what = os.str();
	}

	size_t expected_columns() const
	{
		return _expected_columns ;
	}

	size_t actual_columns() const
	{
		return _actual_columns;
	}

	virtual const char* what() const throw()
	{
		return _what.c_str();
	}
	
	virtual ~tuple_parser_premature_end_of_line() throw()
	{
	}
};

/*
   Parse Error exception.

   Specialized exception class, which can report back the
   number of the failed column.

   The what() still produces a user-friendly string,
   so if the exception is not caught, the report will still
   make some sense.
*/
class tuple_parser_parsing_error: public std::runtime_error
{
private:
	std::string _what;
	size_t	_column ;

public:
	tuple_parser_parsing_error(size_t column) :
		std::runtime_error(""),
		_column(column)
	{
		std::ostringstream os;
		os << "Error: invalid input in column "
		  << column ;

		_what = os.str();
	}

	size_t column() const throw()
	{
		return _column;
	}

	virtual const char* what() const throw()
	{
		return _what.c_str();
	}
	
	virtual ~tuple_parser_parsing_error() throw()
	{
	}
};

/*
 Tiny hack to convert every type into a size_t.

 Used in the constructor of _Tuple_Parser_impl,
 so that for all lists of template types,
 the constructor will accept list of size_t as arguments.

 Usage Example:
 
 	template<typename _Elements...>
	class MyClass
	{
	public:
		//This 'regular' constructor accepts variables with the same
		//Type of the template arguments.

		MyClass ( _Elements... vars ) ;



		//This constructor accepts variables of type size_t,
		//regardless of the actual type of the
		//template arguments.

		MyClass ( typename __column_index<_Elements>::type... vars ) ;
	};


 The outcome:
    A class with the following four template arguments:

         MyClass<double,string,int,char>

    will have a constructor accepting four 'size_t' arguments:

         MyClass::MyClass(size_t, size_t, size_t, size_t)


 Modeled after tr1/tuple's  __add_c_ref helper structs.
*/
template<typename _Tp>
struct __column_index
{ 
	typedef size_t type; 
};




/*
 	Tuple-Parser starts here.



*/

template<int _Idx, typename... _Elements>
     class _Tuple_Parser_impl; 

/*
 Zero-element tuple implementation. 
 This is the basis case for the inheritance recursion.

 used_column_bitset is used (during runtime) do make
 sure there are no duplicates in column numbers.

 max_column_number is used (during runtime) do deduce the
 maximum required column number.

 Since column assignment is done in runtime (not during compile-time),
 this can not be inlined or meta-programmed.

 Inherited sub-classes should call 'update_used_column()'
 in their constructor to add a new column number.
*/
template<int _Idx>
class _Tuple_Parser_impl<_Idx>  
{
private:
	size_t max_column_number ;
	std::bitset<TUPLE_PARSER_MAX_COLUMN_NUMBER> used_column_bitset;

public:
	_Tuple_Parser_impl() :
		max_column_number(0)
	{
#ifdef TUPLE_PARSER_DEBUG
		std::cerr << "At base, _Idx = " << _Idx << std::endl;
#endif
	}

	void update_max_column_number(size_t num) 
	{ 
		max_column_number = std::max(max_column_number,num); 
	}

	void update_used_column ( size_t column )
	{
		if ( column >= TUPLE_PARSER_MAX_COLUMN_NUMBER ) {
			std::ostringstream os;
			os << "Internal error: Invalid column number (" << column
			   << "). maximum allowed value is " << TUPLE_PARSER_MAX_COLUMN_NUMBER
			   << ". To change this value, re-define TUPLE_PARSER_MAX_COLUMN_NUMBER in " \
			   __FILE__ " and re-compile the program. ";
			throw std::length_error ( os.str() ) ;
		}

		if ( used_column_bitset.test ( column ) ) {
			std::ostringstream os;
			os << "Error: column number " << column
			   << " is used more than once." ;
			throw std::invalid_argument( os.str() ) ;
		}

		used_column_bitset.set(column);
		update_max_column_number(column) ;
	}
	
	size_t max_column() const { return max_column_number ; } 
#ifdef TUPLE_PARSER_DEBUG
	void print() const {}
#endif
	bool consume_input ( size_t , std::istream& ) { return false; } 
};

/*
 	The heart of the Tuple Parser recursive implementation.

	Modeled after GCC-4.3.2's <tr1/tuple>.

	At compile time, the types of the fields is recursively set
	(just like in a tuple).

	At run time, the constructor accepts the column number for each
	field, and the 'read_from_stream()' method extract the fields
	from the given input stream (according to the column numbers).

	Users should use a Tuple_Parser<> instead of _Tuple_Parser_impl<>.

	
	Usage exmaple:

	  //Define a parser that extracts three fields from an input stream:
	  //an int, a string and a double.

	  typedef Tuple_Parser<int,std::string,double> MyParser ;


	  //Create a parser object, that will expect
	  //the int field to be on the 8th column,
	  //the string field to be the 4th column,
	  //and the double field to be on the 2nd column.
	  //the other columns will be skipped and ignored.

	  MyParser p(8,4,2);

	  //Extract the columns from the input stream.
	  istringstream is ( "DUMMY1 3.14 DUMMY3 HELLO DUMMY5 DUMMY6 DUMMY7 42 DUMMY9" ) ;
  	  is >> p ;	  

	  //Get the extracted values.
	  int a = get<0>(p);
	  string s = get<1>(p);
	  double d = get<2>(p);
*/
template<int _Idx, typename _Head, typename... _Tail>
struct _Tuple_Parser_impl<_Idx, _Head, _Tail...>
: public _Tuple_Parser_impl<_Idx + 1, _Tail...>
{
	typedef _Tuple_Parser_impl<_Idx + 1, _Tail...> _Inherited;

	typedef _Head _M_head_type;
	_M_head_type _M_head ;
	size_t  _M_head_column ;

	_Inherited&       _M_tail()       { return *this; }
	const _Inherited& _M_tail() const { return *this; }

	_Tuple_Parser_impl() : _Inherited(), _M_head_column(_Idx+1),_M_head() { }

	_Tuple_Parser_impl( size_t _head_column, typename __column_index<_Tail>::type... __tail) : 
		_Inherited(__tail...), _M_head_column(_head_column) 
	{
		update_used_column ( _M_head_column ) ;
#ifdef TUPLE_PARSER_DEBUG
		std::cerr << "At Ctor, _Idx = " << _Idx 
			  << " Max-Column-Number = " << _M_tail().max_column()
			  << std::endl;
#endif
	}

#ifdef TUPLE_PARSER_DEBUG
	void print() const
	{
		std::cout << "_Idx=" << _Idx << " " 
			<< "typeid(head)=" << typeid(_M_head).name()
			<< " column = " << _M_head_column 
			<< " value = " << _M_head
			<< std::endl ;

		_M_tail().print() ;	
	}
#endif

	void read_from_stream(std::istream& strm)
	{
		size_t current_column = 0 ;
		while ( strm && !strm.eof() ) {
			current_column++;
			if ( ! consume_input (  current_column, strm ) ) {
				//consume input with dummy variable
				std::string dummy ;
				strm >> dummy ;
#ifdef TUPLE_PARSER_DEBUG
				std::cout << "skipping column " 
					  << current_column
					  << std::endl;
#endif
			}
		}
		if (current_column<_M_tail().max_column()) {
			throw tuple_parser_premature_end_of_line ( _M_tail().max_column(),
				       			current_column	) ;
		}
	}

	bool consume_input ( size_t column_number, std::istream& strm ) 
	{ 
		if ( column_number == _M_head_column ) {
#ifdef TUPLE_PARSER_DEBUG
			std::cout << "consuming column " 
				  << column_number 
				  << ", _Idx = " 
				  << _Idx << std::endl;
#endif
			strm >> _M_head;

			if (!strm)
				throw tuple_parser_parsing_error(column_number);
			
			return true;
		}
		return _M_tail().consume_input ( column_number, strm ) ;
	} 

	void update_used_column (size_t num) { _M_tail().update_used_column(num);  }
	size_t max_column() const { return _M_tail().max_column() ; } 

};



/*
	Tuple_Parser -
          The user-friendly version of _Tuple_Parser_impl.

	See comments of _Tuple_Parser_impl for details.
*/
template <typename... _Elements>
struct Tuple_Parser : public _Tuple_Parser_impl<0,_Elements...>
{
	Tuple_Parser ( typename __column_index<_Elements>::type... _UElements) : 
		_Tuple_Parser_impl<0, _Elements...>(_UElements...)
       	{ }
};


/*
	Template to get the type of the Nth element
	in a tuple parser.
	copied from 'tr1/tuple', based on tuple_element<> template.

	Usage Example:

	   typedef Tuple_Parser<int, double, std::string, float> MyParser ;

	   // 'MyVariable' will have type std::string, 
	   // which is the third (index=2) element in MyParser )
	   tuple_parser_element<2, MyParser>::type MyVariable ;

*/
/// Gives the type of the ith element of a given tuple type.
template<int __i, typename _Tp>
struct tuple_parser_element;

/**
* Recursive case for tuple_element: strip off the first element in
* the tuple and retrieve the (i-1)th element of the remaining tuple.
*/
template<int __i, typename _Head, typename... _Tail>
struct tuple_parser_element<__i, Tuple_Parser<_Head, _Tail...> >
: tuple_parser_element<__i - 1, Tuple_Parser<_Tail...> > { };

/**
* Basis case for tuple_element: The first element is the one we're seeking.
*/
template<typename _Head, typename... _Tail>
struct tuple_parser_element<0, Tuple_Parser<_Head, _Tail...> >
{
typedef _Head type;
};






/*
	Get the value of the Nth element in a Tuple_Parser.

	Copied almost verbatim from <tr1/tuple>.

	See comments of _Tuple_Parser_impl for usage example.
*/
// Adds a const reference to a non-reference type.
template<int __i, typename _Head, typename... _Tail>
inline typename std::tr1::__add_c_ref<_Head>::type
__get_helper(const _Tuple_Parser_impl<__i, _Head, _Tail...>& __t)
{
return __t._M_head;
}

template<int __i, typename... _Elements>
inline typename std::tr1::__add_c_ref<
	      typename tuple_parser_element<__i, Tuple_Parser<_Elements...> >::type
	    >::type
get(const Tuple_Parser<_Elements...>& __t)
{
return __get_helper<__i>(__t);
}


/*
	Input Stream operator for Tuple_Parser


	See comments of _Tuple_Parser_impl for usage example.
*/
template<typename... _Elements>
std::istream& operator>> ( std::istream& strm, _Tuple_Parser_impl<0, _Elements... > &parser )
{
	parser.read_from_stream(strm);
	return strm;
}


#endif

