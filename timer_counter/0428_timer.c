#include "SEG_MODULE.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

volatile unsigned int cnt, ovf_num, cnt2, ovf_num2;

ISR(TIMER0_COMP_vect)
{
	cnt++;
	if (cnt == 250)
	{
		ovf_num++;
		cnt = 0;
	}
}

ISR(TIMER2_COMP_vect)
{
	cnt2++;
	if (cnt2 == 250)
	{
		ovf_num2++;
		cnt2 = 0;
	}
}

void init();

int main()
{
	TCNT0 = 0x00;
	OCR0 = 249;

	TCNT2 = 0x00;
	OCR2 = 249;
	TIMSK = 1 << OCIE0 | 1 << OCIE2;

	init();
	seg_init();
	cnt = 0;	
	ovf_num = 0;
	cnt2 = 0;
	ovf_num2 = 0;
	sei();
	while (1)
	{
		if (PING & (1 << PG3))
			TCCR0 = 1 << WGM01 | 1 << CS02 | 1 << CS01;
		else if (PING & (1 << PG2))
			TCCR2 = 1 << WGM21 | 1 << CS22;
		if (ovf_num >= 3)
			seg_disp(ovf_num);
		if (ovf_num2 >= 5)
		{
			ovf_num = 0;
			ovf_num2 = 0;
			TCCR0 = 0;
			TCCR2 = 0;
			PORTC = DISP_SEL(0);
		}

	}
	return (0);
}
