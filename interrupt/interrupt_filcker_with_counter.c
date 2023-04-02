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

volatile char	count = 0;
volatile char	start = 0;

ISR(INT6_vect)
{
	start = 1;
	count++;
}

ISR(INT7_vect)
{
	start = 1;
	count--;
	if (count < 0) count = 0;
}

int main(void)
{
	init_devices();
	DDRE = 0x00;
	PORTA = 0x00;
	DDRA = 0xFF;
	PORTC = 0x0F;
	DDRC = 0x0F;
	PORTG = 0x00;
	DDRG = 0x03;
	while (1)
	{
		if (start == 1)
		{
			int	num1, num10;
			num1 = count % 10;
			num10 = count / 10;
			PORTA = SEG_CODE(num1);
			PORTC = DISP_SEL(1);
			_delay_ms(100);
			PORTA = SEG_CODE(num10);
			PORTC = DISP_SEL(2);
			_delay_ms(500);
			start = 0;
		}
		PORTG = 0x03;
		_delay_ms(100);
		PORTG = 0x00;
		_delay_ms(100);		
	}
	return (0);
}
