#include "irq.H"

u8 ADC_FLAG = 0x00;//ADCת����־λ
//extern Struct_Remote Remote_Struct;
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: EXT_IRQ_Init
** ��������: �жϳ�ʼ��
** ������������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void EXT_IRQ_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//ʹ��PORTFʱ��
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PF4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIOF.4
	
    //GPIOF.4 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource4);

  	EXTI_InitStructure.EXTI_Line    = EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			        //ʹ�ܺ��������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: TIMER2_IRQ_Init
** ��������: arr���Զ���װֵ, psc��ʱ��Ԥ��Ƶ��
** ������������
** ʹ��˵��: ��ʱʱ��(uS):Tout=((arr+1)*(psc+1))/Tclk (Tclk:����ʱ��Ƶ��(��λ:Mhz))
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM2_IRQ_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����		 	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: TIM6_IRQ_Init
** ��������: ��ʼ����ʱ��6
** ��������: arr���Զ���װֵ, psc��ʱ��Ԥ��Ƶ��
** ʹ��˵��: ��ʱʱ��(uS):Tout=((arr+1)*(psc+1))/Tclk (Tclk:����ʱ��Ƶ��(��λ:Mhz))
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM6_IRQ_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx����	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: TIM7_IRQ_Init
** ��������: ��ʼ����ʱ��7
** ��������: arr���Զ���װֵ, psc��ʱ��Ԥ��Ƶ��
** ʹ��˵��: ��ʱʱ��(uS):Tout=((arr+1)*(psc+1))/Tclk (Tclk:����ʱ��Ƶ��(��λ:Mhz))
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM7_IRQ_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM7�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM7, ENABLE);  //ʹ��TIMx����	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: TIM_IRQ_Init
** ��������: ��ʼ��Ҫ�õ��Ķ�ʱ��(TIM2,TIM6,TIM7)
** ������������
** ��  ����: wu
** ʹ��˵����arr(�Զ�װ��ֵ)=(Tclk*Tout/(psc+1))-1
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM_IRQ_Init(void)
{
	TIM2_IRQ_Init(17,99);     //25uS��ʱ���жϳ�ʼ��
	TIM6_IRQ_Init(1999,7199); //200mS��ʱ���жϳ�ʼ��
	TIM7_IRQ_Init(19999,7199); //2S��ʱ���жϳ�ʼ��
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: TIM1_IRQHandler
** ��������: 25uS��ʱ���жϷ������
** ������������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ
	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: TIM6_IRQHandler
** ��������: 200mS��ʱ���жϷ������
** ��������: ��
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM6_IRQHandler(void)   //TIM6�ж�
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		//LED2=!LED2;
	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: TIM7_IRQHandler
** ��������: 500mS��ʱ���жϷ������
** ������������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM7_IRQHandler(void)   //TIM7�ж�
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		ADC_FLAG = 0xFF;	//��AD�ɼ���־λ
//		sensor_average(20);
//		Sensor();
	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: EXTI0_IRQHandler
** ��������: �ⲿ�ж�4�������
** ��������: ��
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void EXTI4_IRQHandler(void)
{
	//static u8 IRstart; 
	//static u8 i=0,j=0;
//	if((Remote_Struct.IRcnt>200)&&(Remote_Struct.IRcnt<550))/**/
//	{i=0;j=0;IRstart=1;goto Exit;}
//	if((IRstart==1)&&(Remote_Struct.IRcnt>=32)&&(Remote_Struct.IRcnt<100))/*����9mS�ĵ͵�ƽ��4.5mS�ĸߵ�ƽ������*/
//	{
//		Remote_Struct.IRcodetime[j][i]=Remote_Struct.IRcnt;
//	  i++;if(i==8){i=0;j++;if(j==4){IRstart=0;Remote_Struct.IRok=0xff;}}
//	}
//	else{i=0;j=0;Remote_Struct.IRok=0x00;IRstart=0;}
	//Exit:
//	 Remote_Struct.IRcnt=0;
	 EXTI_ClearITPendingBit(EXTI_Line4);  //���EXTI4��·����λ
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: EXTI9_5_IRQHandler
** ��������: �ⲿ�ж�5�������
** ��������: ��
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void EXTI9_5_IRQHandler(void)
{			
 	//EXTI_ClearITPendingBit(EXTI_Line5);    //���LINE5�ϵ��жϱ�־λ  
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: EXTI15_10_IRQHandler
** ��������: �ⲿ��10�������
** ��������: ��
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

void EXTI15_10_IRQHandler(void)
{
  //EXTI_ClearITPendingBit(EXTI_Line15);  //���LINE15��·����λ
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
