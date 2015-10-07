/*=====================================================================
//	��������:	  Master.Uv2
//	��������:  �ܵ������˿���		
//  IDE ����:  Keil uVision5.1
//  ����ļ�:	  main.c,include.h
//  Ӳ    ��:   STM32F103ZET6-LQFP144 ����Ƶ��:72MHZ
//  Ӳ����Դ: 
//  ά����¼:	  2015-09-20	v1.0
======================================================================*/
#ifndef __IRQ_H
#define __IRQ_H	 
#include "sys.h"
#include "Motor.h"
#include "usart.h"
#include "sensor.h"
//#include "Remote.h"

void EXT_IRQ_Init(void);//�ⲿ�жϳ�ʼ��
void TIM_IRQ_Init(void);//��ʼ�������õ����ж϶�ʱ��
void TIM2_IRQ_Init(u16 arr,u16 psc);//��ʱ��2�жϳ�ʼ��
void TIM6_IRQ_Init(u16 arr,u16 psc);//��ʱ��6�жϳ�ʼ��
void TIM7_IRQ_Init(u16 arr,u16 psc);//��ʱ��7�жϳ�ʼ��
#endif

