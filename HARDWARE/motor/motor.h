/*=====================================================================
//	功能描述：  马达驱动头文件
//  IDE 环境：  Keil uVision5.1
//  组成文件:	  Motor.c,Motor.h
//  硬    件:   TIME4(CH1-CH4)TIME8(CH1-CH4)
//  硬件资源:   PWM
//  维护记录:	  2015-09-20	v1.0
======================================================================*/
#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"
/*----------PWM电机驱动频率宏定义--------*/
#define FREQ_1KHZ     59999 //PWM频率=72000/(59999+1)=1.2Khz
/*------------电机运动状态宏定义---------*/
#define STOP          0 //马达运行状态->停止
#define FORWARD       1 //马达运行状态->前进?
#define BACKWARD      2 //马达运行状态->后退
/*-----------左边马达驱动端口------------*/
#define IN1 PEout(3)	// PE3->左前电机+
#define IN2 PEout(2)	// PE2->左前电机-

#define IN3 PEout(5)	// PE5->左后电机+
#define IN4 PEout(4)	// PE4->左后电机-
/*-----------右边马达驱动端口------------*/
#define IN5 PBout(5)	// PB5->右前电机+
#define IN6 PBout(4)	// PB3->右前电机-

#define IN7 PBout(3)	// PB3 ->右后电机+
#define IN8 PGout(15)	// PG15->右后电机-
/*-------------------------------------*/
#define LED3 PEout(13)	// PE13
#define LED2 PEout(14)	// PE14
/*------------------------------------*/
//#define MOTORL_FORWARD  {IN1=0;IN2=1;IN3=0;IN4=1;}//左边马达正转
//#define MOTORL_BACKWARD {IN1=1;IN2=0;IN3=1;IN4=0;}//左边马达反转
//#define MOTORL_STOP     {IN1=1;IN2=1;IN3=1;IN4=1;}//左边马达停止

//#define MOTORR_FORWARD  {IN5=1;IN6=0;IN7=1;IN8=0;}//右边马达正转
//#define MOTORR_BACKWARD {IN5=0;IN6=1;IN7=0;IN8=1;}//右边马达反转
//#define MOTORR_STOP     {IN5=1;IN6=1;IN7=1;IN8=1;}//右边马达停止

#define MOTORL_FORWARD  {IN1=0;IN2=1;}//左边马达正转
#define MOTORL_BACKWARD {IN1=1;IN2=0;}//左边马达反转
#define MOTORL_STOP     {IN1=1;IN2=1;}//左边马达停止

#define MOTORR_FORWARD  {IN3=0;IN4=1;}//右边马达正转
#define MOTORR_BACKWARD {IN3=1;IN4=0;}//右边马达反转
#define MOTORR_STOP     {IN3=1;IN4=1;}//右边马达停止

void DriverIO_Init(void);//马达驱动端口初始化
void TIM4_PWM_Init(u16 arr,u16 psc);//PWM调速初始化（电机）
void TIM8_PWM_Init(u16 arr,u16 psc);//PWM调速初始化（舵机）
void servo_Control (u8 servo, u16 PWM);//舵机控制
void Motor_Control(u8 Motor_L, u8 Motor_R, u16 PWM_L, u16 PWM_R);//马达运动状态控制
void Speed_Control(u16 PWM_L, u16 PWM_R);
#endif
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
