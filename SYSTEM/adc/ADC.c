#include "ADC.h"
#include "dma.h"
#include "delay.h"

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: adc_Init
** ��������: adת����ʼ������
** ��������: PC0~PC2
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void adc_Init()
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PC0 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	dma_Init();
	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	//ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	//ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_NbrOfChannel = 3;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

	/* ADC1 regular channel10 configuration ADCͨ���飬 ��1��ͨ�� ����˳��1��ת��ʱ�� 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);*/ 

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_239Cycles5 );
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Get_Adc
** ��������: ��ȡͨ��ch��ADת����ֵ
** ��������: uint8_t ch
** ��  ����: wu
** �ա�  ��: 2015��09��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
uint16_t Get_Adc(uint8_t ch)
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			     
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Get_Adc_Average
** ��������: ��ȡͨ��ch��ADת����ֵ
** ��������: uint8_t ch,uint8_t times
** ��  ����: wu
** �ա�  ��: 2015��09��20��
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

