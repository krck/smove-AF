//  serial.h
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
#ifndef SERIAL_H_
#define SERIAL_H_

#include "config.h"

// -----------------------------------------------------
//    Using the USART Registers with the C functions
// provided in the ATMEL ATmega1284P Complete Data sheet
// -----------------------------------------------------

void serial_init() {
	// Set the BAUD rate
	UBRR0H = (byte)(MYUBRR >> 8);
	UBRR0L = (byte)MYUBRR;
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	// Set the frame format: 8data, 2stop bit
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void serial_transmit(byte data) {
	// Wait for empty transmit buffer
	while(!(UCSR0A & (1 << UDRE)));
	// Put data into buffer, sends the data
	UDR0 = data;
}

byte serial_receive() {
	// Wait for the data to be received
	while(!(UCSR0A & (1 << RXC)));
	// Get and return received data from buffer
	return UDR0;
}

void serial_receive_string(byte* buffer, uint8 max_size) {
  byte next_char;
  uint8 str_size = 0;
  // Get the first char
  next_char = serial_receive();
  // Get all chars till newline '\n'
  while(next_char != '\n' && str_size < max_size - 1) {
    *buffer++ = next_char;
    str_size++;
    next_char = serial_receive();
  }
  // max_size - 1 to add the '\0' break of a typical C-String
  *buffer = '\0';
}

void serial_flush() {
	byte dummy;
	while (UCSR0A & (1 << RXC)) dummy = UDR0;
}

#endif
