
#ifndef	__Motor_H__
#define	__Motor_H__

void Motor_GPIO_Init( void );

// ������ʱ���ڣ���λΪms����������ô˺�������ʱ����Ĭ��1S
void Delay(int nCount);

// �̵����øߵ�ƽ 
void SetRelay( void );

// �̵���A�õ͵�ƽ
void ReSetRelayA( void );

// �̵���B�õ͵�ƽ
void ReSetRelayB( void );

void Motor_Entry( void *pvParameters );
#endif	/* __Motor_H__ */
