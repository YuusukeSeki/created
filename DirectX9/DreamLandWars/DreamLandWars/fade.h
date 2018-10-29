//*****************************************************************************
//
// �t�F�[�h
// Author : Yusuke Seki
//
//*****************************************************************************
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

class Fade
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	Fade();
	~Fade();

	// �֐�
	static Fade* Create();
	void Release();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �ݒ�
	void SetColor(unsigned char r = 0xff, unsigned char g = 0xff, unsigned char b = 0xff);

	// �t�F�[�h
	void Start_FadeOut(unsigned int numFrame = 10); // �t�F�[�h�A�E�g�J�n
	bool Finish_FadeOut(); // �t�F�[�h�A�E�g�I������H


private:
	// �F
	union Color {
		unsigned int color;
		unsigned char rgba[4];
	};

	// ���
	static const unsigned char FADE_NONE        = 0b00000000; // ��ԁF�t�F�[�h��������
	static const unsigned char FADE_IN          = 0b00000001; // ��ԁF�t�F�[�h�C��
	static const unsigned char FADE_OUT         = 0b00000010; // ��ԁF�t�F�[�h�A�E�g
	static const unsigned char FADE_OUT_FINISH  = 0b00000100; // ��ԁF�t�F�[�h�A�E�g�I��

	// �֐�
	void UpdateVtxBuf();

	// �ϐ�
	unsigned int m_numFrame; // �t�F�[�h�C�� / �A�E�g����������܂ł̃t���[����
	unsigned char m_FadeState; // ���݂̃t�F�[�h���
	Color m_color;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;


};

#endif
