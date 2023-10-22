/*
 * sevenseg.h
 *
 * Created: 22.10.2023 14:01:26
 *  Author: Fabian
 */ 


#ifndef SEVENSEG_H_
#define SEVENSEG_H_


#define F_CPU 16000000UL // Taktrate des Controllers

#include <util/delay.h> // delay funktion
#include <avr/io.h> //IO ports

void print(int num, int numbs[]);

#endif /* SEVENSEG_H_ */