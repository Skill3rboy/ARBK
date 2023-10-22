/*
 * Praktikum3.c
 *
 * Created: 22.10.2023 13:01:03
 * Author : Fabian
 */ 


#define F_CPU 16000000UL // Taktrate des Controllers
#include <avr/io.h> //IO ports
#include <avr/interrupt.h> // interrupts

volatile uint32_t Clk =0;
#define LED PIND0 // Led ausgang für lesbarkeit

/*
Help:
volatile -> nicht optimieren oder ändern

^= -> XOR
&= -> AND
|= -> OR
~ -> NOT

*/

void init(){
	DDRD= 0xff;		// Ports D als ausgang
	PORTD=0x00;
	
	TCCR0A = (1 << WGM01);						//  CTC Modus (Clear Timer on Compare Match) 
	TCCR0B |= (1 << CS01) | (1 << CS00);		// Prescale 64
	OCR0A = 249;								// if (OCR0A == Timer) -> Interupt
	TIMSK0 = (1 << OCIE0A);						// Interrupt timer anschalten
	sei();
}

ISR(TIMER0_COMPA_vect)
{
	Clk++;										//Timer-Counter
}

void waitFor(uint32_t ms)
{
	uint32_t ziel = Clk + ms; //Zielpunkt auf den wir warten
	
	if(ziel < Clk)	// Wenn ein overflow bei Ziel passiert ist
	{
		Clk=0;		//CLk reset
		while(Clk<ms) 
		{}
	}
	while(Clk < ziel) // Warte solange bis die CLK größer der Zielzeit ist
	{}
}

void waitUntil(uint32_t ms)
{
	while (Clk <=ms) // Wait until Clk ist größer/gleich ms
	{
	}
	
}
int main(void)
{
	init();
	
	waitUntil(5000); // Warte 5sekunden
	PORTD |= (1<<LED); // danach led an
    /* Replace with your application code */
    while (1) 
    {
		waitFor(2000); // Warte 2 sekunden
		PORTD ^= (1<<LED); // blinke blinke
    }
}

/* Aufgaben
a) Oben im Hilfe text
b) 4,294,967,295 (2^32-1) = 49,7 Tage
c) Overflow abfrage
d) Größeren Datentyp also bsp: uint64_t oder prescaler größer wählen
*/

