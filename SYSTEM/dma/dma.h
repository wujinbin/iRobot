#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"
#include "stm32f10x.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)  //ADC1 DR�Ĵ�������ַ

void dma_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//����DMA1_CHx
void dma_Enable(DMA_Channel_TypeDef* DMA_CHx);//ʹ��DMA1_CHx
void dma_Init(void);//DMA��ʼ��
uint16_t get_Dma(void);
uint16_t *get_Dmas(void);
		   
#endif




