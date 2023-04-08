#include "USART.h"
#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	unsigned char *string = "Hello World!\n";
	usart_init(BAUD_9600);
	while (1)
	{
		usart_send_string(string);
		_delay_ms(1000);
	}
}