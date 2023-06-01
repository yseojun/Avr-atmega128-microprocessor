#include "SEG_MODULE.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int cnt, ovf_num;

ISR(TIMER2_COMP_vect)
{
	cnt++;
	if (cnt == 250)
	{
		ovf_num++;
		PORTG ^= 1 << PG0;
		cnt = 0;
	}
}

int main()
{
	DDRG = 1 << PG0;

	TCNT2 = 0x00;
	TCCR2 = 1 << WGM21 | 1 << CS22;
	OCR2 = 249;
	TIMSK = 1 << OCIE2;
	seg_init();
	
	ovf_num = 0;
	cnt = 0;
	sei();
	while (1)
	{
		seg_disp(ovf_num);
	}
	return (0);
}
