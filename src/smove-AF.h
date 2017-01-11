//  smove-AF.h
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
#ifndef SMOVE-AF_H_
#define SMOVE-AF_H_

#include "config.h"
#include "serial.h"
#include "string_parser.h"

void smoveAF_init() {
	// Initializes the serial communication
	serial_init();
	// Initializes the motion funcitons / structs
	// Calls the Endstop init function
	// Calls the Stepper-Motor init function
	motion_init();
}


// Firmware main loop
void smoveAF_loop() {

  while(1) {
  	// START EITHER "DIRECT CONTROL" OR
  	// "AUTOMATIC PROCESSING" MODE
  	
  	// if("DIRECT CONTROL") {
  	//	"PARSE AND EXECUTE THROUGH MANUAL 
  	//	 INPUT GENERATED G-CODE LINES"
  	//
  	// } else if("AUTOMATIC PROCESSING") {
  		// while("NOT M2 / PROGRAM END") {
  			byte data[BUF_SIZE];
			serial_receive_string(data, sizeof(data));	
			// HANDLE SERIAL ERRORS
			parse_string(data);
			// HANDLE PARSING, MOTION, ... ERRORS
			
			// SEND SINGAL THAT THE COMMAND WAS
			// PROCESSED AND EXECUTED AND THAT
			// THE LOOP IS WAITING FOR THE NEXT ONE
		// }
	// 
  	// } else { 
  	// 	"ERROR HANDLING" 
  	//	"SYSTEM RESET"
  	// 
  	// }
  	
  }
  
}

#endif
