#include <avr/io.h>
#include <avr/interrupt.h>
#include "SEG_MODULE.h"

void	reg_init(void)
{
	ADMUX = 1 << REFS0;
	ADCSRA = 1 << ADEN | 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0;
}

volatile int adc_out;
volatile float avolt, rval, rval_i;

ISR(ADC_vect)
{
	adc_out = ADCL + (ADCH << 8);
	avolt = adc_out * 5.0 / 1023.0;
	rval = 10 * avolt / 5;
	rval_i = rval * 100;
}

int	main(void)
{
	reg_init();
	seg_init();
	
	while(1)
	{
		ADCSRA |= (1 << ADSC);
		while((ADCSRA & (1 << ADIF) == 0));
		
		seg_disp(rval_i);
	}
	return (0);
}
