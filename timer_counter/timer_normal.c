#include "SEG_MODULE.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int cnt;

ISR(TIMER0_OVF_vect)
{
	cnt++;
	if (cnt == 50)
	{
		PORTG ^= 1 << PG0;
		cnt = 0;
	}
}

int main()
{
	DDRG = 1 << PG0;

	TCNT0 = 0x00;
	TCCR0 = 1 << CS02 | 1 << CS01;
	TIMSK = 1 << TOIE0;
	
	cnt = 0;
	sei();
	while (1);
	return (0);
}
