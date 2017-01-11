//  motion.h
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
#ifndef MOTION_H_
#define MOTION_H_

#include <math.h>
#include "config.h"
#include "system.h"
#include "stepper.h"
#include "endstops.h"

uint32 calc_steps(float mm, uint8 axis);
float atan3(float dy, float dx);

// -------------------------------------------------------------
// ------------------ MOTION DATA CONTAINERS -------------------
// -------------------------------------------------------------

// Motor positions in millimeters
// Soft-Stops are 0 and X/Y/Z_POS_MAX 
struct positions {
	float x;
	float y;
	float z;
} pos;

// Motor stepping speeds (feedrate in mm/min)
// x, y and z delay get calculated, based on the 
// freedrate and the specific Axis Step-per-Millimeter value
struct axis_speeds {
	uint32 feed_rate;
	uint16 x_delay;
	uint16 y_delay;
	uint16 z_delay;
} speed;


// -------------------------------------------------------------
// ------------------- MOTION INIT FUNCTION --------------------
// -------------------------------------------------------------

void motion_init() {
	memset(&pos, 0, sizeof(pos));
	memset(&speed, 0, sizeof(speed));
	// First initialize the Axis Endstops and the stepper motors
	endstop_init();
	stepper_init();
	// Reset all Axis positions
	goto_MACHINE_ZERO();
}


// -------------------------------------------------------------
// ---------------- FIX POSITIONING FUNCTIONS ------------------
// -------------------------------------------------------------

// Move to the endstops, then back to the soft limits
// and finally set all the positions to 0
void goto_MACHINE_ZERO() {
	uint8 xend = 0, yend = 0, zend = 0;
	// Set the steppers to slowest possible speed
	set_feedrate(MIN_FEEDRATE);
	enable_steppers();
	// Move all Axis till the endstop is reaced
	set_X_direction(true);
	set_Y_direction(true);
	set_Z_direction(false);
	
	while(!x_endstop()) { step_X(speed.x_delay); }
	while(!y_endstop()) { step_Y(speed.y_delay); }
	while(!z_endstop()) { step_Z(speed.z_delay); }
	
	//while(0) {
		//if(!x_endstop()) { step_X(speed.x_delay); } else { xend = 1; }
		//if(!y_endstop()) { step_Y(speed.y_delay); } else { yend = 1; }
		//if(!z_endstop()) { step_Z(speed.z_delay); } else { zend = 1; }
		//if(xend && yend && zend) { break; }
	//}
	// Move out of the enstops to the soft limits
	set_X_direction(false);
	set_Y_direction(false);
	set_Z_direction(true);
	
	for(uint16 i = 0; i < XY_SAVE_DIST; i++) { 
		step_X(speed.x_delay); 
		step_Y(speed.y_delay);
	}
	for(uint16 i = 0; i < Z_SAVE_DIST; i++) { step_Z(speed.z_delay); }
	disable_steppers();	
	// Set the positions to 0 at the soft limits
    pos.x = 0;
   	pos.y = 0;
   	pos.z = 0;
   	// Move Z to the idle pos (X and Y are already there)
	goto_Z_IDLE();
}

// Move the Axis to there idle-position (positive soft-limit) 
// (which is in X = 0, in Y = 0, and in Z = Z_POS_MAX)
void goto_X_IDLE() { linear_motion((pos.x * - 1.0f), 0.0f, 0.0f); }
void goto_Y_IDLE() { linear_motion(0.0f, (pos.y * - 1.0f), 0.0f); }
void goto_Z_IDLE() { linear_motion(0.0f, 0.0f, ((float)Z_POS_MAX - pos.z)); }


// -------------------------------------------------------------
// ---------------- MACHINE MOTION FUNCTIONS -------------------
// -------------------------------------------------------------

// MOVE ALL AXIS relative to the current position
// PARAMETERS distances to move for x, y and z in millimeters (can be +/- values)
// Uses the Bresenham's line Algorithm to move all axis simultaneously
//
//	2 _|           x   x 
//	1 _|   x   x   x
//	  _|___x______________
//	  0|  1|  2|  3|  4|
//
// E.g.:  linear_motion(4,2,0); will step: X, Y, X, X, Y, X
// to get from (0,0) to (4,2)
void linear_motion(float move_x, float move_y, float move_z) {
    uint32 maxsteps = 0;
    int32 over[AXIS];
    // get the deltas to move each axis as steps
    const uint32 deltas[AXIS] = { 	calc_steps(move_x, AXIS_NUM_X), 
    								calc_steps(move_y, AXIS_NUM_Y), 
    								calc_steps(move_z, AXIS_NUM_Z) };
    
    // check if the soft limits are reached, if so: abort
    if((pos.x + move_x < X_POS_MAX) || (pos.x + move_x > ALL_POS_MIN)) { return; }
    if((pos.y + move_y > Y_POS_MAX) || (pos.y + move_y < ALL_POS_MIN)) { return; }
    if((pos.z + move_z > Z_POS_MAX) || (pos.z + move_z < ALL_POS_MIN)) { return; }
    // Get the biggest number of steps
    for(uint8 i = 0; i < AXIS; i++) { if(maxsteps < deltas[i]) maxsteps = deltas[i]; }
    for(uint8 i = 0; i < AXIS; i++) { over[i] = maxsteps / 2; }
    
    enable_steppers();
    // set the stepper directions to move each axis
    set_X_direction((move_x > 0) ? 1 : 0);
    set_Y_direction((move_y > 0) ? 0 : 1);
    set_Z_direction((move_z > 0) ? 1 : 0);
    // Bresenham's line Algorithm
    // Loop for the biggest distance one of the Axis has to move
    // This "main axis" steps every time / the other two axis occasionally
    for(uint32 i = 0; i < maxsteps; i++) {
        for(uint8 a = 0; a < AXIS; a++) {
            // Add the step-delta to over for each Axis
            // If this is bigger than the maxstep count then
            // move the Axis, and lower the over value again
            over[a] += deltas[a];
            if(over[a] >= maxsteps) {
                over[a] -= maxsteps;
                // Actually step the current axis
                if(a == AXIS_NUM_X) step_X(speed.x_delay);
                else if(a == AXIS_NUM_Y) step_Y(speed.y_delay);
                else if(a == AXIS_NUM_Z) step_Z(speed.z_delay);
            }
            // Check if the hard limits (endstops) are reached, if so: abort
            // Highly unlikely, but safety first !!!1!!
            if(any_endstop()) { return; }
        }
    }
    disable_steppers();
    // update the positions
    pos.x += move_x;
    pos.y += move_y;
    pos.z += move_z;
}

// MOVE X ans Y AXIS in a clockwise or counter-clockwise arc
// PARAMETERS distances to arc center from current position
// PARAMETERS x and y end position and direction (cw / ccw)
// This method assumes arcs are not >180 degrees (PI radians)
void arc_motion(float center_x,float center_y, float end_x, float end_y, uint8 dir) {
	// check if the soft limits are reached, if so: abort
	if((pos.x + end_x < X_POS_MAX) || (pos.x + end_x > ALL_POS_MIN)) { return; }
    if((pos.y + end_y > Y_POS_MAX) || (pos.y + end_y < ALL_POS_MIN)) { return; }
    	
    	// get radius
    	const float delta_x = pos.x - center_x;
    	const float delta_y = pos.x - center_y;
    	const float radius = sqrt((delta_x * delta_x) + (delta_y * delta_y));

  	// find angle of arc (sweep)
  	float angle1 = atan3(delta_y, delta_x);
  	float angle2 = atan3((end_y - center_y), (end_x - center_x));
	float theta = angle2 - angle1;
  	
  	// Check the direction (clockwise / counterclockwise)
  	if(dir > 0 && theta < 0) { angle2 += 2 * M_PI; }
  	else if(dir == 0 && theta > 0) { angle1 += 2 * M_PI; }
  	
	// get length of arc
	// float circ=PI*2.0*radius;
	// float len=theta*circ/(PI*2.0);
	// simplifies to
	const float len = abs(theta) * radius;
	const uint32 segments = ceil(len * MM_PER_SEGMENT);
	
	float nx, ny, angle3, scale;
	
	for(uint32 i = 0; i < segments; i++) {
		// interpolate around the arc
		scale = ((float)i) / ((float)segments);
		angle3 = (theta * scale) + angle1;
		nx = center_x + cos(angle3) * radius;
		ny = center_y + sin(angle3) * radius;
		// move along the small line
		linear_motion(nx, ny, 0.0f);
	}
	// move the last little line
	linear_motion(end_x, end_y, 0.0f);
	// update the positions
	pos.x += end_x;
	pos.y += end_y;
}


// -------------------------------------------------------------
// ----------------- MOTION HELPER FUNCTIONS -------------------
// -------------------------------------------------------------

// Not completely accurate but its just some
// delay-time so it doesn't really matter
void dwell_milliseconds(uint16 ms) {
	for(uint16 i = 0; i < ms; i++) { _delay_ms(1); }
}

// returns angle of dy/dx as a value from 0...2PI
float atan3(float dy, float dx) {
	float a = atan2(dy, dx);
	if(a < 0) { a = (3.1415f * 2.0) + a; }
	return a;
}

// Calculates the absolute steps for an axis
// based on a millimeter value
uint32 calc_steps(float mm, uint8 axis) {
	if(axis == AXIS_NUM_X) { return abs((int32)(mm * X_STEPS_MM)); }
	else if(axis == AXIS_NUM_Y) { return abs((int32)(mm * Y_STEPS_MM)); }
	else if(axis == AXIS_NUM_Z) { return abs((int32)(mm * Z_STEPS_MM)); }
	else { return 0; }
}

// Set the general feed rate and calculate the delay between steps
// (Not perfectly precise when it comes to the actual delay between
// steps, because of rounding it could be up to 50 microseconds off)
void set_feedrate(float mm_min) {
    if(mm_min != speed.feed_rate) {
        // catch crazy values and keep the speed within a harmless range
        if(mm_min > MAX_FEEDRATE) { mm_min = MAX_FEEDRATE; }
        else if(mm_min < MIN_FEEDRATE) { mm_min = MIN_FEEDRATE; }
        // Get the "Steps-per-Millisecond" from the "Millimeters-per-Minute" parameter
        const float X_step_milli = (mm_min * X_STEPS_MM) / 60000.0f;
        const float Y_step_milli = (mm_min * Y_STEPS_MM) / 60000.0f;
        const float Z_step_milli = (mm_min * Z_STEPS_MM) / 60000.0f;
        // Calculate the delay for each axis
        // (1 / X_step_milli): gets the delay in milliseconds for one step
        // * 5: to get the count how often _delay_us(100); will be executed.
        // * 5: (and not * 10) because there are two delay loops for each step.
        speed.x_delay = (uint16)round((1 / X_step_milli) * 5);
        speed.y_delay = (uint16)round((1 / Y_step_milli) * 5);
        speed.z_delay = (uint16)round((1 / Z_step_milli) * 5);
        speed.feed_rate = mm_min;
    }
}

#endif
