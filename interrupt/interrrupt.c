#include <avr/io.h>
#include <avr/interrupt.h>

void	init_devices(void)
{
	cli();
	MCUCR = 0x00;
	EICRA = 0x00;
	EICRB = 0xF0;
	EIMSK = 1 << INT7 | 1 << INT6;
	sei();
}

ISR(INT6_vect)
{
	PORTG = 1 << PG0;
}

ISR(INT7_vect)
{
	PORTG = 1 << PG1;
}

int main(void)
{
	init_devices();
	DDRE = 0x00;
	PORTG = 0x00;
	DDRG = 0x03;
	while (1)
	{
		
	}
	return (0);
}