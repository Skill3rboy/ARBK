/*
 * keys.h
 *
 * Created: 22.10.2023 14:01:35
 *  Author: Fabian
 */ 


#ifndef KEYS_H_
#define KEYS_H_

#include <avr/io.h> //IO ports
#include <avr/interrupt.h> // interrupts

#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))	// bit im IO-Register sfr clear, return 0 if set
// https://manpages.debian.org/testing/avr-libc/bit_is_clear.3avr.en.html 

void init();

#endif /* KEYS_H_ */