//__________________________________________________________________________________//
//                                                                                  //
//                               _       _                                          //
//                              (_)     | |                                         //
//                               _ _ __ | |___  __                                  //
//                              | | '_ \| __\ \/ /                                  //
//                              | | | | | |_ >  <                                   //
//                              |_|_| |_|\__/_/\_\ 1.0                              //
//                                                                                  //
//                                                                                  //
//             Copyright (C) 2014 \ Job Talle (jobtalle@ccore.org)                  //
//__________________________________________________________________________________//
//                                                                                  //
//      This program is free software: you can redistribute it and/or modify        //
//      it under the terms of the 3-clause BSD license.                             //
//                                                                                  //
//      You should have received a copy of the 3-clause BSD License along with      //
//      this program. If not, see <http://opensource.org/licenses/>.                //
//__________________________________________________________________________________//

#pragma once

// A position of an intx buffer
typedef struct {
	unsigned int byte, bit;
} intxPosition;

// The intxBuffer keeps track of a read or write process
typedef struct {
	void *data;
	intxPosition position;
} intxBuffer;

// Creates a buffer in the location pointed to by buffer which can store nBits
int intxBufferAllocate(intxBuffer *buffer, int nBits);

// Frees the data contained within buffer
void intxBufferFree(intxBuffer *buffer);

// Writes nBits bits of signed integer into the buffer
int intxBufferWriteUint(intxBuffer *buffer, unsigned int integer, int nBits);

// Reads nBits from buffer as an unsigned integer
unsigned int intxBufferReadUint(intxBuffer *buffer, int nBits);