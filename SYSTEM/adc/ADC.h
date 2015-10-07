#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"

void adc_Init(void);
uint16_t Get_Adc(uint8_t);
uint16_t Get_Adc_Average(uint8_t,uint8_t);
//uint16_t Get_Average(uint8_t);

#endif 
