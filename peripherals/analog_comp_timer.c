#include <avr/io.h>
#include <avr/interrupt.h>
#include "SEG_MODULE.h"
#include <avr/delay.h>

volatile unsigned int cnt, ovf_num;

void	reg_init(void)
{
	DDRG = (1 << PG1) | (1 << PG0);
	DDRE = 0x00;
	PORTG = 0x00;
	ACSR = 1 << ACBG | 1 << ACIE;
	SFIOR = 0x00;
}

volatile unsigned int cout;

ISR(ANALOG_COMP_vect)
{
	cout = ACSR & (1 << ACO);
	if (cout) TCCR0 = 1 << WGM01 | 1 << CS02 | 1 << CS01;
	else TCCR0 = 0;
}

ISR(TIMER0_COMP_vect)
{
	cnt++;
	if (cnt == 250)
	{
		ovf_num++;
		cnt = 0;
	}
}

int	main(void)
{
	reg_init();
	seg_init();

	TCNT0 = 0x00;
	OCR0 = 249;
	TIMSK = 1 << OCIE0;
	sei();

	while(1)
		seg_disp(ovf_num);
        
	return (0);
}
