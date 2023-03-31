#include <avr/io.h>
#include <avr/interrupt.h>

void	init_devices(void)
{
	cli();
	MCUCR = 0x00;
	EICRA = 0x00;
	EICRB = 0xC0;
	EIMSK = 1 << INT7;
	sei();
	PORTA = 0x00;
	DDRA = 0xFF;
	PORTC = 0x0F;
	DDRC = 0x0F;
}

ISR(INT7_vect)
{
	count = 1;
}

int main(void)
{
	init_devices();
	PORTG = 0x00;
	DDRG = 1 << PG1 | 1 << PG0;
	int	start = 0;
	int	LED_cnt = 0;
	while (1)
	{
		if (PING && (1 << PG3)) start = 1;
		while (start)
		{

		}
		if (LED_cnt > 15) LED_cnt = 0;
	}
}