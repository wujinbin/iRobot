/*=====================================================================
//	����������  ����������Դ�ļ�
//  IDE ������  Keil uVision5.1
//  ����ļ�:	sensor.c,sensor.h
//  Ӳ    ��:   PC0~PC2
//  Ӳ����Դ:   ADC1
//  ά����¼:	  2015-09-28	v1.0
======================================================================*/
#include "sensor.h"
#include "usart.h"
#include "delay.h"

uint16_t ADCAverageValue[3];

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
* �� �� ��: sensor_average
* ��    ��: �����������ݣ��˲�
* ��ڲ����u��
* ���ڲ���: ��
* ˵    ��: ��·AD�ɼ���PC0~PC2
* ���÷���: ֱ�ӵ���
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
* �� �� ��: Sensor
* ��    ��: �ɼ����������ݲ�����
* ��ڲ����u��
* ���ڲ���: ��
* ˵    ��: ��·AD�ɼ���PC0~PC2
* ���÷���: ֱ�ӵ���
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
			data[2] = (u8)(sensor_data>>8)&0xFF;//��8λ
			data[3] = (u8)sensor_data&0xFF;//��8λ
			UartSend_nByte(USART3, data, 5);
		}
	}
}
