/*==================================================
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
=====================================================*/	
#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"
#include  "motor.h"
//#define EN_USART1_RX 			1		 //ʹ�ܣ�1��/��ֹ��0������1����
//#define EN_USART2_RX 			1		 //ʹ�ܣ�1��/��ֹ��0������1����
//#define EN_USART3_RX 			1		 //ʹ�ܣ�1��/��ֹ��0������1����
//#define EN_USART4_RX 			1		 //ʹ�ܣ�1��/��ֹ��0������1����
//#define EN_USART5_RX 			1		 //ʹ�ܣ�1��/��ֹ��0������1��?
#define   HEAD              0x55
#define   TAIL              0xaa
/*==========����1�ṹ��==========*/
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
void UartSend_Byte(USART_TypeDef* USARTx, u8 Data); //�򴮿�USARTx����1���ֽ�����
void UartSend_HalfWord(USART_TypeDef* USARTx, u16 Data);  //����2�ֽ�16λ����
void UartSend_nByte(USART_TypeDef* USARTx,u8* Data,uint16_t length);//�򴮿�USARTx����length���ֽ�����
#endif


