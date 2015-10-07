/*=====================================================================
//	功能描述:  马达驱动源文件
//  IDE 环境:  Keil uVision5.1
//  组成文件:	  Motor.c,Motor.h
//  硬    件:   TIME4(CH1-CH4)
//  硬件资源:   PWM
//  维护记录:	  2015-09-20	v1.0
======================================================================*/
#include "motor.h"
#include "usart.h"	
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* 函 数 名: IO_Init(void)
* 功    能: 马达驱动端口初始化?
* 入口参数：无
* 出口参数: 无
* 说    明: 对要使用的IO口进行初始化?
* 调用方法: 直接调用
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void DriverIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PC,PE,PG端口时钟
	/*---------------------LED端口初始化-------------------------------------*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13|GPIO_Pin_14;//LED2,LED3端口配置
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					         //根据设定参数初始化GPIOA.8
	GPIO_ResetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);					 //PA.13,PA.14 输出0?
	/*---------------------电机端口初始化-------------------------------------*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//驱动端口IN1~IN4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					         //根据设定参数初始化GPIOE
	GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);					 //
///*---------------------舵机端口初始化-------------------------------------*/
//	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//舵机端口SERVO1~SERVO4
//	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		   //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
//	GPIO_Init(GPIOC, &GPIO_InitStructure);					         //根据设定参数初始化GPIOC
//	GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
	
	/*-------------释放PB3 PB4为普通IO口(不然不能正常输出信号)-------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	/*---------------------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//驱动端口IN5~IN7
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 		   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					         //根据设定参数初始化GPIOE
	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5); //

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;       //驱动端口IN8
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
	GPIO_Init(GPIOG, &GPIO_InitStructure);					    //根据设定参数初始化GPIO
	GPIO_SetBits(GPIOG,GPIO_Pin_15);//
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* 函 数 名: TIME4_PWM_Init
* 功    能: PWM输出初始化函数
* 入口参数：arry(PWM频率自动转载值),psc(时钟预分频数)
* 出口参数: 无
* 说    明: PWM频率=72000/(arr+1)
* 调用方法: 直接调用
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOB外设时钟使能
	                                                                     	

    //设置该引脚为复用输出功能,输出TIM4 CH1~CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//TIM_CH1~TIM_CH4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr;      //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc;    //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较时极性低
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx的CH1通道
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx的CH2通道
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx的CH3通道
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx的CH4通道
		
	TIM_CtrlPWMOutputs(TIM4,ENABLE);	        //MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH2预装载使能
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH3预装载使能?
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH4预装载使能
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* 函 数 名: TIME8_PWM_Init
* 功    能: PWM输出初始化函数
* 入口参数：arry(PWM频率自动转载值),psc(时钟预分频数)
* 出口参数: 无
* 说    明: PWM频率=72000/(arr+1)
* 调用方法: 直接调用
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM8_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//使能定时器8
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);//使能GPIOB外设时钟使能
	                                                                     	

    //设置该引脚为复用输出功能,输出TIM8 CH1~CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//TIM8_CH1~TIM8_CH4
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM_DeInit(TIM8);
	TIM_TimeBaseStructure.TIM_Period = arr;      //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc;    //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较时极性低
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx的CH1通道
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx的CH2通道
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx的CH3通道
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx的CH4通道
		
    TIM_CtrlPWMOutputs(TIM8,ENABLE);	        //MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2预装载使能
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH3预装载使能
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4预装载使能
	
	TIM_ARRPreloadConfig(TIM8, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM8, ENABLE);  //使能TIM8
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* 函 数 名: Motor_Control
* 功    能: 马达状态控制?
* 入口参数u8 Motor_L, u8 Motor_R, u16 PWM_L, u16 PWM_R
* 出口参数: 无
* 说    明: PWM<=59999
* 调用方法: 直接调用
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Motor_Control (u8 Motor_L, u8 Motor_R, u16 PWM_L, u16 PWM_R)
{
	static u8  temp_motorl = 0;
	static u8  temp_motorr = 0;
	static u16 temp_pwml   = 0;
	static u16 temp_pwmr   = 0;
/*-----------更新电机转动状态-----------------*/
	if(temp_motorl!=Motor_L)//当前电机状态发生改变
	{ 
		if(Motor_L==STOP){MOTORL_STOP;}//停止
		if(Motor_L==FORWARD){MOTORL_FORWARD;}//前进
		if(Motor_L==BACKWARD){MOTORL_BACKWARD;}//后退	 
	}
	if(temp_motorr!=Motor_R)//当前电机状态发生改变
	{ 
		if(Motor_R==STOP){MOTORR_STOP;}//停止
		if(Motor_R==FORWARD){MOTORR_FORWARD;}//前进
		if(Motor_R==BACKWARD){MOTORR_BACKWARD;}//后退	
	}
/*-------------------------------------------*/ 
 
/*-----------------更新PWM值-----------------*/ 
/* if(temp_pwml!=PWM_L)//当前PWM值发生改变
 {
	 TIM_SetCompare3(TIM4,PWM_L);  //左后电机PWM调速
	 TIM_SetCompare4(TIM4,PWM_L);  //左前电机PWM调速
 }
 if(temp_pwmr!=PWM_R)//当前PWM值发生改变
 { 
	 TIM_SetCompare1(TIM4,PWM_R);  //右后电机PWM调速
	 TIM_SetCompare2(TIM4,PWM_R);  //右前电机PWM调速
 }*/
/*-------------------------------------------*/
 
	if(temp_pwml!=PWM_L)//当前PWM值发生改变
	{
		TIM_SetCompare3(TIM4,PWM_L);  //左电机PWM调速
	}
	if(temp_pwmr!=PWM_R)//当前PWM值发生改变
	{ 
		TIM_SetCompare4(TIM4,PWM_R);  //右电机PWM调速
	}
 
	temp_pwml  = PWM_L;   
	temp_pwmr   = PWM_R;
	temp_motorl= Motor_L; 
	temp_motorr = Motor_R;
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* 函 数 名: servo_Control
* 功    能: 舵机状态控制
* 入口参数: u8 servo, u16 PWM
* 出口参数: 无
* 说    明: servo为舵机编号（0代表舵机1，1代表舵机2，类推），45<=PWM<=225（0度~180度）
* 调用方法: 直接调用
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void servo_Control (u8 servo, u16 PWM)
{
	static u16 temp_pwm1 = 0;
	static u16 temp_pwm2 = 0;
	static u16 temp_pwm3 = 0;
	
	if(PWM <= 180)//PWM需加上45，满足0.5ms宽的高电平
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
* 函 数 名: Speed_Control
* 功    能: 电机转速控制
* 入口参数u16 PWM_L, u16 PWM_R
* 出口参数: 无
* 说    明: servo为舵机编号（0代表舵机1，1代表舵机2，类推），45<=PWM<=225（0度~180度）
* 调用方法: 直接调用
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Speed_Control(u16 PWM_L, u16 PWM_R)
{
	static u16 speed_L = 0;
	static u16 speed_R = 0;
	
	if(speed_L != PWM_L)
	{
		TIM_SetCompare3(TIM4,PWM_L);  //左电机PWM调速
	}
	if(speed_R != PWM_R)
	{
		TIM_SetCompare4(TIM4,PWM_R);  //右电机PWM调速
	}
	
	speed_L = PWM_L;
	speed_R = PWM_R;
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
