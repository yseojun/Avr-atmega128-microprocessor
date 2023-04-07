#ifndef USART_H

#define USART_H

#define BAUD_4800	0xCE
#define BAUD_9600	0x67
#define BAUD_14400	0x44
#define BAUD_19200	0x33
#define BAUD_38400	0x19
#define BAUD_57600	0x10
#define BAUD_115200	0x07



void usart_init(unsigned int baud_rate);
void tx_data(unsigned char data);
char rx_data(void);
void tx_string(unsigned char *string);

#endif
