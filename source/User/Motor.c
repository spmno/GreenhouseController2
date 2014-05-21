#include	"stm32f10x.h"
#include	"Motor.h"

#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"list.h"
#include	"portable.h"
#include	"freertosconfig.h"

portTickType m_xDelay = 1000 / portTICK_RATE_MS;

void Motor_GPIO_Init( void )
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	return	;
}
void Delay(int nCount)
{
	m_xDelay = nCount / portTICK_RATE_MS;
}

// �̵����øߵ�ƽ,�̵����Ͽ�
void SetRelay( void )
{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
}


// �̵���A�õ͵�ƽ���̵�������
void ReSetRelayA( void )
{
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		
		vTaskDelay(m_xDelay);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

// �̵���B�õ͵�ƽ���̵�������
void ReSetRelayB( void )
{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		
		vTaskDelay(m_xDelay);
		
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
}

void Motor_Entry( void *pvParameters )
{
//	xQueueHandle			xQueue = (xQueueHandle)pvParameters;
	(void)pvParameters;
	Motor_GPIO_Init();
	
	return	;
}

