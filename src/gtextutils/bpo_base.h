#ifndef __BPO_BASE_H__
#define __BPO_BASE_H__

#include <vector>

class GenericBoostProgramOptions
{
public:
	virtual ~GenericBoostProgramOptions() { } ;

	virtual void validate() { };
	virtual const boost::program_options::options_description& options_description() const = 0 ;
};


class BPO_EasyParser 
{
private:
	std::vector<GenericBoostProgramOptions*> all_options ;

	boost::program_options::options_description all_options_desc;

public:
	BPO_EasyParser();

	void add ( GenericBoostProgramOptions& opts );

	void parse ( int argc,  char* argv[] );
};


#endif
