#include <stm32f10x.h>
#include "RealTimeClock.h"

static CLOCK_TASK Current_Clock_Task;

void Rtc_Configure()
{
	//ʹ�ܵ�Դ�ͺ󱸼Ĵ�����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	//ʹ�ܺ󱸼Ĵ����
	PWR_BackupAccessCmd(ENABLE);
	//��ָ���Ĵ����ж�����
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		//��ֵ����Ϊȱʡֵ
		BKP_DeInit(); 
		//�����ⲿ����ʱ�ӣ�32K
		RCC_LSEConfig(RCC_LSE_ON); 
		//�ȴ��ⲿʱ����
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
		//ʹ���ⲿʱ��ΪRTC
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  
		//����RTC
		RCC_RTCCLKCmd(ENABLE);
		//�ȴ�RTCͬ��
		RTC_WaitForSynchro();
		//�ȴ�RTC���һ��д�������
		RTC_WaitForLastTask();
		//�������ж�
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		
		RTC_WaitForLastTask();
		RTC_SetPrescaler(32776); 
		RTC_WaitForLastTask();
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);  
		
	}
	else 
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		RTC_WaitForLastTask();
		RCC_ClearFlag(); 
	}
}

void Rtc_NVIC_Configure()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);                                             
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;                             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                                           
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                               
	NVIC_Init(&NVIC_InitStructure);
	return;
}

void RTC_IRQHandler(void)
{
	//���������ж�
	if(RTC_GetITStatus(RTC_IT_SEC) != RESET) 
	{
		RTC_ClearITPendingBit(RTC_IT_SEC);
		if (Current_Clock_Task != 0)
		{
			(*Current_Clock_Task)();
		}
	}
}

int Real_Time_Clock_Init()
{
	Rtc_Configure();
	Rtc_NVIC_Configure();
	return 0;
}

void Register_Real_Time_Task(CLOCK_TASK task)
{
	Current_Clock_Task = task;
	return ;
}

void Real_Time_Clock_Adjust(char Hour, char Minute, char Second)
{
	int Count = Hour*60*60 + Minute*60 + Second;
	RTC_WaitForLastTask();  
  RTC_SetCounter(Count);  
	RTC_WaitForLastTask();
}
