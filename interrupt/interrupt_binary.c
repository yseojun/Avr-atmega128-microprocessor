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

volatile char	cnt_bit = 0;

ISR(INT6_vect)
{
	cnt_bit++;
}

ISR(INT7_vect)
{
	cnt_bit--;
}

int main(void)
{
	init_devices();
	DDRE = 0x00;
	PORTG = 0x00;
	DDRG = 0x03;
	int	led[4] = {0x00, 0x01, 0x02, 0x03};
	while (1)
		PORTG = led[cnt_bit];
	return (0);
}
