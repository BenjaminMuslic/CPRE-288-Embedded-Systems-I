

#ifndef ADC_H_
#define ADC_H_

#include <inc/tm4c123gh6pm.h>

// ADC initialization
void adc_init(void);

// ADC read to take samples
uint16_t adc_read(void);

#endif /* ADC_H_ */
