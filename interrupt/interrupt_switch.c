#include <avr/io.h>
#include <avr/interrupt.h>

volatile char	start = 0;

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
	start--;
}

ISR(INT6_vect)
{
	start++;
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
		if (start == 10) start = 0;
		PORTA = SEG_CODE(start);
		PORTC = DISP_SEL(1);
		_delay_ms(500);
		PORTC = DISP_SEL(0);
	}
	return 0;
}
