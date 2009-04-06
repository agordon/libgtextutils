#include <err.h>

#include <cmath>
#include <limits>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include <tr1/tuple>
#include <tr1/type_traits>

#include "gtextutils/tuple_parser.h"
#include "tests_assertion.h"

using namespace std;
using namespace std::tr1;


// Helper function to safely compare doubles
bool doubles_are_equal ( double a, double b )
{
	return std::abs(a-b) <= numeric_limits<double>::epsilon() ;
}

/*
	Test most basic TupleParser usage.

	Parser expects three values: int, string, double.
	
	The int is expected to be on column 4.
	The string is expected on column 3,
	The double is expected on column 1.

	After parsing, validate extracted values.
*/
void test_parser1()
{
	Tuple_Parser<int,std::string,double> parser(4,3,1);

	istringstream is ( "3.14 DUMMY HELLOWORLD 42" ) ;

	is >> parser ;

	int a = get<0>(parser);
	ASSERT ( a == 42 ) ;

	std::string b = get<1>(parser);
	ASSERT ( b == "HELLOWORLD" ) ;

	double c = get<2>(parser);
	ASSERT ( doubles_are_equal (c, 3.14) ) ;
}

/*
	Test column collusion detection.

	Parser expects three values: int, string, double.

	Two fields use the same column number.
	An exception should be thrown.
*/
void test_parser_column_collusion()
{
	try {
		Tuple_Parser<int,std::string,double> parser(1,3,1);

		//We should not get here
		ASSERT ( ! "Column collusion (1) not detected." ) ;
	} catch ( std::invalid_argument &ex ) {
		//fine, exception was thrown. we can continue
	}
}

/*
	Test max. column number overflow
*/
void test_parser_column_number_overflow()
{
	try {
		Tuple_Parser<int,std::string,double> parser(1,20000,1);

		//We should not get here
		ASSERT ( ! "Max. Column number overflow not detected." ) ;
	} catch ( std::length_error &ex ) {
		//fine, exception was thrown. we can continue
	}
}


/*	
	Test parsing error

	Parser expects three values: int, string, double.
	
	The int is expected to be on column 4.
	The string is expected on column 3,
	The double is expected on column 1.

	The 4th column doesn't contain a valid integer, and should fail.
*/
void test_parser_parsing_error()
{
	Tuple_Parser<int,std::string,double> parser(4,3,1);

	istringstream is ( "3.14 DUMMY HELLOWORLD i42" ) ;

	try {
		is >> parser ;

		//We should not get here
		ASSERT ( ! "Invalid input not detected." ) ;
	} catch ( tuple_parser_parsing_error &ex ) {
		//exception was thrown. valid reported errornous columns
		ASSERT ( ex.column() == 4 ) ;
	}
}

/*	
	Test premature-end-of-line

	Parser expects three values: int, string, double.
	
	The int is expected to be on column 4.
	The string is expected on column 3,
	The double is expected on column 1.

	The input contains only 2 columns (instead of expected 4)
*/
void test_parser_premature_eol()
{
	Tuple_Parser<int,std::string,double> parser(4,3,1);

	istringstream is ( "3.14 DUMMY" ) ;

	try {
		is >> parser ;

		//We should not get here
		ASSERT ( ! "premature-end-of-line not detected." ) ;
	} catch ( tuple_parser_premature_end_of_line &ex ) {
		//exception was thrown. valid reported errornous columns
		ASSERT ( ex.expected_columns() == 4 ) ;

		ASSERT ( ex.actual_columns() == 2 ) ;
	}
}


int main()
{
	test_parser1();

	test_parser_column_collusion();

	test_parser_column_number_overflow();

	test_parser_parsing_error();

	test_parser_premature_eol();

	return 0;
}
