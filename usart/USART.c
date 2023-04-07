#include <avr/io.h>

#include "USART.h"

#define	CR	0x0D	//Carriage return, ASCII = 13 (0x0D) : Go to the left of the line
#define	LF	0x0A	//Line feed, ASCII = 10 (0x0A) : Go the next line

void usart_init(unsigned int baud_rate)
{
	UCSR1A = 0x00; // USART initialization
	UCSR1B = 0x98; // rx, tx enable + Rx complete Interrupt enable
	UCSR1C = 0x06; // No parity, 1 stop bit, 8 data bit frame
	UBRR1H = 0x00;  // USART mode :  Asynchronous (without XCLK)
	UBRR1L = baud_rate;
}

void tx_data(unsigned char data)
{
	while(!(UCSR1A & 0x20)); // UDRE1 = 1 when TX buffer is empty
	UDR1 = data;
}

char rx_data(void)
{
	while(!(UCSR1A & 0x80)); // RXC1 = 1 when there are unread data in the RX buffer
	return UDR1;
}

void tx_string(unsigned char *string)
{
	while(*string != '\0')
	{
		if(*string == '\n')
		{
			tx_data(CR);
			tx_data(LF);  // Move to the left and down a line
		}
		else
		{
			tx_data(*string);
		}
		string++;
	}
}	
