/*=====================================================================
//	��������:  �������Դ�ļ�
//  IDE ����:  Keil uVision5.1
//  ����ļ�:	  Motor.c,Motor.h
//  Ӳ    ��:   TIME4(CH1-CH4)
//  Ӳ����Դ:   PWM
//  ά����¼:	  2015-09-20	v1.0
======================================================================*/
#include "motor.h"
#include "usart.h"	
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* �� �� ��: IO_Init(void)
* ��    ��: ��������˿ڳ�ʼ��?
* ��ڲ�������
* ���ڲ���: ��
* ˵    ��: ��Ҫʹ�õ�IO�ڽ��г�ʼ��?
* ���÷���: ֱ�ӵ���
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void DriverIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PC,PE,PG�˿�ʱ��
	/*---------------------LED�˿ڳ�ʼ��-------------------------------------*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13|GPIO_Pin_14;//LED2,LED3�˿�����
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					         //�����趨������ʼ��GPIOA.8
	GPIO_ResetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);					 //PA.13,PA.14 ���0?
	/*---------------------����˿ڳ�ʼ��-------------------------------------*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//�����˿�IN1~IN4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					         //�����趨������ʼ��GPIOE
	GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);					 //
///*---------------------����˿ڳ�ʼ��-------------------------------------*/
//	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//����˿�SERVO1~SERVO4
//	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		   //�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
//	GPIO_Init(GPIOC, &GPIO_InitStructure);					         //�����趨������ʼ��GPIOC
//	GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
	
	/*-------------�ͷ�PB3 PB4Ϊ��ͨIO��(��Ȼ������������ź�)-------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	/*---------------------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//�����˿�IN5~IN7
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					         //�����趨������ʼ��GPIOE
	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5); //

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;       //�����˿�IN8
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOG, &GPIO_InitStructure);					    //�����趨������ʼ��GPIO
	GPIO_SetBits(GPIOG,GPIO_Pin_15);//
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* �� �� ��: TIME4_PWM_Init
* ��    ��: PWM�����ʼ��������
* ��ڲ�����arry(PWMƵ���Զ�ת��ֵ),psc(ʱ��Ԥ��Ƶ��)
* ���ڲ���: ��
* ˵    ��: PWMƵ��=72000/(arr+1)
* ���÷���: ֱ�ӵ���
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOB����ʱ��ʹ��
	                                                                     	

    //���ø�����Ϊ�����������,���TIM4 CH1~CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//TIM_CH1~TIM_CH4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr;      //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc;    //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚ�ʱ���Ե�
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx��CH1ͨ��
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx��CH2ͨ��
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx��CH3ͨ��
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx��CH4ͨ��
		
	TIM_CtrlPWMOutputs(TIM4,ENABLE);	        //MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��?
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* �� �� ��: TIME8_PWM_Init
* ��    ��: PWM�����ʼ��������
* ��ڲ�����arry(PWMƵ���Զ�ת��ֵ),psc(ʱ��Ԥ��Ƶ��)
* ���ڲ���: ��
* ˵    ��: PWMƵ��=72000/(arr+1)
* ���÷���: ֱ�ӵ���
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM8_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//ʹ�ܶ�ʱ��8
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);//ʹ��GPIOB����ʱ��ʹ��
	                                                                     	

    //���ø�����Ϊ�����������,���TIM8 CH1~CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//TIM8_CH1~TIM8_CH4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM_DeInit(TIM8);
	TIM_TimeBaseStructure.TIM_Period = arr;      //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc;    //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚ�ʱ���Ե�
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx��CH1ͨ��
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx��CH2ͨ��
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx��CH3ͨ��
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx��CH4ͨ��
		
    TIM_CtrlPWMOutputs(TIM8,ENABLE);	        //MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��
	
	TIM_ARRPreloadConfig(TIM8, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM8
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* �� �� ��: Motor_Control
* ��    ��: ���״̬������?
* ��ڲ����uu8 Motor_L, u8 Motor_R, u16 PWM_L, u16 PWM_R
* ���ڲ���: ��
* ˵    ��: PWM<=59999
* ���÷���: ֱ�ӵ���
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Motor_Control (u8 Motor_L, u8 Motor_R, u16 PWM_L, u16 PWM_R)
{
	static u8  temp_motorl = 0;
	static u8  temp_motorr = 0;
	static u16 temp_pwml   = 0;
	static u16 temp_pwmr   = 0;
/*-----------���µ��ת��״̬-----------------*/
	if(temp_motorl!=Motor_L)//��ǰ���״̬�����ı�
	{ 
		if(Motor_L==STOP){MOTORL_STOP;}//ֹͣ
		if(Motor_L==FORWARD){MOTORL_FORWARD;}//ǰ��
		if(Motor_L==BACKWARD){MOTORL_BACKWARD;}//����	 
	}
	if(temp_motorr!=Motor_R)//��ǰ���״̬�����ı�
	{ 
		if(Motor_R==STOP){MOTORR_STOP;}//ֹͣ
		if(Motor_R==FORWARD){MOTORR_FORWARD;}//ǰ��
		if(Motor_R==BACKWARD){MOTORR_BACKWARD;}//����	
	}
/*-------------------------------------------*/ 
 
/*-----------------����PWMֵ-----------------*/ 
/* if(temp_pwml!=PWM_L)//��ǰPWMֵ�����ı�
 {
	 TIM_SetCompare3(TIM4,PWM_L);  //�����PWM����
	 TIM_SetCompare4(TIM4,PWM_L);  //��ǰ���PWM����
 }
 if(temp_pwmr!=PWM_R)//��ǰPWMֵ�����ı�
 { 
	 TIM_SetCompare1(TIM4,PWM_R);  //�Һ���PWM����
	 TIM_SetCompare2(TIM4,PWM_R);  //��ǰ���PWM����
 }*/
/*-------------------------------------------*/
 
	if(temp_pwml!=PWM_L)//��ǰPWMֵ�����ı�
	{
		TIM_SetCompare3(TIM4,PWM_L);  //����PWM����
	}
	if(temp_pwmr!=PWM_R)//��ǰPWMֵ�����ı�
	{ 
		TIM_SetCompare4(TIM4,PWM_R);  //�ҵ��PWM����
	}
 
	temp_pwml  = PWM_L;   
	temp_pwmr   = PWM_R;
	temp_motorl= Motor_L; 
	temp_motorr = Motor_R;
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* �� �� ��: servo_Control
* ��    ��: ���״̬������
* ��ڲ���: u8 servo, u16 PWM
* ���ڲ���: ��
* ˵    ��: servoΪ�����ţ�0������1��1������2�����ƣ���45<=PWM<=225��0��~180�ȣ�
* ���÷���: ֱ�ӵ���
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void servo_Control (u8 servo, u16 PWM)
{
	static u16 temp_pwm1 = 0;
	static u16 temp_pwm2 = 0;
	static u16 temp_pwm3 = 0;
	
	if(PWM <= 180)//PWM�����45������0.5ms��ĸߵ�ƽ
	{
		switch(servo)
		{
			case 0:
			{
				if(temp_pwm1 != PWM)
				{
					TIM_SetCompare1(TIM8, PWM+45);
				}
				temp_pwm1 = PWM;
				break;
			}
			case 1:
			{
				if(temp_pwm2 != PWM)
				{
					TIM_SetCompare2(TIM8, PWM+45);
				}
				temp_pwm2 = PWM;
				break;
			}
			case 2:
			{
				if(temp_pwm3 != PWM)
				{
					TIM_SetCompare3(TIM8, PWM+45);
				}
				temp_pwm3 = PWM;
				break;
			}
			default:break;
		}
	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* �� �� ��: Speed_Control
* ��    ��: ���ת�ٿ�����
* ��ڲ����uu16 PWM_L, u16 PWM_R
* ���ڲ���: ��
* ˵    ��: servoΪ�����ţ�0������1��1������2�����ƣ���45<=PWM<=225��0��~180�ȣ�
* ���÷���: ֱ�ӵ���
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Speed_Control(u16 PWM_L, u16 PWM_R)
{
	static u16 speed_L = 0;
	static u16 speed_R = 0;
	
	if(speed_L != PWM_L)
	{
		TIM_SetCompare3(TIM4,PWM_L);  //����PWM����
	}
	if(speed_R != PWM_R)
	{
		TIM_SetCompare4(TIM4,PWM_R);  //�ҵ��PWM����
	}
	
	speed_L = PWM_L;
	speed_R = PWM_R;
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
