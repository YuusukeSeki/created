//*****************************************************************************
//
//	�����\��
//	Autohr	:	Yusuke Seki
//
//*****************************************************************************
#include "font.h"
#include "renderer.h"
#include <string>

//----- �ÓI�ϐ������� -----
LPD3DXFONT Font::m_pFont = nullptr;
//char Font::m_str[NUM_TEXT] = {};
//Font::TextColor Font::m_textColor;

//=============================================================================
// ������
//=============================================================================
void Font::Init(void)
{
	// D3D�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	// �F�̐ݒ�
	//m_textColor.color = 0x00ff00ff;
}

//=============================================================================
// �I��
//=============================================================================
void Font::Uninit(void)
{
	// ���������t�H���g�����
	if (m_pFont != nullptr) {
		m_pFont->Release();
	}

	// �o�b�t�@������������
	//m_str[0] = '\0';

	// �e�L�X�g�F��������
	//m_textColor.color = 0x00ff00ff;
}

//=============================================================================
// ��������o�b�t�@�Ɋi�[
//=============================================================================
//void Font::StoreText(const char* pText, ...)
//{
//	// �����̕������o�b�t�@�Ɋi�[
//	strcat_s(m_str, pText);
//	strcat_s(m_str, "\n");
//}

//=============================================================================
// �o�b�t�@���̕�����`��
//=============================================================================
//void Font::Draw(void)
//{
//	// �ϐ��錾
//	char r = m_textColor.RGBA[3]; // ��
//	char g = m_textColor.RGBA[2]; // ��
//	char b = m_textColor.RGBA[1]; // ��
//	char a = m_textColor.RGBA[0]; // ���l
//
//	// �N���C�A���g�̈�擾
//	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
//
//	// �`��
//	m_pFont->DrawText(nullptr, &m_str[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(r, g, b, a));
//
//	// �o�b�t�@������������
//	m_str[0] = '\0';
//}

//=============================================================================
// �����̕�����`��
//=============================================================================
void Font::Draw(int color, const char* pText, ...)
{
	// �ϐ��錾
	TextColor tColor;
	tColor.color = color;
	char r = tColor.RGBA[3]; // ��
	char g = tColor.RGBA[2]; // ��
	char b = tColor.RGBA[1]; // ��
	char a = tColor.RGBA[0]; // ���l
	char str[256];

	// �ϒ������̑��
	va_list ap;
	va_start(ap, pText);
	vsprintf(str,pText, ap);
	va_end(ap);

	// �N���C�A���g�̈�擾
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	// �`��
	m_pFont->DrawText(nullptr, &str[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(r, g, b, a));
}

//=============================================================================
// �F��ݒ�
//=============================================================================
//void Font::SetColor(int color)
//{
//	m_textColor.color = color;
//}
