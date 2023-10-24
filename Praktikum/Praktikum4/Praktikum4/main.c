/*
 * Praktikum4.c
 *
 * Created: 22.10.2023 13:59:04
 * Author : Fabian
 */ 



#include "keys.h"
#include "sevenseg.h"

int numbs[10]={ 64, 121, 36, 48, 25, 18, 2, 120, 0, 16 }; // Zahlen aus dem Sheet für die binäre darstellung 0-9
volatile uint32_t counter=0;
/*
Help:
volatile -> nicht optimieren oder ändern
sevensegment: 0: an | 1: aus
^= -> XOR
&= -> AND
|= -> OR
~ -> NOT

Zahlenanzeige : gfe dcba

0:  100 0000	= 64
1:  111 1001	= 121
2:  010 0100	= 36
3:	011 0000	= 48
4:  001 1001	= 25
5:  001 0010	= 18
6:  000 0010	= 2
7:  111 1000	= 120
8:  000 0000	= 0
9:  001 0000	= 16
*/

ISR(PCINT0_vect)
{
	if(!(PINB&(1<<PINB1))) // SW1 pressed?
		{
			if(counter==0)
			{
				counter=100; //wir wollen runterzählen aber 0 ist ende, also setzen wir ihn nach das ende
			}
			counter--;
		}
	if(!(PINB&(1<<PINB2))) // SW2 pressed?
		{
			if(counter==99)
			{
				counter=-1;  // wir wollen hochzählen aber 99 ist ende, also setzten wir ihn vor den Anfang
			}
			counter++;
		}
}


int main(void)
{
	init();
    /* Replace with your application code */
    while (1) 
    {
		int einser = counter % 10; // Berechnet die einser stelle mit hilfe Modulo
		int zehner = (counter-einser) / 10 ; // Berechnet die Zehner stelle mit 10 Geteilt 
		
		print(einser,numbs);
		print(zehner,numbs);
    }
}

