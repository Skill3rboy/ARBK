;
; HelloWorld.asm
;
; Created: 06.10.2023 12:03:19
; Author : Fabian
;


.org 0x000
	rjmp start

; Replace with your application code
start:
    ldi r16, LOW( RAMEND )
	out SPL, r16
	ldi r16, HIGH( RAMEND )
	out SPH, r16

	ldi r16, 0b0100000
	out DDRB, r16

main: 
	in r16, PORTB
	ldi r17,1<<5
	eor r16, r17
	out PORTB, r16
	rcall delay

	rjmp main

delay:
	ldi r18, 127

l0:
	ldi r19, 127

l1:
	ldi r20, 127

l2:
	dec r20
	brne l2
	dec r19
	brne l1
	dec r18
	brne l0
	ret
