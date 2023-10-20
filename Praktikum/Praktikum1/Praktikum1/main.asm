;
; Praktikum1.asm
;
; Created: 06.10.2023 12:35:32
; Author : Fabian
;
.include "m328pdef.inc" ; Prozessordefintionen laden
.def temp = r16 ; var temp
.def led = r17 

.org 0x000 ; Reset Vector
	jmp start

; Replace with your application code
start:
	ldi temp, LOW(RAMEND)
	out SPL, temp
	ldi temp, HIGH(RAMEND)
	out SPH, temp
	
	ldi temp, 0xFF ; leds anstellen
	out DDRD, temp 
	out DDRB, temp 

	ldi led,  0b0000_0001	//erstes Ledmuster
	rcall r_l ; erster Rechts-links aufruf
	
l_r:
	;ldi led, 0b0000_0010 ; zweite portb led ;Doppel instanz am rand
	;out PORTB, led
	;rcall delay
	ldi led, 0b0000_0001 ; erste portb led
	out PORTB, led
	rcall delay
	ldi led, 0 
	out PORTB, led ;portb reset
	ldi led,0b1000_0000 ;led
l_r2:
	
	out PORTD, led ; Ausgabe der Led
	lsr led ; rechtslaufen der Led
	rcall delay
	cpi led, 0b0000_0000 ; Muster vergleich, wenn die letzte Portd led an ist
	BRNE l_r2 ; solange noch nicht PortD leds durch sind neu aufrufen
	
ldi led,  0b0000_0010	;Doppelinstalz am rand 0b0000_0001
r_l:
	
	out PORTD, led ; Ausgabe der Led
	lsl led ; linkslaufen der Led
	rcall delay
	cpi led, 0b0000_0000 ; Muster vergleich, wenn die letzte Portd led an ist, wechsel zu port b
	BRNE r_l ; solange noch nicht PortD leds durch sind neu aufrufen
	out PORTD, led ;portd reset
	ldi led, 0b0000_0001 ; erste portb led
	out PORTB, led
	rcall delay
	ldi led, 0b0000_0010 ; zweite portb led
	out PORTB, led
	rcall delay
	jmp l_r ; rücklauf starten
	

delay:
; Assembly code auto-generated
; by utility from Bret Mulvey
; Delay 3 199 996 cycles
; 199ms 999us 750 ns at 16 MHz
//Loop funktioniert so dass runtergezählt wird
    ldi  r18, 17 
    ldi  r19, 60
    ldi  r20, 202
L1: dec  r20 // erster loop
    brne L1
    dec  r19 // zweiter loop
    brne L1
    dec  r18 // dritter loop
    brne L1
	ret