#include <avr/io.h>
#include <avr/delay.h>
#include "SEG_MODULE.h"


void seg_init()
{
	PORTA = 0x00;  // 7-Segment Display uses PA0~PA7 for a~g and dot1 
	DDRA = 0xFF;   // PA0~PA7 are assigned to output pins
	PORTC = 0x0F;  // PC0~PC3 initially output high
	DDRC = 0x0F;   // PC0~PC3 are assigned to output pins
}

char SEG_CODE(char num)
{
	char count[20] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, // 0~4
	                  0x6D, 0x7D, 0x27, 0x7F, 0x6F, // 5~9
					  0x77, 0x7C, 0x39, 0x5E, 0x79, // A~E
					  0x71,							// F
					  0xED,0xF8,0xBF,0xF3 }; //S.,T.,O.,P. (16,17,18,19th)
	return count[num];
}

char DISP_SEL(char num)
{
	char count[5] = {0x0F, 0x07, 0x0B, 0x0D, 0x0E};  // 0x0F = ALL OFF
	return count[num];
}

void seg_disp(int disp_num)
{
	int num1000, num100, num10, num1;
	num1000 = disp_num / 1000;
	num100  = disp_num / 100 % 10; 
	num10   = disp_num / 10 % 10;  // Extract tens digit
	num1    = disp_num % 10;    	
	for(int j=0;j<15;j++)	// Time delay  (4x5ms) x 15 = 300ms	
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
	}
}

void counter(int count)
{
	int num1000, num100, num10, num1;
	int i;
    for(i=0;i<=count+1;i++)
	{  
		if(i > count) i=count; // Stop counting if the count number exceeds the max. number

			num1000 = i / 1000;
			num100  = i / 100 % 10; 
			num10   = i / 10 % 10;  // Extract tens digit
			num1    = i % 10;     	// Extract units digit
	
		for(int j=0;j<1;j++)	// Time delay  (4x5ms) x 15 = 300ms	
			{
				PORTC = DISP_SEL(1);
				PORTA = SEG_CODE(num1);
				_delay_ms(5);
					PORTC = DISP_SEL(0);
				PORTC = DISP_SEL(2);
				PORTA = SEG_CODE(num10);
				_delay_ms(5);
					PORTC = DISP_SEL(0);
				PORTC = DISP_SEL(3);
				PORTA = SEG_CODE(num100);
				_delay_ms(5);
					PORTC = DISP_SEL(0);
				PORTC = DISP_SEL(4);
				PORTA = SEG_CODE(num1000);
				_delay_ms(5);
					PORTC = DISP_SEL(0);			
			}
	}
}
