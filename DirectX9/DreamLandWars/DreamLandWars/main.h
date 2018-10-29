//*****************************************************************************
//	���C���֐�[main.h]
//	Author	:	Yusuke Seki
//*****************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//----------- �C���N���[�h�t�@�C��
#include <stdio.h>
#include <windows.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION	(0x0800)
#include <dinput.h>
#include <XAudio2.h>
#include "oxdebugfont.h"

//---------- �v���O�}�R�����g
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")

//---------- �萔��`
const int SCREEN_WIDTH	= 1280;	// ��ʕ�
const int SCREEN_HEIGHT	= 720;	// ��ʍ���
#define FVF_VERTEX_2D	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )				// ���_�t�H�[�}�b�g(2D�|���S��)
#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL )	// ���_�t�H�[�}�b�g(3D�|���S��)
#define _MSG(msg)	    (MessageBox(NULL, msg, NULL, MB_OK               ))
#define _MSGERROR(msg, title)	(MessageBox(NULL, msg, title, MB_OK | MB_ICONERROR))

//---------- �\���̂̒�`
typedef struct
{	// ���_���W�i2D�|���S���j
	D3DXVECTOR3 pos;	// �R���_�̍��W
	float rhw;			// ���W�ϊ��ςݒ��_�t���O
	D3DCOLOR color;		// ���_���̐F
	D3DXVECTOR2 tex;	// �e�N�X�`���[���W
}VERTEX_2D;

typedef struct
{	// ���_���W�i3D�|���S���j
	D3DXVECTOR3 pos;	// �R���_�̍��W
	D3DXVECTOR3 normal;	// �@��
	D3DCOLOR color;		// ���_���̐F
	D3DXVECTOR2 tex;	// �e�N�X�`���[���W
}VERTEX_3D;

//---------- �v���g�^�C�v�錾
#ifdef _DEBUG
int GetFPS(void);	// FPS�擾
#endif

HWND GetHWnd();

#endif