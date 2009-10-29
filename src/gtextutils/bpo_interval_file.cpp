#include <string>
#include <sstream>
#include <algorithm>
#include <boost/program_options.hpp>
#include <vector>

#include "bpo_interval_file.h"

namespace po = boost::program_options;

IntervalFileColumnOptions::IntervalFileColumnOptions() : 
	column_options("Input file format"),
	_bed_base(true),
	_zero_base(false),
	_one_base(false),
	_zero_based_start_coord(true),
	_zero_based_end_coord(false)
{
	column_options.add_options()
		("chrom-col,c", po::value<unsigned int>(&_chrom_column)->default_value(1), "chromosome column") 
		("start-col,s", po::value<unsigned int>(&_start_column)->default_value(2), "start-coordinate column") 
		("end-col,e", po::value<unsigned int>(&_end_column)->default_value(3), "end-coordinate column") 
		("orien-col,a", po::value<unsigned int>(&_orientation_column)->default_value(0), "orientation(+/-) column (default: no orientation information)") 
		("multi-col,m", po::value<unsigned int>(&_multiplicity_column)->default_value(0), "multiplicity (=read count) column (default: no multiplicity information)") 
		("BED-BASE", po::value<bool>(&_bed_base)->zero_tokens(), "Zero-based start coordinate, one-based end coordinate - like in BED files from UCSC.\nThis is the default." )
		("ZERO-BASE", po::value<bool>(&_zero_base)->zero_tokens(),"BOTH start & end coordinates are zero based" )
		("ONE-BASE", po::value<bool>(&_one_base)->zero_tokens(),"BOTH start & end coordinates are one based")
		;
}

void IntervalFileColumnOptions::validate() 
{
	if ( _bed_base ) {
		_zero_based_start_coord = true ;
		_zero_based_end_coord = false ;
	} else if ( _zero_base ) {
		_zero_based_start_coord = true ;
		_zero_based_end_coord = true ;
	} else if ( _one_base ) {
		_zero_based_start_coord = false ;
		_zero_based_end_coord = false ;
	}

	std::stringstream os ;
	if (_chrom_column <= 0) {
		os << "Invalid chromosome-column value: '" << _chrom_column << "' - must be larger than zero" ;
		throw po::error(os.str()) ;
	}
	if (_start_column <= 0) {
		os << "Invalid start-column value: '" << _start_column << "' - must be larger than zero" ;
		throw po::error(os.str()) ;
	}
	if (_end_column <= 0) {
		os << "Invalid end-column value: '" << _end_column << "' - must be larger than zero" ;
		throw po::error(os.str()) ;
	}

	std::vector<unsigned int> columns;
	columns.push_back ( _chrom_column );

	if ( std::find(columns.begin(), columns.end(), _start_column ) != columns.end()) {
		os << "column number for 'start-column' (" << _start_column << ") is already used";
		throw po::error(os.str());
	}
	columns.push_back ( _start_column );

	if ( std::find(columns.begin(), columns.end(), _end_column ) != columns.end()) {
		os << "column number for 'end-column' (" << _end_column << ") is already used" ;
		throw po::error(os.str());
	}
	columns.push_back ( _end_column );

	if ( _multiplicity_column != 0 ) {
		if ( std::find(columns.begin(), columns.end(), _multiplicity_column ) != columns.end()) {
			os << "column number for 'multiplicity-column' (" << _multiplicity_column << ") is already used" ;
			throw po::error(os.str());
		}
		columns.push_back ( _multiplicity_column );
	}

	if ( _orientation_column != 0 ) {
		if ( std::find(columns.begin(), columns.end(), _orientation_column ) != columns.end()) {
			os << "column number for 'orientation-column' (" << _orientation_column << ") is already used" ;
			throw po::error(os.str());
		}
		columns.push_back ( _orientation_column );
	}

	_max_used_column = *(std::max_element(columns.begin(), columns.end()));
}
