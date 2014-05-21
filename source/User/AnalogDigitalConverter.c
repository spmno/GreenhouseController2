#include "AnalogDigitalConverter.h"

int Analog_Digital_Converter_Init()
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1, ENABLE );
	
	//6��Ƶ12M,С��14M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//ADC�ָ�Ĭ��ֵ
	ADC_DeInit(ADC1);
	
	//����ģʽ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	//��ͨ��ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	//����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
	//ת������������������ⲿ����
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	//ADC�����Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	//˳�����ADCת������Ŀ
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC1, &ADC_InitStructure);
	//ʹ��ADC1
	ADC_Cmd(ADC1, ENABLE);  
  //����У׼    
  ADC_ResetCalibration(ADC1); 
  //����״̬�Ĵ���     
  while(ADC_GetResetCalibrationStatus(ADC1)); 
  //��ʼУ׼    
  ADC_StartCalibration(ADC1); 
  //�ȴ�У׼���� 
  while(ADC_GetCalibrationStatus(ADC1));      
  //�����������   
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);     
	
	return 0;
}

u16 Get_ADC_Data(u8 channel)
{
	u16 value = 0;
	//����ָ��ͨ����ϣ�����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5 );				    
  //��ʼ����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);			
	//�ȴ�����
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	
	value = ADC_GetConversionValue(ADC1);
	return value;	
}






























