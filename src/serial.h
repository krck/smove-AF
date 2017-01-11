//  serial.h
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
