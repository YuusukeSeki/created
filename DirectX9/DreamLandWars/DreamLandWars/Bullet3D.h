//*****************************************************************************
//	
//		�o���b�g�i3D�j
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _OL3D_BULLET_H_
#define _OL3D_BULLET_H_

#include "main.h"
#include "Object3D.h"



class Bullet3D : public Object3D
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	Bullet3D() {}
	Bullet3D(Object::TYPE type);
	virtual ~Bullet3D();


	//----- ��{�I�Ȋ֐� -----
	static Bullet3D* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	virtual void Uninit(void);
	virtual void Update(void) {}
	virtual void Draw(void);

	
	//----- �ݒ菈�� -----
	//void SetBullet(); // �����g�p


	//----- �f�[�^��Ԃ����� -----
	D3DXVECTOR3& GetVecZ()     { return m_vecZ; }		// �����Ă������Ԃ�
	bool         GetInstance() { return m_bInstance; }	// �g�p���t���O��Ԃ�


protected:
	//----- �ݒ菈�� -----
	void SetVecZ(D3DXVECTOR3& vecZ);								// �����Ă�������̐ݒ�
	void SetMove(float move) { m_move = move; }							// �����x�̐ݒ�
	void SetAccelerate(float accelerate) { m_accelerate = accelerate; }	// �����x�̐ݒ�
	void SetInstance(bool bInstanse) { m_bInstance = bInstanse; }		// �g�p���t���O�̐ݒ�

	//----- �f�[�^��Ԃ����� -----
	float GetMove()       { return m_move; }		// �����x��Ԃ�
	float GetAccelerate() { return m_accelerate; }	// �����x��Ԃ�


private:
	//----- �f�[�^ -----
	D3DXVECTOR3 m_vecZ;			// ����
	float       m_move;			// �����x
	float       m_accelerate;	// �����x
	bool        m_bInstance;	// �g�p���t���O

	// �����ŏ�����^�C�v�̃o���b�g�p
	//int m_life;

	// �����ŏ�����^�C�v�̃o���b�g�p
	//D3DXVECTOR3 m_uninitPos;	   // �����n�_
	//D3DXVECTOR3 m_vecInitToUninit; // �����p�̒P�ʃx�N�g��


};


#endif

#pragma once
