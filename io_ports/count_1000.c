void    count1000_while(int count)
{
    int num1, num10, num100, num1000;

    int i = 0;
    while (i < count + 1)
    {
        int j = 0;
		if (i > count) i = count;
		num1000 = i / 1000;
		num100 = (i / 100) % 10;
		num10 = (i / 10) % 10;
        num1 = i % 10;
        while (j < 50)
        {
            PORTC = DISP_SEL(1);
            PORTA = SEG_CODE(num1);
			_delay_ms(5);
            PORTC = DISP_SEL(2);
            PORTA = SEG_CODE(num10);
			_delay_ms(5);
            PORTC = DISP_SEL(3);
            PORTA = SEG_CODE(num100);
			_delay_ms(5);
            PORTC = DISP_SEL(4);
            PORTA = SEG_CODE(num1000);
			_delay_ms(5);
            j++;
        }
        i++;
    }
}
