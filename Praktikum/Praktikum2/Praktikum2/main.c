/*
 * Praktikum2.c
 *
 * Created: 20.10.2023 11:13:09
 * Author : Fabian
 */ 
#define F_CPU 16000000UL // Taktrate des Microcontrollers
#include <avr/io.h> // IO ports
#include <stdbool.h> // für bool
#include <util/delay.h> // Für delay
#define SW1 PINC0 // Aliase damit ich es besser lesen kann
#define SW2 PINC1
#define LED0 PIND0
#define LED9 PIND1

int on =LED0; // aus und an, damit ich einfach hin und her swappen kann
int off =LED9;
bool blink=true; // bool ob es blinken soll oder nicht
/*
Help:
^= -> XOR
&= -> AND
|= -> OR
~ -> NOT
*/
void init()
{
	DDRC= 0x00; // Port C als ein Eingang schalten
	PORTC=0xFF;
	
	DDRD=0xFF; // Port D als Ausgang schalten
	PORTD=0x00;
}


void button() 
{
	if(!(PINC &(1<<SW1))) //Prüft ob gedrückt
	{
		if(PIND & (1 << LED0))						// Wenn die LED0 an ist
		{
			blink ^= 1;							//blinken durchschalten mit XOR
		}
		else if(PIND & (1 << LED9))					// LED swap
		{
			off = LED9;
			on = LED0;
		}
	}
	if(!(PINC & (1 << SW2))) // Prüft ob gedrückt
	{
		if(PIND & (1 << LED9))						// Wenn die LED9 an ist
		{
			blink ^= (1 << 0);						//blinken durchschalten mit XOR
		}
		else if((PIND & (1 << LED0)))				// LED swap
		{
			off = LED0;
			on = LED9;
			
		}
	}
}

int main(void)
{
	init();
    /* Replace with your application code */
    while (1) 
    {
		button();
		if(blink)
		{
			PORTD &= ~(1 << off); // off soll off bleiben
			PORTD ^= (1 << on);	// XOR- für blink instanz
		}else{
			PORTD &= ~(1 << off); // led off soll off bleiben
			PORTD |= (1 << on); // Or- für Konstantes an 
		}
	_delay_ms(200);
	}
}

