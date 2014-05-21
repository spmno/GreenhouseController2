
#include	"stm32f10x.h"
#include	"key.h"
#include	"Business.h"

#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"list.h"
#include	"portable.h"
#include	"freertosconfig.h"


#define	Get_Key1_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
#define	Get_Key2_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
#define	Get_Key3_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
#define	Get_Key4_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
#define	Get_Key5_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
#define	Get_Key6_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
#define	Get_Key7_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
#define	Get_Key8_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6))

void Key_Init( void )
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_Init( GPIOB, &GPIO_InitStructure );

	return	;
}

KeyTypeEnum Key_Scan( void )
{
	KeyTypeEnum	enKeyType = KeyType_Invalid;

	if( !Get_Key1_Up() )  // ����Ƿ���
	{
		delay_ms( 10 );	//ȥ��

		if( !Get_Key1_Up() )
		{
			while( !Get_Key1_Up() );	//�ȴ������ͷţ�������ͷŰ���һֱ�ȴ��˴�����ִ���������򣬳���������ʹ�����ֳ���

			delay_ms( 10 );	//�ͷŰ���ȥ��

			if( Get_Key1_Up() )	//�����ȫ�ͷź�ִ�а�������
			{
				enKeyType = KeyType_1;
			}
		}
	}

	if( !Get_Key2_Up() )  // ����Ƿ���
	{
		delay_ms( 10 );	//ȥ��

		if( !Get_Key2_Up() )
		{
			while( !Get_Key2_Up() );	//�ȴ������ͷţ�������ͷŰ���һֱ�ȴ��˴�����ִ���������򣬳���������ʹ�����ֳ���

			delay_ms( 10 );	//�ͷŰ���ȥ��

			if( Get_Key2_Up() )	//�����ȫ�ͷź�ִ�а�������
			{
				enKeyType = KeyType_2;
			}
		}
	}

	if( !Get_Key3_Up() )  // ����Ƿ���
	{
		delay_ms( 10 );	//ȥ��

		if( !Get_Key3_Up() )
		{
			while( !Get_Key3_Up() );	//�ȴ������ͷţ�������ͷŰ���һֱ�ȴ��˴�����ִ���������򣬳���������ʹ�����ֳ���

			delay_ms( 10 );	//�ͷŰ���ȥ��

			if( Get_Key3_Up() )	//�����ȫ�ͷź�ִ�а�������
			{
				enKeyType = KeyType_3;
			}
		}
	}

	if( !Get_Key4_Up() )  // ����Ƿ���
	{
		delay_ms( 10 );	//ȥ��

		if( !Get_Key4_Up() )
		{
			while( !Get_Key4_Up() );	//�ȴ������ͷţ�������ͷŰ���һֱ�ȴ��˴�����ִ���������򣬳���������ʹ�����ֳ���

			delay_ms( 10 );	//�ͷŰ���ȥ��

			if( Get_Key4_Up() )	//�����ȫ�ͷź�ִ�а�������
			{
				enKeyType = KeyType_4;
			}
		}
	}

	if( !Get_Key5_Up() )  // ����Ƿ���
	{
		delay_ms( 10 );	//ȥ��

		if( !Get_Key5_Up() )
		{
			while( !Get_Key5_Up() );	//�ȴ������ͷţ�������ͷŰ���һֱ�ȴ��˴�����ִ���������򣬳���������ʹ�����ֳ���

			delay_ms( 10 );	//�ͷŰ���ȥ��

			if( Get_Key5_Up() )	//�����ȫ�ͷź�ִ�а�������
			{
				enKeyType = KeyType_5;
			}
		}
	}

	if( !Get_Key6_Up() )  // ����Ƿ���
	{
		delay_ms( 10 );	//ȥ��

		if( !Get_Key6_Up() )
		{
			while( !Get_Key6_Up() );	//�ȴ������ͷţ�������ͷŰ���һֱ�ȴ��˴�����ִ���������򣬳���������ʹ�����ֳ���

			delay_ms( 10 );	//�ͷŰ���ȥ��

			if( Get_Key6_Up() )	//�����ȫ�ͷź�ִ�а�������
			{
				enKeyType = KeyType_6;
			}
		}
	}

	if( !Get_Key7_Up() )  // ����Ƿ���
	{
		delay_ms( 10 );	//ȥ��

		if( !Get_Key7_Up() )
		{
			while( !Get_Key7_Up() );	//�ȴ������ͷţ�������ͷŰ���һֱ�ȴ��˴�����ִ���������򣬳���������ʹ�����ֳ���

			delay_ms( 10 );	//�ͷŰ���ȥ��

			if( Get_Key7_Up() )	//�����ȫ�ͷź�ִ�а�������
			{
				enKeyType = KeyType_7;
			}
		}
	}

	if( !Get_Key8_Up() )  // ����Ƿ���
	{
		delay_ms( 10 );	//ȥ��

		if( !Get_Key8_Up() )
		{
			while( !Get_Key8_Up() );	//�ȴ������ͷţ�������ͷŰ���һֱ�ȴ��˴�����ִ���������򣬳���������ʹ�����ֳ���

			delay_ms( 10 );	//�ͷŰ���ȥ��

			if( Get_Key8_Up() )	//�����ȫ�ͷź�ִ�а�������
			{
				enKeyType = KeyType_8;
			}
		}
	}

	return	enKeyType;
}

void Key_Entry( void *pvParameters )
{
	xQueueHandle			xQueue = (xQueueHandle)pvParameters;

	BusinessQueueItem_t*	pstBusinessQueueItem = NULL;

	portTickType	xLastWakeTime = xTaskGetTickCount();

	Key_Init();
	
	while ( 1 )
	{
		KeyTypeEnum	enKeyType = Key_Scan();

		if ( enKeyType != KeyType_Invalid )
		{
			pstBusinessQueueItem = (BusinessQueueItem_t*)malloc( sizeof(BusinessQueueItem_t) );

			if ( pstBusinessQueueItem != NULL )
			{
				pstBusinessQueueItem->enItemType = BusinessQuueueItemType_Key;
				pstBusinessQueueItem->u.enKey = enKeyType;

				xQueueSend( xQueue, &pstBusinessQueueItem, 5000 / portTICK_RATE_MS );
			}
		}
	
		vTaskDelayUntil( &xLastWakeTime, ( 50 / portTICK_RATE_MS ) );
	}

	return	;
}

