/*
   Gordon's Text-Utilities Library
   Copyright (C) 2009-2013 Assaf Gordon (assafgordon@gmail.com)

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

#ifndef __JOSUTTIS_FD_INBUF_H__
#define __JOSUTTIS_FD_INBUF_H__

/* The following code example is taken from the book
 * "The C++ Standard Library - A Tutorial and Reference"
 * by Nicolai M. Josuttis, Addison-Wesley, 1999
 *
 * (C) Copyright Nicolai M. Josuttis 1999.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 *
 * Added by A. Gordon:
 *  The file is available as "io/inbuf1.hpp" in the examples tarball at
 *    http://www.josuttis.com/libbook/
 *
 *  And in the book at Chapter 13, Page 678.
 *
 * Modifications:
 *    1. Larger buffer, with vector<char> 
 *    2. Accepts input file descriptor in c'tor
 */

#include <cstdio>
#include <cstring>
#include <streambuf>
#include <vector>

// for read():
#ifdef _MSC_VER
# include <io.h>
#else
# include <unistd.h>
#endif

class josuttis_fd_inbuf : public std::streambuf {
  protected:
    /* data buffer:
     * - at most, four characters in putback area plus
     * - at most, six characters in ordinary read buffer
     */
    static const int putBackSize = 4 ;
    static const int bufferSize = putBackSize + 32768;    // size of the data buffer
    std::vector<char> buffer_vector ;
    char* buffer;
    int input_fd;

  public:
    /* constructor
     * - initialize empty data buffer
     * - no putback area
     * => force underflow()
     */
    josuttis_fd_inbuf( int _input_fd ) :
	buffer_vector(bufferSize),
	buffer(&buffer_vector[0]),
	input_fd(_input_fd)
    {
        setg (buffer+putBackSize,     // beginning of putback area
              buffer+putBackSize,     // read position
              buffer+putBackSize);    // end position
    }
  protected:
    // insert new characters into the buffer
    virtual int_type underflow () {

        // is read position before end of buffer?
        if (gptr() < egptr()) {
            return traits_type::to_int_type(*gptr());
        }

        /* process size of putback area
         * - use number of characters read
         * - but at most four
         */
        int numPutback;
        numPutback = gptr() - eback();
        if (numPutback > putBackSize) {
            numPutback = putBackSize;
        }

        /* copy up to four characters previously read into
         * the putback buffer (area of first four characters)
         */
        std::memmove (buffer+(putBackSize-numPutback), gptr()-numPutback,
                      numPutback);

        // read new characters
        int num;
        num = read (input_fd, buffer+putBackSize, bufferSize-putBackSize);
        if (num <= 0) {
            // ERROR or EOF
            return EOF;
        }

        // reset buffer pointers
        setg (buffer+(putBackSize-numPutback),   // beginning of putback area
              buffer+putBackSize,                // read position
              buffer+putBackSize+num);           // end of buffer

        // return next character
        return traits_type::to_int_type(*gptr());
    }
};

/*
 * An output stream that uses the above inbuf 
 *
 * Based on code example from page 673 (class fdostream)
 */

class josuttis_fdistream : public std::istream 
{
private:
	josuttis_fd_inbuf buf ;
public:
	josuttis_fdistream ( int fd ) :
		std::istream(0),
		buf(fd)
	{
		rdbuf(&buf) ;
	}
};


#endif
