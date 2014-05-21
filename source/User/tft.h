
#include	"Font.h"

#ifndef __TFT_H__
#define __TFT_H__

// ��Ļ��������
#define	TFT_DRIVER_ILI9326			(1)
//#define	TFT_DRIVER_ILI9327			(2)

// ��ʼ��
void TFT_Initialize( void );

// ����
void TFT_ClearScreen( unsigned int uiColor );

// �����軭
void TFT_DrawRectangle(	unsigned int	uiStartX,
						unsigned int	uiEndX,
						unsigned int	uiStartY,
						unsigned int	uiEndY,
						unsigned int	uiColor	);

// �ַ����軭
void TFT_DrawString(	unsigned int	uiOffsetX,
						unsigned int	uiOffsetY,
						unsigned char*	pucString,
						unsigned int	uiForeColor,
						unsigned int	uiBackColor,
						FontSizeEnum	enFontSize	);


#endif

