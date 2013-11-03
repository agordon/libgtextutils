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

#ifndef __JOSUTTIS_FD_OUTBUF_H__
#define __JOSUTTIS_FD_OUTBUF_H__

/*
 * The following code example is taken from the book
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
 *  The file is available as "io/outbuf3.hpp" in the examples tarball at
 *    http://www.josuttis.com/libbook/
 *
 *  And in the book at Chapter 13, Page 673.
 *
 * Modifications:
 *    1. Larger buffer, with vector<char> 
 *    2. Accepts output file descriptor in c'tor
 */
#include <cstdio>
#include <streambuf>
#include <vector>

// for write():
#ifdef _MSC_VER
# include <io.h>
#else
# include <unistd.h>
#endif

class josuttis_fd_outbuf : public std::streambuf {
  protected:
    static const int bufferSize = 32768;   // size of data buffer

    /*
     * Note: The vector is used simply because it will manage the memory 
     * resource for us. The buffer is used as a regular C buffer. 
     * see "Effective STL" By Scott Meyer, Page 77,
     * Item 17: "Know how to pass vector and string to legacy API"
    */
    std::vector<char> buffer_vector ;
    char* buffer ;
    int output_fd ;

  public:
    /* constructor
     * - initialize data buffer
     * - one character less to let the bufferSizeth character
     *    cause a call of overflow()
     */
    josuttis_fd_outbuf ( int _output_fd ) :
	buffer_vector(bufferSize),
	buffer ( &buffer_vector[0] ),
	output_fd ( _output_fd )
    {
        setp (buffer, buffer+(bufferSize-1));
    }

    /* destructor
     * - flush data buffer
     */
    virtual ~josuttis_fd_outbuf () {
        sync();
    }

  protected:
    // flush the characters in the buffer
    int flushBuffer () {
        int num = pptr()-pbase();
        if (write (output_fd, buffer, num) != num) {
            return EOF;
        }
        pbump (-num);    // reset put pointer accordingly
        return num;
    }

    /* buffer full
     * - write c and all previous characters
     */
    virtual int_type overflow (int_type c) {
        if (c != EOF) {
            // insert character into the buffer
            *pptr() = c;
            pbump(1);
        }
        // flush the buffer
        if (flushBuffer() == EOF) {
            // ERROR
            return EOF;
        }
        return c;
    }

    /* synchronize data with file/destination
     * - flush the data in the buffer
     */
    virtual int sync () {
        if (flushBuffer() == EOF) {
            // ERROR
            return -1;
        }
        return 0;
    }
};


/*
 * An output stream that uses the above outbuf
 *
 * Based on code example from page 673 (class fdostream)
 */

class josuttis_fdostream : public std::ostream 
{
private:
	josuttis_fd_outbuf buf ;
public:
	josuttis_fdostream ( int fd ) :
		std::ostream(0),
		buf(fd)
	{
		rdbuf(&buf) ;
	}
};


#endif
