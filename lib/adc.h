#include "stm32f103xb.h"
#ifndef adc.h
#define adc.h
void adc_init();
int adc_read(unsigned int canal);

#endif