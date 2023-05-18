#include "USART.h"
#include "SEG_MODULE.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdlib.h>

volatile unsigned int cnt;
volatile unsigned int timer;
volatile unsigned int input;

void	init_all()
{
	cli();
	PORTA = 0x00;  // 7-Segment Display uses PA0~PA7 for a~g and dot1 
	DDRA = 0xFF;   // PA0~PA7 are assigned to output pins
	PORTC = 0x0F;  // PC0~PC3 initially output high
	DDRC = 0x0F;   // PC0~PC3 are assigned to output pins

	UCSR1A = 0x00; // USART initialization
	UCSR1B = 0x98; // rx, tx enable + Rx complete Interrupt enable
	UCSR1C = 0x06; // No parity, 1 stop bit, 8 data bit frame
	UBRR1H = 0x00;  // USART mode :  Asynchronous (without XCLK)
	UBRR1L = BAUD_9600;

	MCUCR = 0x00;
	EICRB = 0xFF;
	EIMSK = 1 << INT7 | 1 << INT6 | 1 << INT5 | 1 << INT4;

	TCNT0 = 0x00;
	TCCR0 = 1 << CS02 | 1 << CS01;
	TIMSK = 1 << TOIE0;
	cnt = 0;
	timer = 0;
	sei();

	DDRG = 1 << PG0;
}

ISR(TIMER0_OVF_vect)
{
	cnt++;
	if (cnt == 100)
	{
		cnt = 0;
		timer++;
	}
}

ISR(INT4_vect)
{
	tx_string("Left\n");
}

ISR(INT5_vect)
{
	tx_string("Down\n");
}

ISR(INT6_vect)
{
	tx_string("Up\n");
}

ISR(INT7_vect)
{
	tx_string("Right\n");
}

void	do_level()
{
	while (1)
	{
		tx_string("doing game\n");
		_delay_ms(1000);
	}
}

int main(void)
{
	init_all();
	input = 0;
	while (1)
	{
		if (playing_game == 1)
		{
			do_level();
			// chk_input();
		}
		else
		{
			tx_string("Press PG3 to Start!");
			while (1)
			{
				if (PING && PG3)
					break ;
			}
		}
	}
}
