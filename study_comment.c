#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

void	init_for_interrupt(void)
{
	cli(); // disable all interrupts
	MCUCR = 0x00; // MCU control register
	EICRA = 0x00; // External interrupt control register A -> INT0 ~ INT3
	EICRB = 0xF0; // External interrupt control register B -> INT4 ~ INT7
	EIMSK = 1 << INT7 | 1 << INT6; // External interrupt masking -> INT7, INT6 pin enable
	sei(); // re-enable interrupts
}

void	init_for_io(void)
{
	PORTA = 0x00;  // 7-Segment Display uses PA0~PA7 for a~g and dot1
	DDRA = 0xFF;   // PA0~PA7 are assigned to output pins
	PORTC = 0x0F;  // PC0~PC3 initially output high
	DDRC = 0x0F;   // PC0~PC3 are assigned to output pins
    PORTG = 0x00;
    DDRG = (1<<PG1) | (1<<PG0); // for LED driving
}

ISR (INT6_vect) // Interrupt service routine
{
	// something do;
}

void	led_and_switch(void)
{
	PORTG = {0x00, 0x01, 0x02, 0x03} // led
	if (PING & (1 << PG2))// PG2 switch check
	if (PING & (1 << PG3))// PG3 switch check
		//something
}

void	seven_segment_display(void)
{
	PORTA = SEG_CODE(num); // segment를 표현하는 방식
	//  a
	// f b
	//  g
	// e c
	//  d 시계방향 -> 중앙 순서
	// 예시) 0 표현 -> a,b,c,d,e,f -> 01111111 -> 0x3F
	PORTC = DISP_SEL(1); // 1번째 open -> 0111 -> 0x07
	PORTC = DISP_SEL(2); // 2번째 open -> 1011 -> 0x0B
	PORTC = DISP_SEL(3); // 3번째 open -> 1101 -> 0x0D
	PORTC = DISP_SEL(4); // 4번째 open -> 1110 -> 0x0E
	PORTC = DISP_SEL(0); // 전부 close, light off
}

void	interrtupt_main(void)
{
	EICRA = 0xF0; // -> INT3, INT2 동작 Synchronous trigger (I/O clock required)
	EICRB = 0xF0; // -> INT7, INT6 동작 Asynchronous trigger
	// A -> D 
	// B -> E 연결
}