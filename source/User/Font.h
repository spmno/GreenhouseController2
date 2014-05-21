
#ifndef	__FONT_H__
#define	__FONT_H__

// �����С
typedef enum tagFontSizeEnum
{
	FontSize_24,

	FontSize_Cnt,
	FontSize_Invalid = FontSize_Cnt

} FontSizeEnum;

// ����Mask��Ϣ
typedef struct tagFontMaskInfo_t {

	unsigned char			ucWidth;
	unsigned char			ucHeight;
	unsigned char			ucSize;
	const unsigned char*	pucMask;

} FontMaskInfo_t;

// ����ֵ
typedef enum tagFontRsltEnum
{
	FontRslt_Success = 0,
	FontRslt_Failed,

} FontRsltEnum;

FontRsltEnum Font_GetMask( FontSizeEnum enFontSize, const unsigned char* pucFont, FontMaskInfo_t* FontMaskInfo );

#endif	/* __KEY_H__ */
