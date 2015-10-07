#include "ADC.h"
#include "dma.h"
#include "delay.h"

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: adc_Init
** 功能描述: ad转化初始化函数
** 参数描述: PC0~PC2
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void adc_Init()
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PC0 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	dma_Init();
	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	//ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	//ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_NbrOfChannel = 3;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

	/* ADC1 regular channel10 configuration ADC通道组， 第1个通道 采样顺序1，转换时间 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);*/ 

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_239Cycles5 );
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Get_Adc
** 功能描述: 获取通道ch的AD转换数值
** 参数描述: uint8_t ch
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint16_t Get_Adc(uint8_t ch)
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			     
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Get_Adc_Average
** 功能描述: 获取通道ch的AD转换均值
** 参数描述: uint8_t ch,uint8_t times
** 作  　者: wu
** 日　  期: 2015年09月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times)
{
	uint32_t temp_val=0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		Delay_ms(5);
	}
	return temp_val/times;	
}

//uint16_t Get_Average(uint8_t times)
//{
//	uint32_t temp_val[3] = {0};
//	uint8_t i, t;
//	for(t=0;t<times;t++)
//	{
//		for(i = 0;i < 3;i++)
//		{
//			temp_val[i] += ADCConvertedValue[i];
//			Delay_ms(5);
//		}
//	}
//	ADCConvertedValue[0] = temp_val[0]/times;
//	ADCConvertedValue[1] = temp_val[1]/times;
//	ADCConvertedValue[2] = temp_val[2]/times;
//}

