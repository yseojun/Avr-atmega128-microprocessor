#include <avr/delay.h>
#include <avr/io.h>

void    count_switch(void)
{
    int num1, num10;

    int i = 0;
    while (1)
    {
		if (PING & (1 << PG3))
		{
			i++;
			_delay_ms(50);
		}
		else if (PING & (1 << PG2))
        {
			i--;
			_delay_ms(50);
		}
		if (i < 0) i = 0;
        num10 = i / 10;
        num1 = i % 10;
        int j = 0;
        while (j < 10)
        {
            PORTC = DISP_SEL(1);
            PORTA = SEG_CODE(num1);
            _delay_ms(10);
            PORTC = DISP_SEL(0);
            PORTC = DISP_SEL(2);
            PORTA = SEG_CODE(num10);
            _delay_ms(10);
            PORTC = DISP_SEL(0);
            j++;
        }
    }
}
