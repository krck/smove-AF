//  stepper.h
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
#ifndef STEPPER_H_
#define STEPPER_H_

#include "config.h"

void stepper_init() {
    // Set Enable-Disable Motor Bits to output
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
    // Z Stepper: Set bits to output and clear STEP / DIR
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
