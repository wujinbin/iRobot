/*=====================================================================
//	��������:	  iRobot
//	��������:  �ܵ������˿���		
//  IDE ����:  Keil uVision5.1
//  ����ļ�:	  main.c,include.h
//  Ӳ    ��:   STM32F103ZET6-LQFP144 ����Ƶ��:72MHZ
//  Ӳ����Դ: 
//  ά����¼:	  2015-09-28	v1.0
======================================================================*/
#include "includes.h"

/*::::::::::::::::::::::::::::::
** ��������: Parameter_Init
** ��������: ϵͳ������ʼ��
** ������������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
::::::::::::::::::::::::::::::::*/
void Parameter_Init(void)
{
	Motor_L        = STOP;
	Motor_R        = STOP;
	MotorL_Speed   = SPEED_LEVEL10;
	MotorR_Speed   = SPEED_LEVEL10;
	Sys_Status     = MODE_STANDBY;//����ģʽ	
	Delay_ms(1000);
	//Motor_Control(FORWARD,FORWARD,30000,30000);
}

/*::::::::::::::::::::::::::::::::::::
** ��������: void Sys_Init(void)
** ��������: ϵͳӲ����ʼ��
** ������������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
::::::::::::::::::::::::::::::::::::::*/
void Sys_Init(void)
{
	Delay_init();	    	       //��ʱ������ʼ��	
	DriverIO_Init();           //��������˿ڳ�ʼ��
	adc_Init();					//adcת��ģ���ʼ��
	NVIC_Configuration();      //�����ж����ȼ�����
	Uart_Init();	             //���ڳ�ʼ��
	TIM_IRQ_Init();            //��ʼ���õ��Ķ�ʱ��
	EXT_IRQ_Init();            // ��ʼ���ⲿ�ж�
	TIM4_PWM_Init(FREQ_1KHZ,0);//PWM������ʼ(Freq=1.2KHz)
	TIM8_PWM_Init(449,799);//���PWM������ʼ�����μ���Ϊ11us,����5MS
	//TIM8_PWM_Init(199,7199);//���PWM������ʼ�����μ���Ϊ11us,����20MS
	Parameter_Init();          //ϵͳ������ʼ��
} 
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* �� �� ��: Motor
* ��    ��: �������е��״̬����
* ��ڲ���: ��
* ���ڲ���: ��
* ˵    ��: PWM<=59999
* ���÷���: ֱ�ӵ���
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Motor(void)
{
	//u16 speed;
	if(USART3_Struct.UartReceiveOk_Flag == 0xFF)
	{
		//servo_Control(0, 0);
		USART3_Struct.UartReceiveOk_Flag = 0x00;
		if(USART3_Struct.UartReceive_Buff[2] == 0x00 )//�����������
		{
			if(USART3_Struct.UartReceive_Buff[3] == 0x00)//���Ʒ���
			{
				if(USART3_Struct.UartReceive_Buff[4] == 0x01)//ǰ��
				{
					Motor_L = Motor_R = FORWARD;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
				else if(USART3_Struct.UartReceive_Buff[4] == 0x02)//ֹͣ
				{
					Motor_L = Motor_R = STOP;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
				else if(USART3_Struct.UartReceive_Buff[4] == 0x03)//����
				{	
					Motor_L = Motor_R = BACKWARD;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
				else if(USART3_Struct.UartReceive_Buff[4] == 0x04)//��ת
				{
					Motor_L = BACKWARD;
					Motor_R = FORWARD;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
				else if(USART3_Struct.UartReceive_Buff[4] == 0x05)//��ת
				{
					Motor_L = FORWARD;
					Motor_R = BACKWARD;
					Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
				}
			}
			else if(USART3_Struct.UartReceive_Buff[3] == 0x01)//�����ٶ�
			{
				MotorL_Speed = MotorR_Speed = 1000*USART3_Struct.UartReceive_Buff[4];
				Motor_Control(Motor_L,Motor_R,MotorL_Speed,MotorR_Speed);
			}
		}
		else if(USART3_Struct.UartReceive_Buff[2] == 0x01)//���ƻ�е�۶��
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
		else if(USART3_Struct.UartReceive_Buff[2] == 0x02)//���ƻ�е���ϵĵ��
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
//			if(USART3_Struct.UartReceive_Buff[2] == 0x00 && USART3_Struct.UartReceive_Buff[3] == 0x00)//���Ʒ���
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
//			else if(USART3_Struct.UartReceive_Buff[2] == 0x00 && USART3_Struct.UartReceive_Buff[3] == 0x01)//�����ٶ�
//			{
//				speed = 1000*USART3_Struct.UartReceive_Buff[4];
//				Motor_Control(FORWARD,FORWARD,speed,speed);
//			}
//		}
		/*for(i = 0;i < 3;i++)	//��ͨ��ADת������
			UartSend_HalfWord(USART3, ADCConvertedValue[i]);*/
			//UartSend_Byte(USART3, ADCConvertedValue[i]);
		//UartSend_HalfWord(USART3,0xFFFF);
		
		//Delay_ms(1000);
	}
}
