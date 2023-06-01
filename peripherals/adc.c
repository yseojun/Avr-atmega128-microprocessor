#include <avr/io.h>
#include <avr/interrupt.h>
#include "SEG_MODULE.h"

void	reg_init(void)
{
	ADMUX = 1 << REFS0;
	// AVCC is used as VREF, Singled-ended input = ADC0
	ADCSRA = 1 << ADEN | 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0;
	// ADC enable, f_ADC = 16MHz/ 128
}

int	main(void)
{
	reg_init();
	seg_init();
	int	adc_out;
	float avolt, rval, rval_i;
	while(1)
	{
		ADCSRA |= (1 << ADSC);
		while((ADCSRA & (1 << ADIF)) == 0);
		adc_out = ADCL + (ADCH << 8);

		avolt = adc_out * 5.0 + 1023.0;
		rval = 10 * avolt / 5;
		rval_i = rval * 100;
		seg_disp(rval_i);
	}
	return (0);
}
