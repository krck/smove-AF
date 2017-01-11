//  system.h
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
#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "config.h"

typedef enum err { FAIL, FATAL_ERROR, PANIC } error;

struct sys {
  uint8 state;                // system state (e.g.: running, idle, stopped, ...)
  byte control;               // system control state ("direct control", "automatic processing", ...)
  uint8 mode;                 // operation mode (e.g.: serial_get, serial_send, linear motion, dwell, ...)
  error err_code;             // error in current operation mode (Check after each operation)
  // ...
} systm;

void system_reset() { }       // Hard reset (Set Hardware-Reset Pin)
void system_restart() { }     // Contolled restart (Only Firmware)

#endif
