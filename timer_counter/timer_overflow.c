#include "SEG_MODULE.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int cnt, ovf_num;

ISR(TIMER0_COMP_vect)
{
	cnt++;
	if (cnt == 250)
	{
		ovf_num++;
		cnt = 0;
	}
}

int main()
{
	DDRG = 1 << PG0;

	TCNT0 = 0x00;
	TCCR0 = 1 << WGM01 | 1 << CS02 | 1 << CS01;
	TIMSK = 1 << OCIE0;
	OCR0 = 249;
	seg_init();
	
	cnt = 0;
	sei();
	while (1)
		seg_disp(ovf_num);
	return (0);
}
