#include "USART.h"
#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	unsigned char *string = "Hello World!\n";
	unsigned char key_come = 0;
	usart_init(BAUD_9600);
	while (1)
	{
		tx_string("--------------------\n");
		tx_string("USART Test\n");
		tx_string("--------------------\n");
		tx_string("push keys (1-4)\n")
		while (1)
		{
			key_come = rx_data();
			switch(key_come)
			{
				case ASCII_1:
					tx_string("switch 1 pressed\n");
					break;
				case ASCII_2:
					tx_string("switch 2 pressed\n");
					break;
				case ASCII_3:
					tx_string("switch 3 pressed\n");
					break;
				case ASCII_4:
					tx_string("switch 4 pressed\n");
					break;
				default:
					tx_string("invalid key\n")
					break;
			}
		}
	}	
}