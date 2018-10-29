//*****************************************************************************
//
//	�����\��
//	Autohr	:	Yusuke Seki
//
//*****************************************************************************
#ifndef _FONT_H_
#define _FONT_H_

//----- �C���N���[�h�t�@�C�� -----
#include "main.h"

//----- �N���X�̒�` -----
class Font
{
public:
	Font(){}
	~Font(){}
	static void Init(void);
	static void Uninit(void);
//	static void Draw(void);   // �o�b�t�@���̕������`��
	static void Draw(int color, const char* pText, ...); // �����̕������`��
//	static void StoreText(const char* pText, ...); // �����̕�������o�b�t�@�Ɋi�[
//	static void SetColor(int color);          // ������̐F���w��F�ɕύX
private:
	static LPD3DXFONT m_pFont;
	//static const int NUM_TEXT = 0x0000ffff; // �m�ۂ���o�b�t�@�̗̈搔
	//static char m_str[NUM_TEXT];            // �o�b�t�@
	union TextColor{
		unsigned int color;
		unsigned char RGBA[4];
	};
	//static TextColor m_textColor; // �����F
};

#endif