/*=====================================================================
//	����������  ����������ͷ�ļ�
//  IDE ������  Keil uVision5.1
//  ����ļ�:	sensor.c,sensor.h
//  Ӳ    ��:   ADC1,PC0~PC2
//  Ӳ����Դ:   PWM
//  ά����¼:	  2015-09-28	v1.0
======================================================================*/
#ifndef __SENSOR_H
#define __SENSOR_H	

#include "sys.h"

extern uint16_t ADCConvertedValue[3];
extern uint8_t ADC_FLAG;

void sensor_average(uint8_t times);
void Sensor(void);

#endif
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
