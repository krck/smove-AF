//  endstops.h
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
#ifndef ENDSTOPS_H_
#define ENDSTOPS_H_

#include "config.h"

// Set all Endstop Bits to input
void endstop_init() {
    CLEAR_BIT(DDRC, X_STOP);
    CLEAR_BIT(DDRC, Y_STOP);
    CLEAR_BIT(DDRC, Z_STOP);
}

// Return true (1) if a specific Endstop is reached
uint8 x_endstop() { return !IS_SET(PINC, X_STOP); }
uint8 y_endstop() { return !IS_SET(PINC, Y_STOP); }
uint8 z_endstop() { return !IS_SET(PINC, Z_STOP); }

// Retrun ture (1) if any Endstop is reached
uint8 any_endstop() { return (x_endstop() || y_endstop() || z_endstop()); }

#endif
