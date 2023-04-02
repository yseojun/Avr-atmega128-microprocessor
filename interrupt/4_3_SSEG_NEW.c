#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>

void init()
{
	PORTA = 0x00;  // 7-Segment Display uses PA0~PA7 for a~g and dot1 
	DDRA = 0xFF;   // PA0~PA7 are assigned to output pins
	PORTC = 0x0F;  // PC0~PC3 initially output high
	DDRC = 0x0F;   // PC0~PC3 are assigned to output pins
    PORTG = 0x00;  
    DDRG = (1<<PG1) | (1<<PG0); // for LED driving
}

char SEG_CODE(char num)
{
	char count[20] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 
	                  0x6D, 0x7D, 0x27, 0x7F, 0x6F,
					  0x77, 0x7C, 0x39, 0x5E, 0x79,
					  0x71,
					  0xED,0xF8,0xBF,0xF3 }; //S.,T.,O.,P. (16,17,18,19th)
	return count[num];
}

char DISP_SEL(char num)
{
	char count[5] = {0x0F, 0x07, 0x0B, 0x0D, 0x0E};  // 0x0F = ALL OFF
	return count[num];
}
