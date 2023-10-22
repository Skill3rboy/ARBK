/*
 * keys.c
 *
 * Created: 22.10.2023 14:13:52
 *  Author: Fabian
 */ 

#include "keys.h"

void init()
{
	
	DDRD=0xff; // Port Ds als Output für 7segment
	PORTD= (1<<PIND0); 
	
	DDRB=0x01;	//Port B0 als Zehnerstelle im 7segment
	PORTB |= (1<<PINB1) | (1<<PINB2); // B1 und b2 als eingang für die Swtiches
	
	cli();
	PCICR |= 0x01;
	PCMSK0|=(1<<PINB1) | (1 << PINB2);
	sei();
}