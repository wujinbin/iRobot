/*=====================================================================
//	工程名称:	  iRobot
//	功能描述:  管道机器人控制		
//  IDE 环境:  Keil uVision5.1
//  组成文件:	  main.c,include.h
//  硬    件:   STM32F103ZET6-LQFP144 晶振频率:72MHZ
//  硬件资源: 
//  维护记录:	  2015-09-28	v1.0
======================================================================*/
#include "includes.h"

/*::::::::::::::::::::::::::::::
** 函数名称: Parameter_Init
** 功能描述: 系统变量初始化
** 参数描述：无
** 作  　者: wu
** 日　  期: 2015年09月20日
::::::::::::::::::::::::::::::::*/
void Parameter_Init(void)
{
	Motor_L        = STOP;
	Motor_R        = STOP;
	MotorL_Speed   = SPEED_LEVEL10;
	MotorR_Speed   = SPEED_LEVEL10;
	Sys_Status     = MODE_STANDBY;//待机模式	
	Delay_ms(1000);
	//Motor_Control(FORWARD,FORWARD,30000,30000);
}

/*::::::::::::::::::::::::::::::::::::
** 函数名称: void Sys_Init(void)
** 功能描述: 系统硬件初始化
** 参数描述：无
** 作  　者: wu
** 日　  期: 2015年09月20日
::::::::::::::::::::::::::::::::::::::*/
void Sys_Init(void)
{
	Delay_init();	    	       //延时函数初始化	
	DriverIO_Init();           //马达驱动端口初始化
	adc_Init();					//adc转换模块初始化
	NVIC_Configuration();      //设置中断优先级分组
	Uart_Init();	             //串口初始化
	TIM_IRQ_Init();            //初始化用到的定时器
	EXT_IRQ_Init();            // 初始化外部中断
	TIM4_PWM_Init(FREQ_1KHZ,0);//PWM参数初始(Freq=1.2KHz)
	TIM8_PWM_Init(449,799);//舵机PWM参数初始，单次计数为11us,周期5MS
	//TIM8_PWM_Init(199,7199);//舵机PWM参数初始，单次计数为11us,周期20MS
	Parameter_Init();          //系统变量初始化
} 
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* 函 数 名: Motor
* 功    能: 电机及机械臂状态控制
* 入口参数: 无
* 出口参数: 无
* 说    明: PWM<=59999
* 调用方法: 直接调用
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Motor(void)
{
	//u16 speed;
	if(USART3_Struct.UartReceiveOk_Flag == 0xFF)
	{
		//servo_Control(0, 0);
		USART3_Struct.UartReceiveOk_Flag = 0x00;
		if(USART3_Struct.UartReceive_Buff[2] == 0x00 )//控制驱动电机
		{
			if(USART3_Struct.UartReceive_Buff[3] == 0x00)//控制方向
			{
				if(USART3_Struct.UartReceive_Buff[4] == 0x01)//前进
				{
					Motor_L = Motor_R = FORWARD;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
				else if(USART3_Struct.UartReceive_Buff[4] == 0x02)//停止
				{
					Motor_L = Motor_R = STOP;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
				else if(USART3_Struct.UartReceive_Buff[4] == 0x03)//后退
				{	
					Motor_L = Motor_R = BACKWARD;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
				else if(USART3_Struct.UartReceive_Buff[4] == 0x04)//左转
				{
					Motor_L = BACKWARD;
					Motor_R = FORWARD;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
				else if(USART3_Struct.UartReceive_Buff[4] == 0x05)//右转
				{
					Motor_L = FORWARD;
					Motor_R = BACKWARD;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
			}
			else if(USART3_Struct.UartReceive_Buff[3] == 0x01)//控制速度
			{
				MotorL_Speed = MotorR_Speed = 1000*USART3_Struct.UartReceive_Buff[4];
				Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
			}
		}
		else if(USART3_Struct.UartReceive_Buff[2] == 0x01)//控制机械臂舵机
		{
			switch(USART3_Struct.UartReceive_Buff[3])
			{
				case 0x00:
				{
					servo_Control(0, USART3_Struct.UartReceive_Buff[4]);
					break;
				}	
				case 0x01:
				{
					servo_Control(1, USART3_Struct.UartReceive_Buff[4]);
					break;
				}
				case 0x02:
				{
					servo_Control(2, USART3_Struct.UartReceive_Buff[4]);
					break;
				}
			}
		}
		else if(USART3_Struct.UartReceive_Buff[2] == 0x02)//控制机械臂上的电机
		{
			
		}
	}
}

int main(void)
{
//	u16 adc_H2S;
//	u16 adc_CO;
//	u16 adc_CH4;
//	u16 adcx;
//	u16 voltage;
//	uint8_t i;
//	u8 data[] = {0xFF, 0x00, 0x60, 0x70, 0xFF};
	Sys_Init();
	while(1)
	{
		Motor();
		Sensor();
//		
//		if(USART3_Struct.UartReceiveOk_Flag == 0xFF)
//		{
//			USART3_Struct.UartReceiveOk_Flag=0x00;
//			if(USART3_Struct.UartReceive_Buff[2] == 0x00 && USART3_Struct.UartReceive_Buff[3] == 0x00)//控制方向
//			{
//				if(USART3_Struct.UartReceive_Buff[4] == 0x01)
//					Motor_Control(FORWARD,FORWARD,50000,50000);
//				else if(USART3_Struct.UartReceive_Buff[4] == 0x02)
//				{
//					Motor_Control(STOP,STOP,0,0);
//				}
//				else if(USART3_Struct.UartReceive_Buff[4] == 0x03)
//				{	
//					
//				}
//			}
//			else if(USART3_Struct.UartReceive_Buff[2] == 0x00 && USART3_Struct.UartReceive_Buff[3] == 0x01)//控制速度
//			{
//				speed = 1000*USART3_Struct.UartReceive_Buff[4];
//				Motor_Control(FORWARD,FORWARD,speed,speed);
//			}
//		}
		/*for(i = 0;i < 3;i++)	//多通道AD转换测试
			UartSend_HalfWord(USART3, ADCConvertedValue[i]);*/
			//UartSend_Byte(USART3, ADCConvertedValue[i]);
		//UartSend_HalfWord(USART3,0xFFFF);
		
		//Delay_ms(1000);
	}
}
