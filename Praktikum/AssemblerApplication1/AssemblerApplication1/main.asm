;
; P2.asm
;
; Created: 19.10.2023 17:15:13
; Author : gx
; Description: Uses PD0 and PD1 to control D0 and D9 respectively, as well as PD2 and PD3 as interrupt inputs connected to SW1 and SW2 respectively

.include <m328pdef.inc>

.def led_state_d0d9 = r17 ; 4bit d0-logic + 4bit d9-logic ; Reset idx3 (should never be set), Blink idx2, On idx1, Off idx0
.def led_output = r18
.def led_blinker = r19
.def d0_inverter = r20
.def d9_inverter = r21

.equ F_CPU = 16000000
.equ Prescaler = 1024
.equ DelayCycles = 10; (F_CPU / Prescaler) / 5

.cseg

.org 0x0000
    rjmp init

.org INT0addr
    rjmp int0_handler

.org INT1addr
    rjmp int1_handler

init:
    ldi r16, low(RAMEND)
    out SPL, r16
    ldi r16, high(RAMEND)
    out SPH, r16

    ldi r16, (1 << DDD0) | (1 << DDD1) ; 0b00000011
    out DDRD, r16 ; D0 / D9 LED output

    ldi r16, (0 << DDD2) | (0 << DDD3) ; 0b00000000
    out PORTD, r16 ; set D0 / D9 to off
    out DDRD, r16 ; INT0 / INT1 for SW1 / SW2 respectively

    ldi r16, (1 << WGM12) | (1 << CS10) | (1 << CS12) ; CTC and 1024 Prescaler
    sts TCCR1B, r16

    ldi r16, (1 << INT1) | (1 << INT0)
    out EIMSK, r16 ; enable external interrupt source INT0 and INT1
    ; EIFR (1 << INTF1) | (1 << INTF0) can be set now

    ldi r16, (1 << ISC01) | (1 << ISC11)
    sts EICRA, r16

    ldi r16, low(DelayCycles)
    sts OCR1AL, r16

    ldi r16, high(DelayCycles)
    sts OCR1AH, r16

    ldi d0_inverter, (1 << 5) | (1 << 4)
    ldi d9_inverter, (1 << 1) | (1 << 0)

	ldi led_state_d0d9, (1 << 4) | (1 << 0)

    ; enable interrupts
    sei

main_loop:
    ; keep in mind, that this main loop can be interrupted at any point, and has to be as fool proof as possible.

    ; delay
    sbis TIFR1, OCF1A
    rjmp main_loop

    sbi TIFR1, OCF1A

    ; d0_off
    sbrc led_state_d0d9, 4
    ldi led_output, (0 << DDD0)
    ; d9_off
    sbrc led_state_d0d9, 0
    ldi led_output, (0 << DDD1)

    ; d0_on
    sbrc led_state_d0d9, 5
    ldi led_output, (1 << DDD0)
    ; d9_on
    sbrc led_state_d0d9, 1
    ldi led_output, (1 << DDD1)

    ; d0_blink
    sbrc led_state_d0d9, 6
    eor led_state_d0d9, d0_inverter
    ; d9_blink
    sbrc led_state_d0d9, 2
    eor led_state_d0d9, d9_inverter

    out PORTD, led_output

    rjmp main_loop

int0_handler:
    ; rising edge of PD2 / SW1
    ; make sure, that other led is off
    sbrs led_state_d0d9, 0
    reti

    ; off -> on
    sbrc led_state_d0d9, 4
    ldi led_state_d0d9, (1 << 5) | (1 << 0)

    ; on -> blink
    sbrc led_state_d0d9, 5
    ldi led_state_d0d9, (1 << 6) | (1 << 5) | (1 << 0)

    ; blink -> off
    sbrc led_state_d0d9, 6
    ldi led_state_d0d9, (1 << 4) | (1 << 0)

    reti

int1_handler:
    ; rising edge of PD3 / SW2
    ; make sure, that other led is off
    sbrs led_state_d0d9, 4
    reti

    ; off -> on
    sbrc led_state_d0d9, 0
    ldi led_state_d0d9, (1 << 1) | (1 << 4)

    ; on -> blink
    sbrc led_state_d0d9, 1
    ldi led_state_d0d9, (1 << 3) | (1 << 2) | (1 << 4)

    ; blink -> off
    sbrc led_state_d0d9, 2
    ldi led_state_d0d9, (1 << 0) | (1 << 4)

    reti

.exit