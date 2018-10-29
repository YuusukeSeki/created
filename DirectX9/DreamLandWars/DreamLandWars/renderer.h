//*****************************************************************************
//	DirectX�ݒ�N���X[renderer.h]
//	Autohr	:	Yusuke Seki
//*****************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

//---------- �C���N���[�h�t�@�C��
#include "main.h"

//---------- �N���X�̒�`
class Renderer{
private:
	static LPDIRECT3D9			m_pD3D;
	static LPDIRECT3DDEVICE9	m_pD3DDevice;
#ifdef _DEBUG
	static LPD3DXFONT			m_pFont;
#endif
public:
	Renderer(){}
	~Renderer(){}
	static HRESULT				Init( HWND hWnd, BOOL bWindow );	// ������
	static void					Uninit(void);						// �I��
	static HRESULT				DrawBegin(void);					// �`��J�n
	static void					DrawEnd(void);						// �`��I��
	static LPDIRECT3DDEVICE9	GetDevice(void);					// �f�o�C�X�̎擾
#ifdef _DEBUG
	static void					DrawFPS(void);						// FPS�̕\��
#endif
};

#endif
