#include <stm32f10x.h>
#include "Usart1.h"

#define  USARTx                     USART1
#define  GPIOx                      GPIOA
#define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOA
#define  GPIO_RxPin                 GPIO_Pin_10
#define  GPIO_TxPin                 GPIO_Pin_9

void Uart1_PutString(u8* buf , u8 len);
u8 Uart1_PutChar(u8 ch);

void USART1_IRQHandler(void)
{
	uint16_t ReceiveData = USART_ReceiveData(USART1);
}

void Uart1_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                                             
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                                           
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                               
	NVIC_Init(&NVIC_InitStructure);
}

int Usart1_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;				  //�������ͽṹ��
	USART_ClockInitTypeDef USART_ClockInitStructure;	  //����ʱ�ӽṹ�� 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
		//����USARTx_TxΪ�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOx, &GPIO_InitStructure); 
	//���� USARTx_Rx Ϊ��������
	GPIO_InitStructure.GPIO_Pin = GPIO_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOx, &GPIO_InitStructure);

	//�������ã� ������ 115200 ����λ 8 ֹͣλ 1  ��żλ NONE  
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity =  USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	USART_ClockInit(USART1, &USART_ClockInitStructure);
	//��ʼ������
	USART_Init(USARTx, &USART_InitStructure);
	//���ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//��������
	USART_Cmd(USARTx, ENABLE);
	
	Uart1_NVIC_Config();
	
	return 0;
}

//����һ���ַ���
/*******************************************************************************
* Name  : Uart1_PutString
* Deion : print a string to the uart1
* Input : bufΪ�������ݵĵ�ַ , lenΪ�����ַ��ĸ���
*******************************************************************************/
void Uart1_PutString(u8* buf , u8 len)
{   u8 i;
    for(i=0;i<len;i++)
    {
        Uart1_PutChar(*buf++);
    }
}
//����һ���ַ�
/*******************************************************************************
* Name  : Uart1_PutChar
* Deion : printf a char to the uart.
*******************************************************************************/
u8 Uart1_PutChar(u8 ch)
{
	/* Write a character to the USART */
	USART_SendData(USART1, (u8) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
	{
	}
	return ch;
}
