/*=====================================================================
//	��������:	  Master.Uv2
//	����������?�����ƶ�������Ӧ�ó���ͷ�ļ�		
//  IDE ������  Keil uVision5.1
//  ����ļ�:	  main.c,include.h
//  Ӳ    ��:   STM32F103ZET6-LQFP144 ����Ƶ��:72MHZ
//  Ӳ����Դ: 
//  ά����¼:	  2015-08-20	v1.0
======================================================================*/
#ifndef	__INCLUDES_H
#define	__INCLUDES_H	
#include "stdio.h"
#include "sys.h"
#include "irq.h"
#include "delay.h"
#include "usart.h"
#include "motor.h"
#include "ADC.h"
#include "dma.h"
#include "sensor.h"
//#include "Remote.h"
/*------------����ģʽ-----------*/
#define MODE_STANDBY      1//����ģʽ
#define MODE_REMOTE       2//ң��ģʽ
#define MODE_ULTRASONIC   3//����������ģʽ
#define MODE_CAMERA       4//�ƶ��������ģʽ
#define MODE_STOP         5//ֹͣ
#define MODE_FORWARD      6//ǰ��
#define MODE_TURNLEFT     7//����
#define MODE_TURNRIGHT    8//��ת
#define MODE_BACKWARD     9//����
#define MODE_OBJECTLOST   10//Ŀ�궪ʧ
#define MODE_ACCELERATE   11//����
#define MODE_DECELERATE   12//����
#define MODE_WELCOMDE     13//��ӭ����ϵͳ
#define MODE_GO           14//Let's go
#define MODE_WRONGCMD     15//�������
#define MODE_GOoDBYE      16//Good Bye
/*------------�������ٶȵ���-----*/
#define  SPEED_LEVEL1     0
#define  SPEED_LEVEL2     1000
#define  SPEED_LEVEL3     5000
#define  SPEED_LEVEL4     10000
#define  SPEED_LEVEL5     20000
#define  SPEED_LEVEL6     30000
#define  SPEED_LEVEL7     40000
#define  SPEED_LEVEL8     45000
#define  SPEED_LEVEL9     50000
#define  SPEED_LEVEL10    55000
#define  SPEED_LEVEL11    59999
/*-------------------------------*/
u8  Motor_L;
u8  Motor_R;
u16 MotorL_Speed;
u16 MotorR_Speed;
u8  g_Flag;
u8  Sys_Status;
/*-------------------------------------------------------------------------------------------*/
const unsigned char CMD_AllLoop[8]       ={0x7e,0xff,0x06,0x11,0x00,0x00,0x01,0xef};//ȫ��ѭ��
const unsigned char CMD_Last[8]          ={0x7e,0xff,0x06,0x02,0x00,0x00,0x00,0xef};//��һ��
const unsigned char CMD_Next[8]          ={0x7e,0xff,0x06,0x01,0x00,0x00,0x00,0xef};//������һ��
const unsigned char CMD_Play[8]          ={0x7e,0xff,0x06,0x0d,0x00,0x00,0x01,0xef};//����
unsigned       char CMD_Stop[8]          ={0x7e,0xff,0x06,0x0e,0x00,0x00,0x00,0xef};//ֹͣ����
unsigned       char CMD_Volume[8]        ={0x7e,0xff,0x06,0x06,0x00,0x00,0x15,0xef};//��������
unsigned       char CMD_SELECT_MUSIC[8]  ={0X7e,0Xff,0X06,0X03,0X00,0X00,0X01,0xef};//����ָ�����ļ�?
unsigned       char CMD_MUSIC_LOOP[8]    ={0X7e,0Xff,0X06,0X17,0X00,0X00,0X01,0xef};//�ļ���ȫ��ѭ��
unsigned       char CMD_SIGNLE_LOOP[8]   ={0X7e,0Xff,0X06,0X08,0X00,0X00,0X01,0xef};//����ѭ��
/*--------------------------------------------------------------------------------------------*/
//extern Struct_Remote Remote_Struct;//������ң�ؽṹ�����
extern Struct_USART  USART1_Struct;//����1�ṹ�����
extern Struct_USART  USART3_Struct;//����3�ṹ�����
extern Struct_USART  UART4_Struct; //����4�ṹ�����
extern uint16_t ADCConvertedValue[3];//ADת��ֵ
//extern uint8_t ADC_FLAG;
#endif
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
