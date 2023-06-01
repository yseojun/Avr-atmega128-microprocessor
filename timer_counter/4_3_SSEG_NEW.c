//#define F_CPU 16000000UL
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
