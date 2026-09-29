#include "adc.h"



adc_init(){
    //ENCIENDO CLOCK
    RCC-> APB2ENR |= (RCC_APB2ENR_ADC1EN);
    RCC -> APB2ENR |= (RCC_APB2ENR_IOPAEN);
    RCC -> APB2ENR |= (RCC_APB2ENR_IOPBEN);
    //encender y calibrar  adc
    //encender → esperar estabilización → reset de calibración → calibrar → esperar fin.
    ADC1 -> CR2 |= ADC_CR2_ADON; //ENCENDER EL ADC
        for( int i= 0; i<1000; i++); //ESPERAR ESTABILIZACIÓN
    ADC1 -> CR2 |= ADC_CR2_RSTCAL; //RESET
        while(ADC1->CR2&ADC_CR2_RSTCAL);
    ADC1 -> CR2 |= ADC_CR2_CAL; //CALIBRO
        while(ADC1->CR2&ADC_CR2_CAL);
}

adc_read(unsigned int canal){
    //CNF = 00 y MODE = 00.
    if(canal <  8){
        GPIOA -> CRL &=~ (0xF << canal*4); //PA0-PA7
    }else{
        GPIOB -> CRL &=~ (0xF << 8*4); //PB0
        GPIOB -> CRL &=~ (0xF << 9*4); //PB1
}
    ADC1 -> SQR3 |= canal ; //ESCRIBO NUM DE CANAL EN CH1
    ADC1 -> SMPR2  |= (0b111 << canal*3) ; //SET TIEMPO MUESTREO
    ADC1 -> CR2 |= ADC_CR2_SWSTART; //INICIAR CONVERSION
        while (~(ADC1 -> SR & ADC_SR_EOC)); //TERMINO LA CONVERSION?
    return ADC1 -> DR;//VALOR DIGITAL FINAL
}