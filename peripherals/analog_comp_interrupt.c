#include <avr/io.h>
#include <avr/interrupt.h>

void	reg_init(void)
{
	DDRG = (1 << PG1) | (1 << PG0);
	DDRE = 0x00;
	PORTG = 0x00;
	ACSR = 1 << ACBG | 1 << ACIE; // ACSR ->BGR applied (+)input ,ACIE -> interrupt
	SFIOR = 0x00;
	sei();
}

volatile unsigned int cout;

ISR(ANALOG_COMP_vect)
{
	cout = ACSR & (1 << ACO);
	if (cout) PORTG = 1 << PG0;
	else PORTG = 1 << PG1;
}

int	main(void)
{
	reg_init();

	unsigned int	cout;

	while(1);
	return (0);
}
