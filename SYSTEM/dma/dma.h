#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"
#include "stm32f10x.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)  //ADC1 DR寄存器基地址

void dma_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//配置DMA1_CHx
void dma_Enable(DMA_Channel_TypeDef* DMA_CHx);//使能DMA1_CHx
void dma_Init(void);//DMA初始化
uint16_t get_Dma(void);
uint16_t *get_Dmas(void);
		   
#endif




