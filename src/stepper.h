//  stepper.h
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
#ifndef STEPPER_H_
#define STEPPER_H_

#include "config.h"

void stepper_init() {
	// Set all Stepper Bits to output
	SET_BIT(DDRD, N_XYE_ENABLE);
	SET_BIT(DDRA, N_Z_ENABLE);
	disable_steppers();
	// X Stepper: Set bits to output and clear STEP / DIR
	SET_BIT(DDRC, X_DIR);
	SET_BIT(DDRD, X_STEP);
	CLEAR_BIT(PORTC, X_DIR);
	CLEAR_BIT(PORTD, X_STEP);
	// Y Stepper: Set bits to output and clear STEP / DIR
	SET_BIT(DDRC, Y_DIR);
	SET_BIT(DDRC, Y_STEP);
	CLEAR_BIT(PORTC, Y_DIR);
	CLEAR_BIT(PORTC, Y_STEP);
	// Y Stepper: Set bits to output and clear STEP / DIR
	SET_BIT(DDRB, Z_DIR);
	SET_BIT(DDRB, Z_STEP);
	CLEAR_BIT(PORTB, Z_DIR);
	CLEAR_BIT(PORTB, Z_STEP);
}


// Enable all stepper controllers by clearing !XYEENABLE and !ZENABLE
void enable_steppers() {
	CLEAR_BIT(PORTD, N_XYE_ENABLE);
	CLEAR_BIT(PORTA, N_Z_ENABLE);
}
// Disable all stepper controllers by setting !XYEENABLE and !ZENABLE
void disable_steppers() {
	SET_BIT(PORTD, N_XYE_ENABLE);
	SET_BIT(PORTA, N_Z_ENABLE);
}


// Set the X Axis direction (+ / -)
void set_X_direction(byte plus) {
	if(plus) { CLEAR_BIT(PORTC, X_DIR); }
	else { SET_BIT(PORTC, X_DIR); }
}
// Step the X Axis Motor one Step (the speed depends on the delay)
void step_X(uint16 delay) {
	SET_BIT(PORTD, X_STEP);
	for(uint16 d = 0; d < delay; d++) { _delay_us(100); }
	CLEAR_BIT(PORTD, X_STEP);
	for(uint16 d = 0; d < delay; d++) { _delay_us(100); }
}


// Set the Y Axis direction (+ / -)
void set_Y_direction(byte plus) {
	if(plus) { CLEAR_BIT(PORTC, Y_DIR); }
	else { SET_BIT(PORTC, Y_DIR); }
}
// Step the Y Axis Motor one Step (the speed depends on the delay)
void step_Y(uint16 delay) {
	SET_BIT(PORTC, Y_STEP);
	for(uint16 d = 0; d < delay; d++) { _delay_us(100); }
	CLEAR_BIT(PORTC, Y_STEP);
	for(uint16 d = 0; d < delay; d++) { _delay_us(100); }
}


// Set the Z Axis direction (+ / -)
void set_Z_direction(byte plus) {
	if(plus) { CLEAR_BIT(PORTB, Z_DIR); }
	else { SET_BIT(PORTB, Z_DIR); }
}
// Step the Z Axis Motor one Step (the speed depends on the delay)
void step_Z(uint16 delay) {
	SET_BIT(PORTB, Z_STEP);
	for(uint16 d = 0; d < delay; d++) { _delay_us(100); }
	CLEAR_BIT(PORTB, Z_STEP);
	for(uint16 d = 0; d < delay; d++) { _delay_us(100); }
}

#endif
