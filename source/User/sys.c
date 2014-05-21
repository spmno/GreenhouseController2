#include "stm32f10x.h"

#define uint unsigned int
#define uchar unsigned char

#define CLOCK 72/8 //ʱ��=72M

/*------------------------------------------------------------
                         us��ʱ���� 
------------------------------------------------------------*/
void delay_us(unsigned int us)
{
	u8 n;		    
	while(us--)for(n=0;n<CLOCK;n++); 	 
}

/*------------------------------------------------------------
                         ms��ʱ����
------------------------------------------------------------*/
void delay_ms(unsigned int ms)
{
	while(ms--)delay_us(1000);	 
}

/*------------------------------------------------------------
                      ������ʱ�ӼĴ�����λ
------------------------------------------------------------*/
void RCC_DeInit(void)
{									   
	RCC->APB2RSTR = 0x00000000;//���踴λ			 
	RCC->APB1RSTR = 0x00000000;   	  
  	RCC->AHBENR = 0x00000014;  //flashʱ��,����ʱ��ʹ��.DMAʱ�ӹر�	  
  	RCC->APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //ʹ���ڲ�����ʱ��HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //��λHSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //��λHSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //�ر������ж�
}


/*------------------------------------------------------------
                  �ⲿ8M,��õ�72M��ϵͳʱ��
------------------------------------------------------------*/	
void Stm32_Clock_Init(void)
{
	ErrorStatus HSEStartUpStatus; 

	RCC_DeInit();

	RCC_HSEConfig(RCC_HSE_ON);

	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
	if (HSEStartUpStatus == SUCCESS) {

		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		RCC_PCLK2Config(RCC_HCLK_Div1);

		RCC_PCLK1Config(RCC_HCLK_Div2);

		FLASH_SetLatency(FLASH_Latency_2);

		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

		RCC_PLLCmd(ENABLE);

		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		while(RCC_GetSYSCLKSource() != 0x08);
	}
}

