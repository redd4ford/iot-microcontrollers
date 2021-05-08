;
; Lab8.asm
;
; Created: 17/04/2021 11:59:53
; Author : Viktoriia
;
.include "m2560def.inc"

.macro outi															; write from constant
	ldi _swap, @1
	.if @0 < 0x40													; register has max of 0x3F address
		out @0, _swap
	.else
		sts @0, _swap
	.endif
.endmacro

.macro outr															; write from register
	mov _swap, @1
	.if @0 < 0x40
		out @0, _swap
	.else
		sts @0, _swap
	.endif
.endmacro

																	; registers
.def	_low		=r16											; I/O ports states
.def	_high		=r17
.def	_swap		=r18											; register for outi and outr

.def	_logic		=r0												; 1=HIGH - button1; 2=HIGH - button2
.def	_counter1	=r19

.def	_delay1		=r20											; registers for delay
.def	_delay2		=r21

.def	_temp		=r22
.def	_start1		=r23											; PORTC states
.def	_end1		=r24
.def	_start2		=r25											; PORTK states

																	; SRAM
.DSEG

																	; FLASH
.CSEG																; VECTOR OF INTERRUPTS
		.org 0x000													; the program starts at the zero address (w/out the bootloader)
			rjmp reset
		.org OC4Aaddr												; exit interruption
			rjmp TIMER4_COMPA

																	; TIMER4 COMPARE MATCH A
TIMER4_COMPA:															
		sbrs	_logic, 1											; skip if bit1 is set in _logic
		rjmp	end_algorithm1										; goto end_algorithm1
		cp		_start1, _end1										; compare _start1 and _end1
		brmi	reset_algorithm1									; goto reset_algorithm1 if _start1 < _end1


start_algorithm1:
		inc		_counter1											; _counter1 ++
		sbrc	_counter1, 0										; if bit is not clean, execute next
		rjmp	a1_end												; goto a1_end


a1_start:
		out		PORTC, _start1										; write data from _start1 to I/O port
		lsr		_start1												; logic right shift
		lsl		_end1												; logic left shift
		rjmp	end_algorithm1										; goto end_algorithm1


a1_end:
		out		PORTC, _end1										; write data from _end1 to I/O port
		rjmp	end_algorithm1										; goto end_algorithm1
		

reset_algorithm1:
		outr	PORTC, _low
		clt															; clear flag T
		bld		_logic, 1											; load flag T to bit1 in _logic


end_algorithm1:
		sbrs	_logic, 2											; skip the next statement if bit2 is set in _logic
		brmi	reset_algorithm2


start_algorithm2:
		mov		_temp, _start2										; copy _temp to _start2
		outr	PORTK, _temp
		lsr		_start2												; logic right shift
		rjmp	end_algorithm2										; goto end_algorithm2


reset_algorithm2:
		outr	PORTK, _low
		clt															; clear flag T
		bld		_logic, 2											; load flag T to bit2 in _logic


end_algorithm2:
		reti														; return from interruption

																	; STACK INITIALIZATION
reset:																	
		ldi		_temp, Low(RAMEND)
		out		SPL, _temp											; RAMEND is the last cell in RAM; SPL - stack point low
		ldi		_temp, High(RAMEND)
		out		SPH, _temp											; SPH - stack point high
																	; I/O PORTS INITIALIZATION
		ldi		_low, 0x00											; 0 - low, 1 (255) - high
		ldi		_high, 0xFF											; _low and _high are needed for I/O ports initialization

		outr	ACSR, _low											; turn off the comparator to lower the energy consumption
																	; PORTC - OUTPUT, LOW (PINS PC0-PC7)
		out		DDRC, _high
		out		PORTC, _low
																	; PORTK - OUTPUT, LOW (PINS PK0-PK7)
		outr	DDRK, _high
		outr	PORTK, _low
																	; PORTD - OUTPUT, LOW (BUZZER PD0)
		out		DDRD, _high
		out		PORTD, _low
																	; PORTA - INPUT, PULLUP (BUTTONS PA4, PA6)
		out		DDRA, _low
		ldi		_high, (1<<DDA4) | (1<<DDA6)
		out		PORTA, _high
																	; TIMER INITIALIZER
		cli															; clear global interruption flag
		outi	OCR4AH, 0x2A										; 60 ticks = 1000 ms; 42 ticks = 700 ms
		outi    OCR4AL, 0xB9
		outi	TCCR4A, 0x00
		outi	TCCR4B, (1 << WGM42) | (1 << CS42) | (1 << CS40)
		outi	TIMSK4, (1 << OCIE4A)
		sei															; set global interruption flag


main:
		sbic	PINA, 4												; if button1 is pressed (bit1 == LOW),
		rjmp	trigger_button1										; goto trigger_button1
		clr		_counter1											; reset the counter
		ldi		_start1, 0b10000000
		ldi		_end1, 0b00000001

		set															; set flag T
		bld		_logic, 1											; load flag T to bit1 in _logic

		sbi		PORTD, 0											; set the register as I/O										
		rcall	delay200ms											; call buzzer
		cbi		PORTD, 0											; clear the bits of an I/O register											

trigger_button1:
		sbic	PINA, 6												; if button2 is pressed (bit2 == LOW),
		rjmp	trigger_button2										; goto trigger_button2
		ldi		_start2, 0b10000000

		set															; set flag T
		bld		_logic, 2											; load flag T to bit2 in _logic

		sbi		PORTD, 0											; set the register as I/O										
		rcall	delay200ms											; call buzzer
		cbi		PORTD, 0											; clear the bits of an I/O register												

trigger_button2:
		rjmp main													; loop main
																	; DELAYS
delay200ms:
		ldi		_delay1, 0x00
		ldi		_delay2, 0xC8										; 200 ms = 0xC8
delay:
		subi	_delay1, 1											; substract 1 from _delay1
		sbci	_delay2, 0											; substract 0 with shift
		brne	delay												; if _delay1 != _delay2, goto delay
		ret															; else finish the subroutine

																	; EEPROM
.ESEG