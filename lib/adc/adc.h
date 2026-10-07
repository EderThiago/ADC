#include "stm32f103xb.h"
#ifndef ADC_H
#define ADC_H


void adc_init();
int adc_read(unsigned int canal);
#endif