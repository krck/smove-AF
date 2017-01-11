//  bit_fiddle.h
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
#ifndef BIT_FIDDLE_H_
#define BIT_FIDDLE_H_

#define LOW		0
#define HIGH	1
#define false	0
#define true	1

// Manipulation (write bit to register)
#define SET_BIT(reg, bit)       (reg |= (1<<bit))       // Set a Bit in an Register to 1
#define CLEAR_BIT(reg, bit)     (reg &= ~(1<<bit))      // Set a Bit in an Register to 0
#define TOGGLE_BIT(reg, bit)    (reg ^= (1<<bit))       // Negate a Bit in an Register
// Selection (read bit from register)
#define IS_SET(reg, bit)        (reg & (1<<bit))        // Check if a Bit in an Register is 1
#define IS_CLEAR(reg, bit)      (!(reg & (1<<bit)))     // Check if a Bin in an Register is 0

#endif