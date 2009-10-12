#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/program_options.hpp>
#include <vector>
#include <tr1/functional>
#include "bpo_base.h"

using namespace std;
using namespace std::tr1;
using std::tr1::placeholders::_1;

namespace po = boost::program_options;

BPO_EasyParser::BPO_EasyParser()
{
}

void BPO_EasyParser::add ( GenericBoostProgramOptions& opts )
{
	all_options.push_back ( &opts ) ;
	all_options_desc.add ( opts.options_description() ) ;
}

void BPO_EasyParser::parse ( int argc, char* argv[] )
{
	po::variables_map vm;
	try {
		po::store(po::parse_command_line(argc, argv, all_options_desc), vm);
		po::notify(vm);    

		for_each(all_options.begin(), all_options.end(),
				bind( &GenericBoostProgramOptions::validate, _1 ) ) ;

	} catch ( boost::program_options::error &e ) {
		cerr << "command line error: " << e.what() << endl ;
		exit(1);
	}

	if (vm.count("help")) {
		cout << all_options_desc << endl;
		exit(1);
	}
}

