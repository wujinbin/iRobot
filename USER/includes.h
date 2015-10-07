/*=====================================================================
//	工程名称:	  Master.Uv2
//	功能描述：?室内移动机器人应用程序头文件		
//  IDE 环境：  Keil uVision5.1
//  组成文件:	  main.c,include.h
//  硬    件:   STM32F103ZET6-LQFP144 晶振频率:72MHZ
//  硬件资源: 
//  维护记录:	  2015-08-20	v1.0
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
/*------------运行模式-----------*/
#define MODE_STANDBY      1//待机模式
#define MODE_REMOTE       2//遥控模式
#define MODE_ULTRASONIC   3//超声波避障模式
#define MODE_CAMERA       4//移动物体跟踪模式
#define MODE_STOP         5//停止
#define MODE_FORWARD      6//前进
#define MODE_TURNLEFT     7//后退
#define MODE_TURNRIGHT    8//右转
#define MODE_BACKWARD     9//后退
#define MODE_OBJECTLOST   10//目标丢失
#define MODE_ACCELERATE   11//加速
#define MODE_DECELERATE   12//减速
#define MODE_WELCOMDE     13//欢迎进入系统
#define MODE_GO           14//Let's go
#define MODE_WRONGCMD     15//错误操作
#define MODE_GOoDBYE      16//Good Bye
/*------------机器人速度调节-----*/
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
const unsigned char CMD_AllLoop[8]       ={0x7e,0xff,0x06,0x11,0x00,0x00,0x01,0xef};//全部循环
const unsigned char CMD_Last[8]          ={0x7e,0xff,0x06,0x02,0x00,0x00,0x00,0xef};//上一曲
const unsigned char CMD_Next[8]          ={0x7e,0xff,0x06,0x01,0x00,0x00,0x00,0xef};//播放下一曲
const unsigned char CMD_Play[8]          ={0x7e,0xff,0x06,0x0d,0x00,0x00,0x01,0xef};//播放
unsigned       char CMD_Stop[8]          ={0x7e,0xff,0x06,0x0e,0x00,0x00,0x00,0xef};//停止播放
unsigned       char CMD_Volume[8]        ={0x7e,0xff,0x06,0x06,0x00,0x00,0x15,0xef};//音量调节
unsigned       char CMD_SELECT_MUSIC[8]  ={0X7e,0Xff,0X06,0X03,0X00,0X00,0X01,0xef};//播放指定的文件?
unsigned       char CMD_MUSIC_LOOP[8]    ={0X7e,0Xff,0X06,0X17,0X00,0X00,0X01,0xef};//文件夹全部循环
unsigned       char CMD_SIGNLE_LOOP[8]   ={0X7e,0Xff,0X06,0X08,0X00,0X00,0X01,0xef};//单曲循环
/*--------------------------------------------------------------------------------------------*/
//extern Struct_Remote Remote_Struct;//红外线遥控结构体变量
extern Struct_USART  USART1_Struct;//串口1结构体变量
extern Struct_USART  USART3_Struct;//串口3结构体变量
extern Struct_USART  UART4_Struct; //串口4结构体变量
extern uint16_t ADCConvertedValue[3];//AD转换值
//extern uint8_t ADC_FLAG;
#endif
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
