#ifndef __BPO_INTERVAL_FILE_H__
#define __BPO_INTERVAL_FILE_H__

#include "bpo_base.h"
#include <boost/program_options.hpp>

/*
   Future improvement:
      multiplicity and orientation columns are always optionally.
      add option to make them mandatory
*/
class IntervalFileColumnOptions : public GenericBoostProgramOptions
{
	boost::program_options::options_description column_options;

	unsigned int _chrom_column ;
	unsigned int _start_column ;
	unsigned int _end_column ;
	unsigned int _orientation_column ;
	unsigned int _multiplicity_column ;

	unsigned int _max_used_column ;

public:
	IntervalFileColumnOptions() ;
	virtual ~IntervalFileColumnOptions() { }

	virtual const boost::program_options::options_description& options_description() const { return column_options; } 

	unsigned int chrom_column() const { return _chrom_column ; }
	unsigned int start_column() const { return _start_column ; }
	unsigned int end_column() const { return _end_column ; }
	unsigned int orientation_column() const { return _orientation_column ; }
	unsigned int multiplicity_column() const { return _multiplicity_column ; }

	unsigned int max_used_column() const { return _max_used_column; }

	virtual void validate() ;
};

#endif
