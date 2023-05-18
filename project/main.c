#include "USART.h"
#include "SEG_MODULE.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void    init_map(char **map);
void	print_map(char **map);

volatile unsigned int cnt;
volatile unsigned int timer;
volatile unsigned char game_over = 1;
volatile unsigned char player[11];
volatile unsigned char map[23][11];
volatile unsigned int score;
volatile unsigned int player_pos;
volatile unsigned int stop;

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
	if (stop)
		stop = 0;
	else
		stop = 1;
}

ISR(INT5_vect)
{
	for (int i = 0; i < 10; i++)
	{
		if (player[i] == 'O')
		{
			if (i - 1 >= 0)
			{
				player[i] = ' ';
				player[i - 1] = 'O';
				player_pos--;
			}
			break ;
		}
	}
}

ISR(INT7_vect)
{
	for (int i = 0; i < 10; i++)
	{
		if (player[i] == 'O')
		{
			if (i + 1 < 10)
			{
				player[i] = ' ';
				player[i + 1] = 'O';
				player_pos++;
			}
			break ;
		}
	}
}

ISR(INT6_vect)
{
	for (int n = 22; n >= 0; n--)
	{
		if (map[n][player_pos] == 'x')
		{
			map[n][player_pos] = ' ';
			score++;
			break ;
		}
	}
}

int main(void)
{
	player =  = "    O    \n";
	for(int i = 0; i < 23; i++)
		map[i++] = "         \n";
	init_all();
	stop = 0;
	score = 0;
	player_pos = 5;
	while (1)
	{
		if (stop == 1)
			continue ;
		if (game_over == 1)
		{
			tx_string("GAME OVER\n");
			tx_string("GAME OVER\n");
			tx_string("SCORE : ");
			tx_string("GAME OVER\n");
			tx_string("GAME OVER\n");
			tx_int(score);
			tx_string("\n");
			_delay_ms(1000);
			game_over = 0;
			player = = "    O    \n";
			for (int i = 0; i < 23; i++)
				map[i++] = "         \n";
			score = 0;
		}
		else
		{
			int x_pos = rand() % 10;
			if (map[0][x_pos] != 'x')
				map[0][x_pos] = 'x';
			for(int i = 0; i < 23; i++)
				tx_string(map[i++]);
			tx_string(player);
			for (int i = 0; i < 23; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map[i][j] == 'x')
					{
						if (i == 22)
							game_over = 1;
						else
						{
							map[i][j] = ' ';
							map[i + 1][j] = 'x';
						}
					}
				}
			}
		}
	}
}
