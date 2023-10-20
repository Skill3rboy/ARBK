/*
 * Praktikum2I.c
 *
 * Created: 20.10.2023 14:14:12
 * Author : Fabian
 */ 

#define F_CPU 16000000UL // Taktrate des Controllers
#include <avr/io.h> //IO ports
#include <avr/interrupt.h> // interrupts
#include <util/delay.h> // delay funktion
#include <stdbool.h> // bool werte


#define LED0 PINB0 
#define LED9 PINB1
#define SW1 PIND2 // INT0
#define SW2 PIND3 // INT1

volatile int on= LED0; // bessere Lesbarkeit
volatile bool blink = true; 
/*
Help:
volatile -> nicht optimieren oder ändern

^= -> XOR
&= -> AND
|= -> OR
~ -> NOT

*/

void init()
{
	DDRB = 0xff; // Port B als ausgang 
	PORTB = 0x00;
	
	DDRD = 0x00; // Portd als Taster eingang
	PORTD |= (1<<SW1) | (1<<SW2);
	EICRA |= (1<<ISC11) | (1<<ISC01); // Fallende flanke = Interrupt Request
	EIMSK = (1<< INT0) | (1<< INT1); //INT schalten externen Interrupt frei
	sei(); // globale Interrupt maske
	
}

ISR(INT0_vect)
{
	if(on==LED0) // Wenn led0 an, dann soll modus gewechselt werden
	{
		blink=!blink;
	}
	else//wenn led 0 aus, schalten wir led9 aus und led 0 an
	{ 
		PORTB=(1<<LED0);
	}
	on=LED0;
}

ISR(INT1_vect)
{
	if(on==LED9) // Wenn led9 an, dann soll modus gewechselt werden
	{
		blink=!blink;
	}
	else//wenn led 9 aus, schalten wir led0 aus und led9 an
	{
		PORTB=(1<<LED9);
	}
	on=LED9;
}


int main(void)
{
	init(); // Port einrichten
    /* Replace with your application code */
    while (1) 
    {
		if(blink) // Blinkfunktion
		{
			PORTB ^= (1<<on);
		}
		else
		{
			PORTB =(1<<on); // Konstantes Leuchten
		}
		_delay_ms(200);
    }
}

/*
f) Interrupt start-> andere deatkivieren -> PC+1 -> Vektor laden -> ISR ausführen -> RETI -> Interrupts wieder aktivieren 
g) Vorteil ist dass erst wenn ein Ereigniss eintritt etwas passiert

*/

