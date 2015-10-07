#include "irq.H"

u8 ADC_FLAG = 0x00;//ADC转换标志位
//extern Struct_Remote Remote_Struct;
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: EXT_IRQ_Init
** 功能描述: 中断初始化
** 参数描述：无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void EXT_IRQ_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//使能PORTF时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PF4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOF.4
	
    //GPIOF.4 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource4);

  	EXTI_InitStructure.EXTI_Line    = EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			        //使能红外线所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: TIMER2_IRQ_Init
** 功能描述: arr：自动重装值, psc：时钟预分频数
** 参数描述：无
** 使用说明: 定时时间(uS):Tout=((arr+1)*(psc+1))/Tclk (Tclk:输入时钟频率(单位:Mhz))
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM2_IRQ_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设		 	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: TIM6_IRQ_Init
** 功能描述: 初始化定时器6
** 参数描述: arr：自动重装值, psc：时钟预分频数
** 使用说明: 定时时间(uS):Tout=((arr+1)*(psc+1))/Tclk (Tclk:输入时钟频率(单位:Mhz))
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM6_IRQ_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM6, ENABLE);  //使能TIMx外设	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: TIM7_IRQ_Init
** 功能描述: 初始化定时器7
** 参数描述: arr：自动重装值, psc：时钟预分频数
** 使用说明: 定时时间(uS):Tout=((arr+1)*(psc+1))/Tclk (Tclk:输入时钟频率(单位:Mhz))
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM7_IRQ_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM7中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM7, ENABLE);  //使能TIMx外设	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: TIM_IRQ_Init
** 功能描述: 初始化要用到的定时器(TIM2,TIM6,TIM7)
** 参数描述：无
** 作  　者: wu
** 使用说明：arr(自动装载值)=(Tclk*Tout/(psc+1))-1
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM_IRQ_Init(void)
{
	TIM2_IRQ_Init(17,99);     //25uS定时器中断初始化
	TIM6_IRQ_Init(1999,7199); //200mS定时器中断初始化
	TIM7_IRQ_Init(19999,7199); //2S定时器中断初始化
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: TIM1_IRQHandler
** 功能描述: 25uS定时器中断服务程序
** 参数描述：无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM2_IRQHandler(void)   //TIM2中断
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源
	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: TIM6_IRQHandler
** 功能描述: 200mS定时器中断服务程序
** 参数描述: 无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM6_IRQHandler(void)   //TIM6中断
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
		//LED2=!LED2;
	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: TIM7_IRQHandler
** 功能描述: 500mS定时器中断服务程序
** 参数描述：无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM7_IRQHandler(void)   //TIM7中断
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
		ADC_FLAG = 0xFF;	//置AD采集标志位
//		sensor_average(20);
//		Sensor();
	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: EXTI0_IRQHandler
** 功能描述: 外部中断4服务程序
** 参数描述: 无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void EXTI4_IRQHandler(void)
{
	//static u8 IRstart; 
	//static u8 i=0,j=0;
//	if((Remote_Struct.IRcnt>200)&&(Remote_Struct.IRcnt<550))/**/
//	{i=0;j=0;IRstart=1;goto Exit;}
//	if((IRstart==1)&&(Remote_Struct.IRcnt>=32)&&(Remote_Struct.IRcnt<100))/*跳过9mS的低电平和4.5mS的高电平引导码*/
//	{
//		Remote_Struct.IRcodetime[j][i]=Remote_Struct.IRcnt;
//	  i++;if(i==8){i=0;j++;if(j==4){IRstart=0;Remote_Struct.IRok=0xff;}}
//	}
//	else{i=0;j=0;Remote_Struct.IRok=0x00;IRstart=0;}
	//Exit:
//	 Remote_Struct.IRcnt=0;
	 EXTI_ClearITPendingBit(EXTI_Line4);  //清除EXTI4线路挂起位
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: EXTI9_5_IRQHandler
** 功能描述: 外部中断5服务程序
** 参数描述: 无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void EXTI9_5_IRQHandler(void)
{			
 	//EXTI_ClearITPendingBit(EXTI_Line5);    //清除LINE5上的中断标志位  
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: EXTI15_10_IRQHandler
** 功能描述: 外部中10服务程序
** 参数描述: 无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

void EXTI15_10_IRQHandler(void)
{
  //EXTI_ClearITPendingBit(EXTI_Line15);  //清除LINE15线路挂起位
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
