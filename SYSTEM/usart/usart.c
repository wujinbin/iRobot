#include "usart.h"	
//#include "led.h"
Struct_USART USART1_Struct;
Struct_USART USART3_Struct;
Struct_USART UART4_Struct;
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Uart_init
** 功能描述: 初始化串口1各个寄存器
** 参数描述：Bound->波特率
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart1_Init(u32 Bound)
{
   /*----------GPIO端口设置------------*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
 	USART_DeInit(USART1); //复位串口1
	
	//USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
    //USART 初始化设置
	USART_InitStructure.USART_BaudRate = Bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure);     //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能接收中断?
    USART_Cmd(USART1, ENABLE);                    //使能串口 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Uart_init
** 功能描述: 初始化串口2各个寄存器
** 参数描述：Bound->波特率
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart2_Init(u32 Bound)
{
    /*----------GPIO端口设置------------*/
	GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//使能USART3时钟
 	USART_DeInit(USART2); //复位串口3

	 //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PA.2
   
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PA.3

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
    //USART 初始化设置
	USART_InitStructure.USART_BaudRate = Bound;//设置波特率;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART2, &USART_InitStructure);     //初始化串口
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能接收中断?
    USART_Cmd(USART2, ENABLE);                    //使能串口 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Uart_init
** 功能描述: 初始化串口3各个寄存器
** 参数描述: Bound->波特率
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart3_Init(u32 Bound)
{
    /*----------GPIO端口设置------------*/
	GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	//使能USART3时钟
 	USART_DeInit(USART3); //复位串口3

	//USART1_TX   PB.10
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10; //PB.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
   
    //USART1_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
    //USART 初始化设置
	USART_InitStructure.USART_BaudRate = Bound;//设置波特率;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART3, &USART_InitStructure);     //初始化串口
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//使能接收中断?
    USART_Cmd(USART3, ENABLE);                    //使能串口 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Uart_init
** 功能描述: 初始化串口4各个寄存器
** 参数描述: Bound->波特率
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart4_Init(u32 Bound)
{
    /*----------GPIO端口设置------------*/
	GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能GPIOC时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);	//使能USART3时钟 
 	USART_DeInit(UART4); //复位串口3

	//USART1_TX   PC.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化PC10
   
    //USART1_RX	  PC.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PC11

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
    //USART 初始化设置
	USART_InitStructure.USART_BaudRate = Bound;//设置波特率;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(UART4, &USART_InitStructure);     //初始化串口
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//使能接收中断?
    USART_Cmd(UART4, ENABLE);                    //使能串口 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Uart_init
** 功能描述: 初始化串口5各个寄存器
** 参数描述：Bound->波特率
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Uart5_Init(u32 Bound)
{
    /*----------GPIO端口设置------------*/
    GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//使能GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);	//使能USART5时钟
	USART_DeInit(USART3); //复位串口3

	//USART1_TX   PC.12
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12; //PC.12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化PB10
   
    //USART1_RX	  PD.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PD.2

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
    //USART 初始化设置
	USART_InitStructure.USART_BaudRate = Bound;//设置波特率;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART3, &USART_InitStructure);     //初始化串口
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); //使能接收中断?
    USART_Cmd(UART5, ENABLE);                     //使能串口 
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Uart_init
** 功能描述: 初始化要使用的串口各个寄存器
** 参数描述：无
** 作  　者: wu
** 日　  期: 2015年09月20日
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
** 函数名称: UartSend_Byte
** 功能描述: 向串口x发送一个字节?
** 参数描述：USARTx->串口号(1-5), Data->要发送的数据
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void UartSend_Byte(USART_TypeDef* USARTx, u8 Data)
{
	assert_param(IS_USART_ALL_PERIPH(USARTx));
	assert_param(IS_USART_DATA(Data)); 
	USARTx->DR = (Data & (uint16_t)0x01FF);
	while((USARTx->SR&0X40)==0);//(TC=1,发送完成)等待发送结束
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: UartSend_HalfWord
** 功能描述: 向串口x发送两个字节16位数据
** 参数描述：USARTx->串口号(1-5), Data->要发送的数据
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void UartSend_HalfWord(USART_TypeDef* USARTx, u16 Data)
{
	u8 temp[2],i;
	temp[0] = (u8)(Data>>8)&0xFF;//高8位
	temp[1] = (u8)Data&0xFF;//低8位
	for(i = 0;i < 2;i++)
	{
		UartSend_Byte(USARTx, temp[i]);
	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: UartSend_nByte
** 功能描述: 向串口x发送length个字节?
** 参数描述：USARTx->串口号(1-5), Data->要发送的数据，length->发送数据长度?
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void UartSend_nByte(USART_TypeDef* USARTx, u8* Data, uint16_t length)
{
	uint16_t i;
	for(i=0;i<length;i++)
	{
		assert_param(IS_USART_ALL_PERIPH(USARTx));
		assert_param(IS_USART_DATA(Data[i])); 
		USARTx->DR = (Data[i] & (uint16_t)0x01FF);
		while((USARTx->SR&0X40)==0);//(TC=1,发送完成)等待发送结束
	}	  
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: USART1_IRQHandler
** 功能描述: 串口1中断服务程序
** 参数描述：无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_IRQHandler(void)                	
{
	u8 i;
	u8 data = 0;
	static u8 startreceive_flag = 0;
	static u8 receive_count = 0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE)!= RESET) //判断是不是串口有接收到数据
	{
		data =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据 
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
** 函数名称: USART3_IRQHandler
** 功能描述: 串口3中断服务程序(接收上位机指令)
** 参数描述: 无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART3_IRQHandler(void)                	
{
	u8 data = 0;
    static u8 startreceive_flag = 0;
	static u8 checksecondbyte_flag = 0;
    static u8 receive_count = 0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE)!= RESET) //判断是不是串口有接收到数据
	{ 
		data =USART_ReceiveData(USART3);//(USART1->DR);	//读取接收到的数据 
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
				if(receive_count == 3)//接收完成
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
				if(receive_count > 3)//接收到异常数据，停止接收
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
** 函数名称: USART1_IRQHandler
** 功能描述: 串口4中断服务程序
** 参数描述：无
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void UART4_IRQHandler(void)                	
{
	u8 i;
	u8 data                     = 0;
	static u8 startreceive_flag = 0;
	static u8 receive_count     = 0;
	if(USART_GetITStatus(UART4, USART_IT_RXNE)!= RESET) //判断是不是串口有接收到数据
	{
		data =USART_ReceiveData(UART4);//(USART1->DR);	//读取接收到的数据 
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

