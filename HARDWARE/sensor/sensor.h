/*=====================================================================
//	功能描述：  传感器驱动头文件
//  IDE 环境：  Keil uVision5.1
//  组成文件:	sensor.c,sensor.h
//  硬    件:   ADC1,PC0~PC2
//  硬件资源:   PWM
//  维护记录:	  2015-09-28	v1.0
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
