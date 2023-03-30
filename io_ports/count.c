#include <avr/delay.h>
#include <avr/io.h>

char SEG_CODE(char num);
char DISP_SEL(char num);

void    count10(int count)
{
    int num1, num10;
    int i;
    for (i = 0; i <= count + 1; i++)
    {
        if (i > count) i = count;
        num10 = i / 10;
        num1 = i % 10;
        for (int j = 0; j < 50; j++)
        {
            PORTC = DISP_SEL(1);
            PORTA = SEG_CODE(num1);
            _delay_ms(10);
            PORTC = DISP_SEL(0);
            PORTC = DISP_SEL(2);
            PORTA = SEG_CODE(num10);
            _delay_ms(10);
            PORTC = DISP_SEL(0);
        }
    }
}

void    count10_while(int count)
{
    int num1, num10;

    int i = 0;
    while (i < count + 1)
    {
        num10 = i / 10;
        num1 = i % 10;
        int j = 0;
        while (j < 50)
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
        i++;
    }
}
