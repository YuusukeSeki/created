//*****************************************************************************
//
//		���C�g
//													Autohr : Yusuke Seki
//
//*****************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"


class Light
{
public:
	// �R���X�g���N�^ / �f�X�g���N�^
	Light();
	~Light();

	// ��{�I�Ȋ֐�
	static Light* Create(void);
	void Release(void);
	void Init(void);
	void Uninit(void);
	void Update(void);

	// �ݒ�
	void SetDiffuse(float r, float g, float b, float a);
	void SetAmbient(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);

	// �����̐ݒ�
	// vecDirection : �ݒ肵��������
	void SetVectorDirection(D3DXVECTOR3& vecDirection);



private:
	D3DLIGHT9	m_light;
	D3DXVECTOR3	m_vecDir;	// ���̌���


};

#endif