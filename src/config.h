//  config.h
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
#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "bit_fiddle.h"

// -------------------------------------------------------
// ---------------- GENERAL BOARD SETTINGS ---------------
// ------------------ BOARD: MELZI V 2.0 -----------------
// -------------------------------------------------------
#define F_CPU			16000000UL					// CPU Frequency (16 MHz)

// REGISTER A BITS
#define SD_SS			0
#define EXT_A1			1
#define EXT_A2			2
#define EXT_A3			3
#define EXT_A4			4							// LED also on this Pin
#define N_Z_ENABLE		5							// !Z_ENABLE
#define BED_TEMP		6
#define END_TEMP		7
// REGISTER B BITS
#define E_DIR			0
#define E_STEP			1
#define Z_DIR			2
#define Z_STEP			3
#define N_FAN			4							// !FAN
#define MOSI			5
#define MISO			6
#define SCLK			7
// REGISTER C BITS
#define EXT_SCL			0
#define EXT_SDA			1
#define X_STOP			2
#define Y_STOP			3
#define Z_STOP			4
#define X_DIR			5
#define Y_STEP			6
#define Y_DIR			7
// REGISTER D BITS
#define AIFO			0
#define AOFI			1
#define EXT_RX1			2
#define EXT_TX1			3
#define N_HOTBED		4							// !HOTBED
#define N_HOTEND		5							// !HOTEND
#define N_XYE_ENABLE	6							// !XYE_ENABLE
#define X_STEP			7

// -------------------------------------------------------
// ------------ SERIAL COMMUNICATION SETTINGS ------------
// -------------------------------------------------------
#define BAUD			57600						// Baud Rate
#define MYUBRR			(((F_CPU / (BAUD * 16UL))) - 1)

#define BUF_SIZE		128							// size of the string buffer / should be 256 (G Code Standard)

#define RXC				7
#define TXC				6
#define UDRE			5

// -------------------------------------------------------
// ---------------- MOTOR CONTROL SETTINGS ---------------
// -------------------------------------------------------
#define AXIS            3                           // Number of Axis - 3 = X, Y, Z
#define AXIS_NUM_X      0 
#define AXIS_NUM_Y      1
#define AXIS_NUM_Z      2

#define MAX_FEEDRATE	800.0f						// Fastest rate mm/min the Stepper Motors should move
#define MIN_FEEDRATE	200.0f					    // Slowest rate mm/min the Stepper Motors should move

#define X_STEPS_MM      100							// X Axis motor steps to move 1 millimeter
#define Y_STEPS_MM      100							// Y Axis motor steps to move 1 millimeter
#define Z_STEPS_MM      200							// Z Axis motor steps to move 1 millimeter

#define ALL_POS_MIN     0                           // Negative Soft-Limit for all the Axis
#define X_POS_MAX       -200.0f						// Millimeters till positive X Soft-Limit is reached
#define Y_POS_MAX		200.0f						// Millimeters till positive Y Soft-Limit is reached
#define Z_POS_MAX		250.0f						// Millimeters till positive Z Soft-Limit is reached

#define XY_SAVE_DIST    2000						// Steps between end stop and soft-stop for the X and Y Axis
#define Z_SAVE_DIST		2000						// Steps between end stop and soft-stop for the Z Axis

#define ARC_CW          1							// Set arc direction to clockwise (used with G2)
#define ARC_CCW         0							// Set arc direction to counter-clockwise (used with G3)
#define MM_PER_SEGMENT  5							// Arc function: Length of arc (line) segment


// -------------------------------------------------------
// --------------- SPECIAL TYPE DEFINITIONS --------------
// -------------------------------------------------------
typedef	unsigned char	byte;
typedef int8_t			int8;						// 8 Bit    -128..127
typedef int16_t			int16;						// 16 Bit   -32768..32767
typedef int32_t			int32;						// 32 Bit   -2147483648..2147483647
typedef uint8_t			uint8;						// 8 Bit    0..255
typedef uint16_t		uint16;						// 16 Bit   0..65535
typedef uint32_t		uint32;						// 32 Bit   0..4294967295

#endif
