#include <avr/io.h>

void	reg_init(void)
{
	DDRG = (1 << PG1) | (1 << PG0);
	DDRE = 0x00;
	PORTG = 0x00;
	ACSR = 0x00;
	SFIOR = 0x00;
}

void	main(void)
{
	reg_init();

	unsigned int	cout;

	while(1)
	{
		cout = ACSR & (1 << ACO);
		if (cout) PORTG = 1 << PG0;
		else PORTG = 1 << PG1;
	}
}
