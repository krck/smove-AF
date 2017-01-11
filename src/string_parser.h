//  string_parser.h
/*************************************************************************************
 *  smove-AF (ATMEL Firmware / CPU: Atmega1284P / Board: Melzi V2.0)                 *
 *-----------------------------------------------------------------------------------*
 *  Copyright (c) 2016, Peter Baumann                                                *
 *  All rights reserved.                                                             *
 *                                                                                   *
 *  Redistribution and use in source and binary forms, with or without               *
 *  modification, are permitted provided that the following conditions are met:      *
 *    1. Redistributions of source code must retain the above copyright              *
 *       notice, this list of conditions and the following disclaimer.               *
 *    2. Redistributions in binary form must reproduce the above copyright           *
 *       notice, this list of conditions and the following disclaimer in the         *
 *       documentation and/or other materials provided with the distribution.        *
 *    3. Neither the name of the organization nor the                                *
 *       names of its contributors may be used to endorse or promote products        *
 *       derived from this software without specific prior written permission.       *
 *                                                                                   *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND  *
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED    *
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
 *  DISCLAIMED. IN NO EVENT SHALL PETER BAUMANN BE LIABLE FOR ANY                    *
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES       *
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;     *
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND      *
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS    *
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                     *
 *                                                                                   *
 *************************************************************************************/

#pragma once
#ifndef STRING_PARSER_H_
#define STRING_PARSER_H_

#include <float.h>
#include "stdlib.h"
#include "motion.h"

float get_number(const byte* data, char letter);

void parse_string(byte* data) {
	if(!sizeof(data)) { return; }
	const byte letter = data[0];
	if(letter < 'A' || letter > 'Z') { return; }
	// Check G Codes and M Codes
	if(letter == 'G') {
		const uint8 number = get_number(data, 'G');
		if(number < 0 || number > 200) { return; }
		switch(number) {
			case 0:		parse_and_execute_G0(data);				break;
			case 1:		parse_and_execute_G1(data);				break;
			case 2:		parse_and_execute_G2G3(data, true);		break;
			case 3:		parse_and_execute_G2G3(data, false);	break;
			case 4:		parse_and_execute_G4(data);				break;
			case 17:						break;
			case 18:						break;
			case 19:						break;
			case 20:						break;
			case 21:						break;
			case 28:	/* Move to home */	break;
			case 53:						break;
			case 80:						break;
			case 93:						break;
			case 94:						break;
			default: break;
		}
	} else if(letter == 'M') {
		const uint8 number = get_number(data, 'M');
		if(number < 0 || number > 200) { return; }
		switch(number) {
			case 0:							break;
			case 1:							break;
			default: break;
		}
	}
	
}


// ------------------------------------------------------------------------
// --------------------- G / M CODE PARSING FUNCTIONS ---------------------
// ------------------------------------------------------------------------

// G00: Rapid positioning
// Move all Axis at fast speed until vector {X,Y,Z} is reached
// Parameter: Data-String without the Letter and Number (e.g.: No "G00 ")
void parse_and_execute_G0(byte* data) {
	const float moveX = get_number(data, 'X');
	const float moveY = get_number(data, 'Y');
	const float moveZ = get_number(data, 'Z');
	// Set the feed rate to max !!!!!!
	// Move all the Axis
	// linear_motion(...);
}

// G01: Linear interpolation
// Move in a straight line with normal Axis speed until vector {X,Y,Z} is reached
// Parameter: Data-String without the Letter and Number (e.g.: No "G00 ")
void parse_and_execute_G1(byte* data) {
	const float moveX = get_number(data, 'X');
	const float moveY = get_number(data, 'Y');
	const float moveZ = get_number(data, 'Z');
	const float feed = get_number(data, 'F');
	// Set the feed rate to f !!!!!!
	// Move all the Axis
	// linear_motion(...);
}

// G02 - G03: Arc motion
// Move in an clockwise (G02) or counter-clockwise (G03) arc until vector {X,Y} is reached
// Move only two Axis (X and Y) parallel. Z Axis arcs are not supported right now
void parse_and_execute_G2G3(byte* data, byte is_g2) {
	const float endX = get_number(data, 'X');
	const float endY = get_number(data, 'Y');
	const float centerX = get_number(data, 'I');
	const float centerY = get_number(data, 'J');
	const float feed = get_number(data, 'F');
	// set the feedrate
	// set_feedrate();
	
}

// G04: Dwell
// Machine waits for a number of milliseconds
void parse_and_execute_G4(byte* data) {
	const float dwell_milli = get_number(data, 'P');
	if(dwell_milli != FLT_MAX) {
		dwell_milliseconds(dwell_milli);
	}
}


// ------------------------------------------------------------------------
// --------------------------- HELPER FUNCTIONS ---------------------------
// ------------------------------------------------------------------------

// Parameter: Data-String and Char which number to extract
// Return: Number after a char e.g.: Returns 17 when data = G17
float get_number(const byte* data, char letter) {
	// Get position of the X and the next ' ' space chars
	uint8* pc = (strchr(data, letter) - (char*)data);
	if(pc != NULL) {
		const uint8 pos_char = *pc;
		uint8 pos_space = (strchr(data + pos_char, ' ') - (char*)data);
		// If pos_space is strange, the end of the string was reached / set it == length
		if(pos_space < 0 || pos_space >= BUF_SIZE) { pos_space = (uint8)strlen(data); }
		// Get all the chars between the letter and the space (e.g. "X015 ")
		// and put them into an new string
		const uint8 size = (pos_space - pos_char) - 1;
		char tmpstr[size];
		strncpy(tmpstr, (data + pos_char + 1), size);
		// Parse the number chars into an int16 value and return it;
		return (float)atof(tmpstr);	
	} else {
		return FLT_MAX;	
	}
}

#endif
