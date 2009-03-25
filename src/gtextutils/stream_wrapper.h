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
#ifndef __STREAM_WRAPPER__
#define __STREAM_WRAPPER__

#include <iostream>
#include <iosfwd>
#include <fstream>

class InputStreamWrapper
{
private:
	std::ifstream input_file ;
	bool use_stdin;

public:
	InputStreamWrapper(const std::string & filename = "") ;

	std::istream& stream() { return (use_stdin)?std::cin:input_file; } ;

	operator std::istream&() { return stream() ; }
};

class OutputStreamWrapper
{
private:
	std::ofstream output_file ;
	bool use_stdout;
	bool compressed ;

public:
	OutputStreamWrapper(const std::string & filename = "", bool _compressed = false) ;

	std::ostream& stream() { return (use_stdout)?std::cout:output_file; } ;

	operator std::ostream&() { return stream() ; }
};

#endif

