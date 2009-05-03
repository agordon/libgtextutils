#include <err.h>
#include <getopt.h>

#include <cstdlib>
#include <cmath>
#include <limits>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include <tr1/tuple>
#include <tr1/type_traits>

#include <gtextutils/stream_wrapper.h>
#include <gtextutils/text_line_reader.h>
#include <gtextutils/tuple_parser.h>
#include "tests_assertion.h"

using namespace std;
using namespace std::tr1;

std::string input_filename = "test.bed";
size_t	chrom_column = 1 ;
size_t	start_column = 2 ;
size_t	end_column = 3 ;
bool verbose = false ;

void read_and_parse_file()
{
	InputStreamWrapper input(input_filename);

	TextLineReader reader ( input.stream() );

	Tuple_Parser<std::string,size_t,size_t> parser( chrom_column,
		      					start_column,
							end_column);
	while ( reader.next_line() ) {
		reader.line_stream() >> parser ;
	}
}

void usage()
{
	exit(0);
}

void parse_command_line(int argc, char* argv[])
{
	int opt;

	while ((opt=getopt(argc, argv,"hi:c:s:ev")) != -1) {
		switch(opt)
		{
		case 'h':
			usage();

		case 'i':
			input_filename = optarg ;
			break;

		case 'c':
			if ( sscanf(optarg, "%zu", &chrom_column ) != 1  )
				errx(1,"Error: invalid chromosome column (%s)", optarg ) ;
			if ( chrom_column <= 0 ) 
				errx(1,"Error: invalid chromosome column (%s)", optarg ) ;
			break;

		case 's':
			if ( sscanf(optarg, "%zu", &start_column ) != 1 )
				errx(1,"Error: invalid start column (%s)", optarg ) ;
			if ( start_column <= 0 )
				errx(1,"Error: invalid start column (%s)", optarg ) ;
			break;

		case 'e':
			if ( sscanf(optarg, "%zu", &end_column ) != 1 )
				errx(1,"Error: invalid end column (%s)", optarg ) ;
			if ( end_column <= 0 )
				errx(1,"Error: invalid end column (%s)", optarg ) ;
			break;

		case 'v':
			verbose=true;
			break ;

		default:
			exit(1);
		}
	}
}

int main(int argc, char* argv[])
{
	parse_command_line(argc, argv) ;

	read_and_parse_file();

	return 0;
}
