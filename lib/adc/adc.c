#include "stm32f103xb.h"
#include "adc.h"

void adc_init(){
    RCC-> APB2ENR |= (RCC_APB2ENR_ADC1EN);
    RCC -> APB2ENR |= (RCC_APB2ENR_IOPAEN);
    RCC -> APB2ENR |= (RCC_APB2ENR_IOPBEN);

    ADC1 -> CR2 |= ADC_CR2_ADON; 

    for( int i= 0; i<1000; i++);

    ADC1 -> CR2 |= ADC_CR2_RSTCAL;

    while(ADC1->CR2&ADC_CR2_RSTCAL);

    ADC1 -> CR2 |= ADC_CR2_CAL; 

    while(ADC1->CR2&ADC_CR2_CAL);

    ADC1->CR2 |= ADC_CR2_EXTSEL;   
    ADC1->CR2 |= ADC_CR2_EXTTRIG;
}

int adc_read(unsigned int canal){
    
    if(canal <  8){
        GPIOA -> CRL &=~ (0xF << canal*4); 
    }else{
    GPIOB->CRL&=~(0xF<<(canal%2)*4); 
         }

    ADC1 -> SQR3 |= canal ; 
    ADC1 -> SMPR2  |= (0b111 << canal*3) ; 
    ADC1 -> CR2 |= ADC_CR2_SWSTART; 

    while (!(ADC1 -> SR & ADC_SR_EOC));

    return ADC1 -> DR;
} 
