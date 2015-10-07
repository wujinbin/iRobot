/*=====================================================================
//	功能描述：  传感器驱动源文件
//  IDE 环境：  Keil uVision5.1
//  组成文件:	sensor.c,sensor.h
//  硬    件:   PC0~PC2
//  硬件资源:   ADC1
//  维护记录:	  2015-09-28	v1.0
======================================================================*/
#include "sensor.h"
#include "usart.h"
#include "delay.h"

uint16_t ADCAverageValue[3];

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* 函 数 名: sensor_average
* 功    能: 处理传感器数据，滤波
* 入口参数无
* 出口参数: 无
* 说    明: 多路AD采集，PC0~PC2
* 调用方法: 直接调用
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void sensor_average(uint8_t times)
{
	uint32_t temp_val[3] = {0};
	uint8_t i, t;
	for(t=0;t<times;t++)
	{
		for(i = 0;i < 3;i++)
			temp_val[i] += ADCConvertedValue[i];
		//Delay_ms(5);
	}
	ADCAverageValue[0] = (u16)temp_val[0]/times;
	ADCAverageValue[1] = (u16)temp_val[1]/times;
	ADCAverageValue[2] = (u16)temp_val[2]/times;
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* 函 数 名: Sensor
* 功    能: 采集传感器数据并发送
* 入口参数无
* 出口参数: 无
* 说    明: 多路AD采集，PC0~PC2
* 调用方法: 直接调用
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Sensor(void)
{
	u8 i = 0;
	u16 sensor_data = 0;
	u8 data[] = {0xFF,0xFF,0xFF,0xFF,0xFF};
	if(ADC_FLAG == 0xFF)
	{
		ADC_FLAG = 0x00;
		sensor_average(20);
		for(i = 0;i < 3;i++)
		{
			sensor_data = ADCAverageValue[i];
			data[1] = i;
			data[2] = (u8)(sensor_data>>8)&0xFF;//高8位
			data[3] = (u8)sensor_data&0xFF;//低8位
			UartSend_nByte(USART3, data, 5);
		}
	}
}
