/*
 * sevenseg.c
 *
 * Created: 22.10.2023 14:00:27
 *  Author: Fabian
 */ 

#include "sevenseg.h"

void print(int num,int numbs[])
{
	PORTD = numbs[num];
	_delay_ms(10);
	PORTB ^= (1<<PINB0);
}