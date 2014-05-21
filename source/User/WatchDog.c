#include <stm32f10x.h>
#include "WatchDog.h"

static void IWDG_Configuration(void)
{
 	RCC_LSICmd(ENABLE);                              //LSI
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);
	/* ʹ�ܶԿ��Ź�д���� */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	//IWDG_PR: 40KHz(LSI) / 32 = 1.25 KHz //800u 
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	//һ���Ӳ�ι���͸�λ
	IWDG_SetReload(1250);	  
	IWDG_ReloadCounter();
	IWDG_Enable();
}


int WatchDog_Init()
{
	IWDG_Configuration();
	return 0;
}

int WatchDog_Feed()
{
	IWDG_ReloadCounter();  
	return 0;
}
