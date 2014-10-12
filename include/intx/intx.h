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

// The intxBuffer keeps track of a read or write process
typedef struct {
	void *data;
	struct {
		int byte, bit;
	} position;
} intxBuffer;

// Creates a buffer in the location pointed to by buffer which can store nBits
int intxAllocateBuffer(intxBuffer *buffer, int nBits);

// Frees the data contained within buffer
void intxFreeBuffer(intxBuffer *buffer);