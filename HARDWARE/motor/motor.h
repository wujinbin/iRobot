/*=====================================================================
//	����������  �������ͷ�ļ�
//  IDE ������  Keil uVision5.1
//  ����ļ�:	  Motor.c,Motor.h
//  Ӳ    ��:   TIME4(CH1-CH4)TIME8(CH1-CH4)
//  Ӳ����Դ:   PWM
//  ά����¼:	  2015-09-20	v1.0
======================================================================*/
#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"
/*----------PWM�������Ƶ�ʺ궨��--------*/
#define FREQ_1KHZ     59999 //PWMƵ��=72000/(59999+1)=1.2Khz
/*------------����˶�״̬�궨��---------*/
#define STOP          0 //�������״̬->ֹͣ
#define FORWARD       1 //�������״̬->ǰ��?
#define BACKWARD      2 //�������״̬->����
/*-----------�����������˿�------------*/
#define IN1 PEout(3)	// PE3->��ǰ���+
#define IN2 PEout(2)	// PE2->��ǰ���-

#define IN3 PEout(5)	// PE5->�����+
#define IN4 PEout(4)	// PE4->�����-
/*-----------�ұ���������˿�------------*/
#define IN5 PBout(5)	// PB5->��ǰ���+
#define IN6 PBout(4)	// PB3->��ǰ���-

#define IN7 PBout(3)	// PB3 ->�Һ���+
#define IN8 PGout(15)	// PG15->�Һ���-
/*-------------------------------------*/
#define LED3 PEout(13)	// PE13
#define LED2 PEout(14)	// PE14
/*------------------------------------*/
//#define MOTORL_FORWARD  {IN1=0;IN2=1;IN3=0;IN4=1;}//��������ת
//#define MOTORL_BACKWARD {IN1=1;IN2=0;IN3=1;IN4=0;}//�����ﷴת
//#define MOTORL_STOP     {IN1=1;IN2=1;IN3=1;IN4=1;}//������ֹͣ

//#define MOTORR_FORWARD  {IN5=1;IN6=0;IN7=1;IN8=0;}//�ұ������ת
//#define MOTORR_BACKWARD {IN5=0;IN6=1;IN7=0;IN8=1;}//�ұ���ﷴת
//#define MOTORR_STOP     {IN5=1;IN6=1;IN7=1;IN8=1;}//�ұ����ֹͣ

#define MOTORL_FORWARD  {IN1=0;IN2=1;}//��������ת
#define MOTORL_BACKWARD {IN1=1;IN2=0;}//�����ﷴת
#define MOTORL_STOP     {IN1=1;IN2=1;}//������ֹͣ

#define MOTORR_FORWARD  {IN3=0;IN4=1;}//�ұ������ת
#define MOTORR_BACKWARD {IN3=1;IN4=0;}//�ұ���ﷴת
#define MOTORR_STOP     {IN3=1;IN4=1;}//�ұ����ֹͣ

void DriverIO_Init(void);//��������˿ڳ�ʼ��
void TIM4_PWM_Init(u16 arr,u16 psc);//PWM���ٳ�ʼ���������
void TIM8_PWM_Init(u16 arr,u16 psc);//PWM���ٳ�ʼ���������
void servo_Control (u8 servo, u16 PWM);//�������
void Motor_Control(u8 Motor_L, u8 Motor_R, u16 PWM_L, u16 PWM_R);//����˶�״̬����
void Speed_Control(u16 PWM_L, u16 PWM_R);
#endif
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
