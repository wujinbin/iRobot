#include "usart.h"	
//#include "led.h"
Struct_USART USART1_Struct;
Struct_USART USART3_Struct;
Struct_USART UART4_Struct;
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Uart_init
** ��������: ��ʼ������1�����Ĵ���
** ����������Bound->������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart1_Init(u32 Bound)
{
   /*----------GPIO�˿�����------------*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
 	USART_DeInit(USART1); //��λ����1
	
	//USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
    //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = Bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure);     //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�?
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Uart_init
** ��������: ��ʼ������2�����Ĵ���
** ����������Bound->������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart2_Init(u32 Bound)
{
    /*----------GPIO�˿�����------------*/
	GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOBʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//ʹ��USART3ʱ��
 	USART_DeInit(USART2); //��λ����3

	 //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PA.2
   
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PA.3

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
    //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = Bound;//���ò�����;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure);     //��ʼ������
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�?
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Uart_init
** ��������: ��ʼ������3�����Ĵ���
** ��������: Bound->������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart3_Init(u32 Bound)
{
    /*----------GPIO�˿�����------------*/
	GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	//ʹ��USART3ʱ��
 	USART_DeInit(USART3); //��λ����3

	//USART1_TX   PB.10
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10; //PB.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
   
    //USART1_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
    //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = Bound;//���ò�����;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure);     //��ʼ������
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�?
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Uart_init
** ��������: ��ʼ������4�����Ĵ���
** ��������: Bound->������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart4_Init(u32 Bound)
{
    /*----------GPIO�˿�����------------*/
	GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��GPIOCʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);	//ʹ��USART3ʱ�� 
 	USART_DeInit(UART4); //��λ����3

	//USART1_TX   PC.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PC10
   
    //USART1_RX	  PC.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PC11

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
    //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = Bound;//���ò�����;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(UART4, &USART_InitStructure);     //��ʼ������
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�?
    USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ��� 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Uart_init
** ��������: ��ʼ������5�����Ĵ���
** ����������Bound->������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart5_Init(u32 Bound)
{
    /*----------GPIO�˿�����------------*/
    GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//ʹ��GPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//ʹ��GPIOBʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);	//ʹ��USART5ʱ��
	USART_DeInit(USART3); //��λ����3

	//USART1_TX   PC.12
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12; //PC.12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PB10
   
    //USART1_RX	  PD.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PD.2

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
    //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = Bound;//���ò�����;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure);     //��ʼ������
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); //ʹ�ܽ����ж�?
    USART_Cmd(UART5, ENABLE);                     //ʹ�ܴ��� 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Uart_init
** ��������: ��ʼ��Ҫʹ�õĴ��ڸ����Ĵ���
** ������������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart_Init(void)
{
	Uart1_Init(9600);
	//Uart2_Init(9600);	
	Uart3_Init(9600);	
	Uart4_Init(9600);
    //Uart5_Init(9600);		
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: UartSend_Byte
** ��������: �򴮿�x����һ���ֽ�?
** ����������USARTx->���ں�(1-5), Data->Ҫ���͵�����
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void UartSend_Byte(USART_TypeDef* USARTx, u8 Data)
{
	assert_param(IS_USART_ALL_PERIPH(USARTx));
	assert_param(IS_USART_DATA(Data)); 
	USARTx->DR = (Data & (uint16_t)0x01FF);
	while((USARTx->SR&0X40)==0);//(TC=1,�������)�ȴ����ͽ���
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: UartSend_HalfWord
** ��������: �򴮿�x���������ֽ�16λ����
** ����������USARTx->���ں�(1-5), Data->Ҫ���͵�����
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void UartSend_HalfWord(USART_TypeDef* USARTx, u16 Data)
{
	u8 temp[2],i;
	temp[0] = (u8)(Data>>8)&0xFF;//��8λ
	temp[1] = (u8)Data&0xFF;//��8λ
	for(i = 0;i < 2;i++)
	{
		UartSend_Byte(USARTx, temp[i]);
	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: UartSend_nByte
** ��������: �򴮿�x����length���ֽ�?
** ����������USARTx->���ں�(1-5), Data->Ҫ���͵����ݣ�length->�������ݳ���?
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void UartSend_nByte(USART_TypeDef* USARTx, u8* Data, uint16_t length)
{
	uint16_t i;
	for(i=0;i<length;i++)
	{
		assert_param(IS_USART_ALL_PERIPH(USARTx));
		assert_param(IS_USART_DATA(Data[i])); 
		USARTx->DR = (Data[i] & (uint16_t)0x01FF);
		while((USARTx->SR&0X40)==0);//(TC=1,�������)�ȴ����ͽ���
	}	  
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: USART1_IRQHandler
** ��������: ����1�жϷ������
** ������������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_IRQHandler(void)                	
{
	u8 i;
	u8 data = 0;
	static u8 startreceive_flag = 0;
	static u8 receive_count = 0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE)!= RESET) //�ж��ǲ��Ǵ����н��յ�����
	{
		data =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ������� 
		if(!startreceive_flag){if(data==HEAD){startreceive_flag=1;USART1_Struct.UartReceive_Buff[0]=data;}goto Exit;}
		if(startreceive_flag)
		{
			USART1_Struct.UartReceive_Buff[receive_count+1]=data;receive_count++;
			if((receive_count==9)&&(USART1_Struct.UartReceive_Buff[9]==TAIL))
			{receive_count=0x00;startreceive_flag=0;USART1_Struct.UartReceiveOk_Flag=0xff;}
			if((receive_count==9)&&(USART1_Struct.UartReceive_Buff[9]!=TAIL))
			{receive_count=0;startreceive_flag=0;for(i=0;i<10;i++){USART1_Struct.UartReceive_Buff[i]=0;}}
		}	
	} 
	Exit:
		data=0;  	
} 
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: USART3_IRQHandler
** ��������: ����3�жϷ������(������λ��ָ��)
** ��������: ��
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART3_IRQHandler(void)                	
{
	u8 data = 0;
    static u8 startreceive_flag = 0;
	static u8 checksecondbyte_flag = 0;
    static u8 receive_count = 0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE)!= RESET) //�ж��ǲ��Ǵ����н��յ�����
	{ 
		data =USART_ReceiveData(USART3);//(USART1->DR);	//��ȡ���յ������� 
		//UartSend_Byte(USART3, data);
		//UartSend_Byte(USART3, 0xFF);
		if(!startreceive_flag)
		{
			if(!checksecondbyte_flag)
			{
				if(data==HEAD)
				{
					USART3_Struct.UartReceive_Buff[0]=data;
					checksecondbyte_flag=1;
					startreceive_flag=1;
				}
				goto Exit;
			}
		}
		else if(startreceive_flag)
		{
			if(data == TAIL)
			{
				if(receive_count == 3)//�������
				{
					startreceive_flag=0;
					USART3_Struct.UartReceive_Buff[1]=data;
					checksecondbyte_flag=0;
					receive_count=0;
					USART3_Struct.UartReceiveOk_Flag=0xff;
				}
				else
				{
					startreceive_flag=0;
					checksecondbyte_flag=0;
					receive_count=0;
				}
			}
			else
			{
				USART3_Struct.UartReceive_Buff[receive_count+2]=data;
				receive_count++;
				if(receive_count > 3)//���յ��쳣���ݣ�ֹͣ����
				{
					startreceive_flag=0;
					checksecondbyte_flag=0;
					receive_count=0;
				}
			}
		}
//		if(!startreceive_flag)
//		{
//			if(checksecondbyte_flag)
//			{
//				if(data==TAIL)
//				{
//					startreceive_flag=0;
//					USART3_Struct.UartReceive_Buff[1]=data;
//					checksecondbyte_flag=0;
//					complete = 1;
//				}
//			goto Exit;
//			}
//		}
	} 
	Exit:
		data=0;  
	
} 
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: USART1_IRQHandler
** ��������: ����4�жϷ������
** ������������
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void UART4_IRQHandler(void)                	
{
	u8 i;
	u8 data                     = 0;
	static u8 startreceive_flag = 0;
	static u8 receive_count     = 0;
	if(USART_GetITStatus(UART4, USART_IT_RXNE)!= RESET) //�ж��ǲ��Ǵ����н��յ�����
	{
		data =USART_ReceiveData(UART4);//(USART1->DR);	//��ȡ���յ������� 
		if(!startreceive_flag){if(data==HEAD){startreceive_flag=1;UART4_Struct.UartReceive_Buff[0]=data;}goto Exit;}
		if(startreceive_flag)
		{	
			UART4_Struct.UartReceive_Buff[receive_count+1]=data;receive_count++;
			if((receive_count==9)&&(UART4_Struct.UartReceive_Buff[9]==TAIL))
			{receive_count=0x00;startreceive_flag=0;UART4_Struct.UartReceiveOk_Flag=0xff;}
			if((receive_count==9)&&(UART4_Struct.UartReceive_Buff[9]!=TAIL))
			{receive_count=0;startreceive_flag=0;for(i=0;i<10;i++){UART4_Struct.UartReceive_Buff[i]=0;}}
		}	
	} 
	Exit:
		data=0;  	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/	

