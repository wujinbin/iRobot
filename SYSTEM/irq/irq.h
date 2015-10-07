/*=====================================================================
//	工程名称:	  Master.Uv2
//	功能描述:  管道机器人控制		
//  IDE 环境:  Keil uVision5.1
//  组成文件:	  main.c,include.h
//  硬    件:   STM32F103ZET6-LQFP144 晶振频率:72MHZ
//  硬件资源: 
//  维护记录:	  2015-09-20	v1.0
======================================================================*/
#ifndef __IRQ_H
#define __IRQ_H	 
#include "sys.h"
#include "Motor.h"
#include "usart.h"
#include "sensor.h"
//#include "Remote.h"

void EXT_IRQ_Init(void);//外部中断初始化
void TIM_IRQ_Init(void);//初始化所有用到的中断定时器
void TIM2_IRQ_Init(u16 arr,u16 psc);//定时器2中断初始化
void TIM6_IRQ_Init(u16 arr,u16 psc);//定时器6中断初始化
void TIM7_IRQ_Init(u16 arr,u16 psc);//定时器7中断初始化
#endif

