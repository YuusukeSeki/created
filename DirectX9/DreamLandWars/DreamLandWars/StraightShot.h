#pragma once
//*****************************************************************************
//	
//		�X�g���[�g�V���b�g
//													Autohr : Yusuke Seki
//*****************************************************************************
#ifndef _STRAIGHTSHOT_H_
#define _STRAIGHTSHOT_H_

#include "main.h"
#include "Bullet3D.h"

class Player;

class StraightShot : public Bullet3D
{
public:
	//----- �R���X�g���N�^ / �f�X�g���N�^ -----
	StraightShot() {}
	StraightShot(Object::TYPE type);
	virtual ~StraightShot();


	//----- ��{�I�Ȋ֐� -----
	static StraightShot* Create(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Init(D3DXVECTOR3& position, D3DXVECTOR3& size);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	//----- �ݒ菈�� -----
	static void SetStraightShot(Player& player);	// SS�̔���


	//----- �f�[�^��Ԃ����� -----


protected:


private:
	//----- ���\�b�h -----
	void SetStraightShot_Private(Player& player);	// SS�̐ݒ�
	bool CollisionSoldier();	// true �ŏ���
	bool CollisionPlayer();		// true �ŏ���
	bool CollisionWall();		// true �ŏ���

	//----- �f�[�^ -----
	D3DXVECTOR3 m_uninitPos;		// �����n�_
	D3DXVECTOR3 m_vecInitToUninit;	// �����p�̒P�ʃx�N�g��
	Player* m_pParent;				// �e

};


#endif

