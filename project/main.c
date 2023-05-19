#include "USART.h"
#include "SEG_MODULE.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

volatile unsigned int cnt;
volatile unsigned int timer;

volatile unsigned int play_game;
volatile unsigned int level;
volatile unsigned int input[10];
volatile unsigned int expect[10];
volatile unsigned int now_input;

void	init_all()
{
	cli();
	PORTA = 0x00;  // 7-Segment Display uses PA0~PA7 for a~g and dot1 
	DDRA = 0xFF;   // PA0~PA7 are assigned to output pins
	PORTC = 0x0F;  // PC0~PC3 initially output high
	DDRC = 0x0F;   // PC0~PC3 are assigned to output pins

	PORTD = 0;
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
		PORTG ^= 1 << PG0;
		cnt = 0;
		timer++;
	}
}

ISR(INT4_vect)
{
	
}

ISR(INT5_vect)
{
	now_input = 1;
}

ISR(INT6_vect)
{
	now_input = 2;
}

ISR(INT7_vect)
{	
	now_input = 3;
}

void	chk_level()
{
	int	idx = 0;
	while (idx < level)
	{
		if (input[idx] != expect[idx])
		{
			tx_string("Fail\n");
			_delay_ms(1000);
			play_game = 0;
			level = 1;
		}
		idx++;
	}
	tx_string("Level Done!!!\n");
	level++;
	if (level == 10)
	{
		tx_string("You Win!!!\n");
		_delay_ms(1000);
		play_game = 0;
		level = 1;
	}
}

void	do_level()
{
	tx_string("Remember !!\n");
	int	random;
	int idx = 0;
	while (idx < level)
	{
		random = rand() % 3 + 1;
		if (random == 1)
			tx_string("Left!!!\n");
		else if (random == 2)
			tx_string("Up!!\n");
		else if (random == 3)
			tx_string("Right!\n");
		expect[idx] = random;
		idx++;
		_delay_ms(500);
	}
	tx_string("Remember!!\n");
	_delay_ms(1000);
	for (int i = 0; i < 20; i++)
		tx_string("\n");
	tx_string("Start Game!!\n");
	tx_string("Taking input...\n");
	idx = 0;
	while (idx < level)
	{
		now_input = 0;
		while (now_input == 0);
		if (now_input == 1)
			tx_string("Left\n");
		else if (now_input == 2)
			tx_string("Up\n");
		else if (now_input == 3)
			tx_string("Right\n");
		input[idx] = now_input;
		idx++;
	}
	chk_level();
}

int main(void)
{
	init_all();
	usart_init(BAUD_9600);
	play_game = 0;
	level = 1;
	while (1)
	{
		tx_string("In main\n");
		if (play_game == 1)
		{
			if (level == 1)
			{
				tx_string("Left : 5, Up : 6, Right : 7\n");
				tx_string("Remember script, and press in order!\n");
			}
			do_level();
		}
		else
		{
			while (play_game == 0)
			{
				tx_string("Press PG3 to start GAME!\n");
				if (PING & (1 << PG3))
					play_game = 1;
				_delay_ms(1000);
			}
		}
		_delay_ms(100);
	}
}
