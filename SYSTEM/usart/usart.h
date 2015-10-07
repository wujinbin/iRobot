/*==================================================
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
=====================================================*/	
#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"
#include  "motor.h"
//#define EN_USART1_RX 			1		 //使能（1）/禁止（0）串口1接收
//#define EN_USART2_RX 			1		 //使能（1）/禁止（0）串口1接收
//#define EN_USART3_RX 			1		 //使能（1）/禁止（0）串口1接收
//#define EN_USART4_RX 			1		 //使能（1）/禁止（0）串口1接收
//#define EN_USART5_RX 			1		 //使能（1）/禁止（0）串口1接?
#define   HEAD              0x55
#define   TAIL              0xaa
/*==========串口1结构体==========*/
typedef struct
{
  u8 UartReceiveOk_Flag;
  u8 UartSend_Buff[20];   
  u8 UartReceive_Buff[20];
}Struct_USART;
/*==========================================*/
void Uart_Init(void);
void Uart1_init(u32 bound);
void Uart2_init(u32 bound);
void Uart3_init(u32 bound);
void Uart4_init(u32 bound);
void Uart5_init(u32 bound);
void UartSend_Byte(USART_TypeDef* USARTx, u8 Data); //向串口USARTx发送1个字节数据
void UartSend_HalfWord(USART_TypeDef* USARTx, u16 Data);  //发送2字节16位数据
void UartSend_nByte(USART_TypeDef* USARTx,u8* Data,uint16_t length);//向串口USARTx发送length个字节数据
#endif


