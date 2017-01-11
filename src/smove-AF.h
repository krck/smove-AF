//  basicCNC_Firmware.h
/*************************************************************************
 * smove-AF (ATMEL Firmware / CPU: Atmega1284P / Board: Melzi V2.0)
 *------------------------------------------------------------------------
 * Copyright (c) 2016 Peter Baumann
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would
 *    be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not
 *    be misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
 *************************************************************************/

#pragma once 
#ifndef BASICCNC_FIRMWARE_H_
#define BASICCNC_FIRMWARE_H_

#include "config.h"
#include "serial.h"
#include "string_parser.h"

// Call the whole tree of init functions
void basicCNC_Firmware_init() {
	// Initializes the serial communication
	serial_init();
	// Initializes the motion funcitons / structs
	// Calls the Endstop init function
	// Calls the Stepper-Motor init function
	motion_init();
}


// Firmware main loop
void basicCNC_Firmware_loop() {
  
  // linear_motion(100, false, 100, false, 0, false);
  
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
