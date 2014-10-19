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
//             Copyright (C) 2014 \ Job Talle (job@ccore.org)                       //
//__________________________________________________________________________________//
//                                                                                  //
//      This program is free software: you can redistribute it and/or modify        //
//      it under the terms of the 3-clause BSD license.                             //
//                                                                                  //
//      You should have received a copy of the 3-clause BSD License along with      //
//      this program. If not, see <http://opensource.org/licenses/>.                //
//__________________________________________________________________________________//

#pragma once

#include <stdint.h>

// The unit of storage, ideally the target machine's word size
typedef int_fast32_t intxWord;

// The number of bits occupied by a single unit of storage
#define INTX_WORDSIZE 32

// The position of an intx buffer
typedef struct {
	unsigned int word;
	unsigned char bit;
} intxPosition;

// The intxBuffer keeps track of a read or write process
typedef struct {
	intxWord *data;
	unsigned int words;
	intxPosition position;
} intxBuffer;

// Creates a buffer in the location pointed to by buffer which can store nBits bits
int intxBufferAllocate(intxBuffer *buffer, unsigned int nBits);

// Frees the data contained within buffer
void intxBufferFree(intxBuffer *buffer);

// Writes an unsigned integer of nBits bits into the buffer
void intxBufferWriteUint(intxBuffer *buffer, unsigned int integer, unsigned int nBits);
// Writes a signed integer of nBits bits into the buffer
void intxBufferWriteInt(intxBuffer *buffer, int integer, unsigned int nBits);

// Reads nBits from buffer as an unsigned integer
unsigned int intxBufferReadUint(intxBuffer *buffer, unsigned int nBits);
// Reads nBits from buffer as a signed integer
int intxBufferReadInt(intxBuffer *buffer, int nBits);